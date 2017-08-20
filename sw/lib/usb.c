#include <assert.h>
#include <time.h>
#include <string.h>
#include <io.h>
#include <usb.h>
#include <usb-int.h>

/*
 * This file is currently a mixup of generic and cpu-specific stuff
 */
static struct usb_hw_device usb_hw_device;

static struct usb_dev_desc usb_dev_desc = {
	.bLength = sizeof(struct usb_dev_desc),
	.bDescriptorType = USB_DT_DEVICE,
	.bcdUSB = 0x100, /* might be 0200, but this is easier it seems */
	.bDeviceClass = USB_CLASS_PER_INTERFACE,
	.bDeviceProtocol = 0,
	.bMaxPacketSize0 = 64,
	/* idVendor, idProduct, bcdDevice set at run time (CONFIG_ + const?) */
	.iManufacturer = 0, /* no strings by now */
	.iProduct = 0, /* no strings by now */
	.iSerialNumber = 0, /* no strings by now */
	.bNumConfigurations = 1,
};

static const struct usb_cfg_desc usb_cfg_desc = {
	.bLength = sizeof(struct usb_cfg_desc),
	.bDescriptorType = USB_DT_CONFIG,
	.wTotalLength = 32, /* this + 1 interface + 2 endpoints = 9+9+7+7 */
	.bNumInterfaces = 1,
	.bConfigurationValue = 1,
	.iConfiguration = 0, /* no string for this cfg */
	.bmAttributes = USB_CONFIG_ATT_ONE | USB_CONFIG_ATT_SELFPOWER,
	.bMaxPower = 5, /* 10mA -- just a value */
};

static const struct usb_if_desc usb_if_desc = {
	.bLength = sizeof(struct usb_if_desc),
	.bDescriptorType = USB_DT_INTERFACE,
	.bInterfaceNumber = 0,
	.bAlternateSetting = 0,
	.bNumEndpoints = 2,
	.bInterfaceClass = 255,
	.bInterfaceSubClass = 0,
	.bInterfaceProtocol = 0,
	.iInterface = 0,
};

static const struct usb_ep_desc usb_ep_desc[2] = {
	{
		.bLength = sizeof(struct usb_ep_desc),
		.bDescriptorType = USB_DT_ENDPOINT,
		.bEndpointAddress = 0x81,
		.bmAttributes = USB_ENDPOINT_XFER_BULK,
		.wMaxPacketSize = 64,
		.bInterval = 0,
	}, {
		.bLength = sizeof(struct usb_ep_desc),
		.bDescriptorType = USB_DT_ENDPOINT,
		.bEndpointAddress = 0x01,
		.bmAttributes = USB_ENDPOINT_XFER_BULK,
		.wMaxPacketSize = 64,
		.bInterval = 0,
	},
};

static uint32_t eplist_setbuf(void *address, int length)
{
	uint32_t iaddr = (uint32_t)address;

	assert((iaddr & 0x3f) == 0, 0,
	       "usb buffer address %lx not aligned\n", iaddr);
	length <<= EPLIST_NBYTES_SHIFT;
	assert((length & ~EPLIST_NBYTES_MASK) == 0, 0,
	       "usb size 0x%x too big\n", length >> EPLIST_NBYTES_SHIFT);
	return length | ((iaddr >> 6) & EPLIST_OFFSET_MASK);
}

