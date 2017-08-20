#include <io.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <usb.h>
#include <usb-serial.h>

/* This is the setup callback; we reply to CP2102 requests */
static int us_setup_cb(struct usb_device *ud, void *buf, int len, int error)
{
	struct usb_setup *s = buf;
	static uint32_t baud = 9600;
	static const uint16_t line_control = 0x800;
	static const uint8_t flow_control[16];
	static const uint16_t modem_status = 0x03;

	if (0)
		printf("%s: %02x %02x %04x %04x %04x\n", __func__,
		       s->bRequestType,
		       s->bRequest,
		       s->wValue,
		       s->wIndex,
		       s->wLength);

	/* See AN571 for protocol */
	switch(s->bRequest) {
	case 0x00: /* enable or disable: ignore */
	case 0x07: /* set modem handshake: ignore */
		usb_setup_reply(ud, NULL, 0);
		break;
	case 0x1d: /* get baud date */
		usb_setup_reply(ud, &baud, 4);
		break;
	case 0x04: /* get line control */
		usb_setup_reply(ud, &line_control, 2);
		break;
	case 0x14: /* get flow control */
		usb_setup_reply(ud, flow_control, 16);
		break;
	case 0x08: /* get modem status */
		usb_setup_reply(ud, &modem_status, 1);
		break;

	case 0x1e: /* set baud rate: we got 4 bytes */
		memcpy(&baud, ud->ep0_out_buffer, 4);
		printf("baud now %li\n", baud);
		usb_setup_reply(ud, NULL, 0);
		break;
	default:
		printf("unhandled request %02x\n", s->bRequest);
	}

	return 0;
}

/* Note; "rd" and "wr" are from our POV, "out" and "in" from the host POV */

static struct usbser *us; /* Maybe the following should be inside the device */
static char us_rd_buffer[CONFIG_USBSERIAL_BSIZE];
static char us_wr_buffer[CONFIG_USBSERIAL_BSIZE];
static int us_rd_bsize;
static int us_wr_bsize;
static int us_rd_error;
static int us_wr_busy;

/* Output callback: we got data from the host, we accumulate in the buffer */
static int us_out_cb(struct usb_device *ud, void *buf, int len, int error)
{
	char *us_b = us_rd_buffer + us_rd_bsize;
	int maxsize;

	if (error) {
		us_rd_error = error > 0 ? error : -error; /* positive errno */
		return 0;
	}
	maxsize = CONFIG_USBSERIAL_BSIZE - us_rd_bsize;
	if (len > maxsize) {
		len = maxsize;
		us_rd_error = ENOSPC;
	}
	memcpy(us_b, buf, len);
	us_rd_bsize += len;
	if (us && us->flags & USBSER_FLAG_ECHO)
		usbser_write(us, buf, len);
	return 0;
}

/* Input callback: our frame went through. Proceed with busy/idle FSM */
static int us_in_cb(struct usb_device *ud, void *buf, int len, int error)
{
	if (!us_wr_bsize) {
		us_wr_busy = 0;
		return 0;
	}
	/* send the current buffer content and keep busy on */
	usb_ep1_in_submit(ud, us_wr_buffer, us_wr_bsize);
	us_wr_bsize = 0;
	return 0;
}

/* Configuration: we use CP2102 vendor and device ID */
static struct usb_config usbc = {
	.vendor = 0x10c4,
	.device = 0xea60,
	.devrelease = 0x0100,
};

/* Device: configuration and callbacks */
static struct usb_device usbd = {
	.cfg = &usbc,
	.setup_cb = us_setup_cb,
	.ep1_out_cb = us_out_cb,
	.ep1_in_cb = us_in_cb,
};

/*
 * External API
 */
struct usbser *usbser_init(struct usbser *userus)
{
	if (us->ud == &usbd)
		return NULL; /* EBUSY: do not re-init */
	us = userus; /* remember it */
	us->ud = &usbd;
	us->flags &= USBSER_USER_FLAGS;

	usb_init(&usbd); /* Error check? */
	return us;
}

/* Read methods work as polling too */
static void usbser_poll(struct usbser *us)
{
	int vbus;

	usb_poll(us->ud);

	if (us->ud->state == USB_DETACHED) {
		vbus = usb_attach(us->ud, 0);
		if (vbus)
			usb_attach(us->ud, 1);
		return;
	}
	vbus = usb_attach(us->ud, 1); /* bah: no polling without setting */

	if (!vbus) {
		usb_attach(us->ud, 0);
		return;
	}

	if (us->ud->state != USB_CONFIGURED)
		return;

	/* If we failed writing last time, do it now */
	if (us_wr_bsize && !us_wr_busy) {
		usb_ep1_in_submit(us->ud, us_wr_buffer, us_wr_bsize);
		us_wr_bsize = 0;
	}
	/* There no "output submit (for our read), as usb.c does it */

}



/* Write: fill the buffer and possibly send it out */
int usbser_write(struct usbser *us, const void *buf, int len)
{
	int maxlen = CONFIG_USBSERIAL_BSIZE - us_wr_bsize;

	if (len > maxlen) len = maxlen;

	memcpy(us_wr_buffer + us_wr_bsize, buf, len);
	us_wr_bsize += len;
	/* we can't call usbser_poll(us); as we may be in the out callback */
	return len;
}

/* FIXME: rd_error (as accumulated ENOSPC) is not used */
int usbser_read(struct usbser *us, void *buf, int len)
{
	usbser_poll(us);

	if (len > us_rd_bsize)
		len = us_rd_bsize;
	if (!len)
		return -EAGAIN;
	memcpy(buf, us_rd_buffer, len);
	/* move back the trailing part, if any */
	us_rd_bsize -= len;
	memcpy(us_rd_buffer, us_rd_buffer + len, us_rd_bsize);
	return len;
}

/* consider \r like \n; if \r\n the reader will get an empty line too */
int usbser_gets(struct usbser *us, void *buf, int len)
{
	int i;

	usbser_poll(us);

	for (i = 0; i < us_rd_bsize; i++) {
		if (us_rd_buffer[i] == '\r')
			us_rd_buffer[i] = '\n';
		if (us_rd_buffer[i] == '\n')
			break;
	}
	if (i == us_rd_bsize)
		return -EAGAIN;
	i++; /* the newline itself */

	/* So, there is newline. If the user buffer won't fit, ENOSPC */
	if (i > len)
		return -ENOSPC;
	return usbser_read(us, buf, i);
}