/* This cannot be an initcall, as we need the configuration */
int usb_init(struct usb_device *ud)
{
	struct usbram {
		uint8_t eplist[256]; /* same size as previous code */
		uint8_t ep0_out[64];
		uint8_t setup[64];
		uint8_t ep0_in[64];
		uint8_t filler[64];
		/* next 1.5kB we split in 3 (bulk+bulk+interrupt?) */
		uint8_t b0[512];
		uint8_t b1[512];
		uint8_t b2[512];
	} *usbram = (void *)USBRAM_ADDR;

	struct usb_hw_device *hd = &usb_hw_device;
	struct usb_hw_eplist *eplist = (void *)usbram->eplist;

	ud->hd = hd;
	usb_dev_desc.idVendor = ud->cfg->vendor;
	usb_dev_desc.idProduct = ud->cfg->device;
	usb_dev_desc.bcdDevice = ud->cfg->devrelease;

	/* chapter 11, p. 219 -- pll is already powered up */

	/* use usbram for buffers (64-aligned) and prepare eplist */
	assert(sizeof(*usbram) == 2048, 0, "Fix you structure\n");
	memset(usbram, 0, sizeof(*usbram));
	regs[REG_DATABUFSTART] = (uint32_t)usbram & REG_DATABUFSTART_MASK;

	hd->ep0_out_buf = usbram->ep0_out;
	eplist->ep0_out = eplist_setbuf(hd->ep0_out_buf, 64) | EPLIST_A;
	ud->ep0_out_buffer = hd->ep0_out_buf;
	ud->ep0_out_bsize = 64;

	hd->setup_buf = usbram->setup;
	eplist->setup = eplist_setbuf(hd->setup_buf, 0); /* no len for setup */
	ud->setup_buffer = hd->setup_buf;

	hd->ep0_in_buf = usbram->ep0_in;
	eplist->ep0_in = eplist_setbuf(hd->ep0_in_buf, 18);

	/* Bulk-out and bulk-in: out is already active */
	ud->ep1_out_buffer = usbram->b0;
	ud->ep1_out_bsize = sizeof(usbram->b0);
	eplist->buffers[0] = EPLIST_A |
		eplist_setbuf(ud->ep1_out_buffer, ud->ep1_out_bsize);

	ud->ep1_in_buffer = usbram->b1;
	ud->ep1_in_bsize = sizeof(usbram->b1);
	eplist->buffers[2] =
		eplist_setbuf(ud->ep1_out_buffer, ud->ep1_out_bsize);

	regs[REG_EPLISTSTART] = (uint32_t)eplist;
	hd->eplist = eplist;

	/*
	 * Now everything is configured; enable but not DCON yet
	 */
	regs[REG_DEVCMDSTAT] |= REG_DEVCMDSTAT_DEVEN;

	/* gpio in "detached" state */
	gpio_dir_af(GPIO_NR(0,3), GPIO_DIR_IN, 0, GPIO_AF(1)); /* vbus input */
	gpio_dir_af(GPIO_NR(0,6), GPIO_DIR_OUT, 0, GPIO_AF(1)); /* conn out */
	ud->state = USB_DETACHED;

	return 0;
}

int usb_attach(struct usb_device *ud, int on)
{
	if (on && ud->state == USB_DETACHED) {
		regs[REG_DEVCMDSTAT] |=  REG_DEVCMDSTAT_DCON;
		ud->state = USB_ATTACHED;
	}
	if (!on && ud->state != USB_DETACHED) {
		regs[REG_DEVCMDSTAT] &=  ~REG_DEVCMDSTAT_DCON;
		ud->state = USB_DETACHED;
	}
	return gpio_get(GPIO_NR(0, 3));
}

void usb_setup_reply(struct usb_device *ud, const void *buf, int len)
{
	struct usb_hw_device *hd = ud->hd;
	struct usb_hw_eplist *eplist = hd->eplist;
	uint32_t val;

	if (!len) {
		/* No reply but write eplist (p 235/521)  */
		val = eplist_setbuf(hd->ep0_out_buf, 64);
		eplist->ep0_out = EPLIST_S | val;
		val = eplist_setbuf(hd->ep0_in_buf, 0);
		eplist->ep0_in = EPLIST_A | EPLIST_S | val;
		return;
	}

	assert(len <= 64, 0, "Setup reply won't fit buffer (%i > 64)\n",
	       len);
	if (buf != hd->ep0_in_buf)
		memcpy(hd->ep0_in_buf, buf, len);
	val = eplist_setbuf(hd->ep0_in_buf, len);
	/* Setting eplist forces a send of the frame */
	eplist->ep0_in = EPLIST_A | EPLIST_S | val;
}

static void usb_handle_setup(struct usb_device *ud, uint32_t cmdstat)
{
	struct usb_hw_device *hd = ud->hd;
	uint8_t *buf = hd->ep0_in_buf;
	struct usb_setup *s = hd->setup_buf;
	struct usb_hw_eplist *eplist = hd->eplist;
	uint32_t val;

	/* Clear active and stall in both EP0 command/status word */
	if (eplist->ep0_in & (EPLIST_S)) {
		eplist->ep0_in = 0;
	}
	if (eplist->ep0_out & (EPLIST_S)) {
		if (eplist->ep0_out & EPLIST_A) {
			/* disable it first */
			regs[REG_EPSKIP] = 0x01; /* ep0_out is index 0 */
			while (regs[REG_EPSKIP] & 0x01)
				;
			eplist->ep0_out = 0;
		}
	}
	if (!(eplist->ep0_out & (EPLIST_A))) {
		eplist->ep0_out = eplist_setbuf(hd->ep0_out_buf, 64)
			| EPLIST_A; /* must be ready for next setup frame */
	}

	/* Clear intonnak */
	cmdstat &= ~(REG_DEVCMDSTAT_INTNAK_CO | REG_DEVCMDSTAT_INTNAK_CO);
	regs[REG_DEVCMDSTAT] = cmdstat;

	/* select the action */
	if ((s->bRequestType & 0x60) != 0) {
		/* class or vendor */
		if (ud->setup_cb) {
			ud->setup_cb(ud, ud->setup_buffer, 8, 0);
			return;
		}
		printf("ERROR: request %02x and no handler\n",
		       s->bRequestType);
		return;
	}

	if (s->bRequest == USB_REQ_GET_DESCRIPTOR) {
		if ((s->wValue >> 8) == USB_DT_DEVICE) {
			/*
			 * We got first setup frame (80 06 00 01 00 00 40 00)
			 * This is "get descriptor", "device", 0, 0x40 bytes.
			 */
			memcpy(buf, &usb_dev_desc, sizeof(usb_dev_desc));
			usb_setup_reply(ud, buf, s->wLength);
			return;
		}
		if ((s->wValue >> 8) == USB_DT_CONFIG) {
			uint8_t *target = buf;
			/* Get descriptors: fill the whole 32 byte thing */
			memcpy(target, &usb_cfg_desc, sizeof(usb_cfg_desc));
			target += sizeof(usb_cfg_desc);
			memcpy(target, &usb_if_desc, sizeof(usb_if_desc));
			target += sizeof(usb_if_desc);
			/* Next is an array, so no "&" is there */
			memcpy(target, usb_ep_desc, sizeof(usb_ep_desc));
			target += sizeof(usb_ep_desc);
			assert(target - buf == usb_cfg_desc.wTotalLength,
			       0, "Wrong size in datastruct");

			/* Send 9 or 32, according to the request */
			usb_setup_reply(ud, buf, s->wLength);
			return;
		}
	}

	if (s->bRequest == USB_REQ_SET_ADDRESS) {
		/* set address: caller will use ud->addr to complete */
		ud->addr = s->wValue;
		usb_setup_reply(ud, NULL, 0);
		return;
	}

	if (s->bRequest == USB_REQ_SET_CONFIGURATION) {
		/* like above: accept and send no data back */
		val = eplist_setbuf(hd->ep0_out_buf, 64);
		eplist->ep0_out = EPLIST_S | val;
		val = eplist_setbuf(hd->ep0_in_buf, 0);
		eplist->ep0_in = EPLIST_A | EPLIST_S | val;
		ud->state = USB_CONFIGURED;
		return;
	}

	printf("Unhandled setup request %02x %02x\n",
	       s->bRequestType, s->bRequest);
}

int usb_poll(struct usb_device *ud)
{
	struct usb_hw_device *hd = ud->hd;
	struct usb_hw_eplist *eplist = hd->eplist;
	static uint32_t prev_cmdstat, prev_info, prev_intstat;
	static int iterations;
	int len;

	uint32_t cmdstat = regs[REG_DEVCMDSTAT];
	uint32_t info = regs[REG_INFO];
	uint32_t intstat = regs[REG_INTSTAT];

	iterations++;
	/*
	 * Trivial very-verbose diagnostics
	 */
	if (0) {
		if (cmdstat != prev_cmdstat) {
			printf("%i: CMDSTAT %08lx (a %li en %i setup %i)\n",
			       iterations, cmdstat,
			       cmdstat & REG_DEVCMDSTAT_DEVADDR_MASK,
			       cmdstat & REG_DEVCMDSTAT_DEVEN ? 1 : 0,
			       cmdstat & REG_DEVCMDSTAT_SETUP ? 1 : 0);
			prev_cmdstat = cmdstat;

		}
		/* Did we get setup? print buffer, then */
		if (cmdstat & REG_DEVCMDSTAT_SETUP) {
			uint8_t *s = hd->setup_buf;
			printf("setup: %02x %02x\n", s[0], s[1]);
		}
		if ((prev_info & ~0x7ff) != (info & ~0x7ff)) {
			printf("%i: INFO %08lx (err %lx, count %li)\n",
			       iterations, info, (info >> 11) & 0xf,
			       info & 0x7ff);
			prev_info = info;
		}
		if (prev_intstat != (intstat & ~0x40000000)) {
			printf("%i: INTS %08lx\n", iterations, intstat);
			prev_intstat = intstat & ~0x40000000;
		}
	}
	if ((info >> 11) & 0xf) { /* report and clear error code */
		if (0)
			printf("Error 0x%lx\n", (info >> 11) & 0xf);
		regs[REG_INFO] = 0;
	}

	/*
	 * Real work
	 */
	if (cmdstat & REG_DEVCMDSTAT_SETUP) {
		usb_handle_setup(ud, cmdstat);
	}

	if (intstat & 0x4) { /* bulk-out */
		len = (eplist->buffers[0] & EPLIST_NBYTES_MASK)
			>> EPLIST_NBYTES_SHIFT;
		len = ud->ep1_out_bsize - len;
		if (ud->ep1_out_cb)
			ud->ep1_out_cb(ud, ud->ep1_out_buffer, len, 0);
		/* and re-prepare for next iteration */
		eplist->buffers[0] = EPLIST_A |
			eplist_setbuf(ud->ep1_out_buffer, ud->ep1_out_bsize);
	}
	if (intstat & 0x8) { /* bulk-in */
		len = (eplist->buffers[2] & EPLIST_NBYTES_MASK)
			>> EPLIST_NBYTES_SHIFT; /* should be zero */
		if (ud->ep1_in_cb)
			ud->ep1_in_cb(ud, ud->ep1_in_buffer, len, 0);
	}

	/* we must reset some cmdstat bits, leaving enable on. And add addr */
	cmdstat |= ud->addr;
	regs[REG_DEVCMDSTAT] = cmdstat;
	regs[REG_INTSTAT] = intstat; /* same for interrupt */

	return 0;
}

int usb_ep1_in_submit(struct usb_device *ud, void *buf, int len)
{
	struct usb_hw_device *hd = ud->hd;
	struct usb_hw_eplist *eplist = hd->eplist;

	if (buf != ud->ep1_in_buffer)
		memcpy(ud->ep1_in_buffer, buf, len);
	eplist->buffers[2] = EPLIST_A |
		eplist_setbuf(ud->ep1_in_buffer, len);
	return 0;
}
