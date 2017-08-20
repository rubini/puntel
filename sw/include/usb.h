#ifndef __USB_H__
#define __USB_H__

/*
 * This is the API for usb-slave interaction. The hardware driver
 * is limited to only ep0out and ep0in endpoints. Everything matches.
 * I may add ep1 later on, but it's not in current plans.
 */

/* Filled by the caller, before init */
struct usb_config {
	uint16_t vendor;
	uint16_t device;
	uint16_t devrelease; /* bcd */
};

struct usb_device {
	struct usb_config *cfg;

	/* callback pointers */
	int (*setup_cb)(struct usb_device *, void *buf, int len, int error);
	int (*ep1_out_cb)(struct usb_device *, void *buf, int len, int error);
	int (*ep1_in_cb)(struct usb_device *, void *buf, int len, int error);

	/* The following stanza is filled by the hw driver */
	void *hd; /* hardware device */
	int state;
	int addr;
	int ep0_out_bsize;
	int ep1_out_bsize;
	int ep1_in_bsize;
	void *ep0_out_buffer;
	void *ep1_out_buffer;
	void *ep1_in_buffer;
	void *setup_buffer; /* size is 8 */
	unsigned n_in, n_out; /* statistics */
};

enum usb_state {
	USB_DETACHED = 0,
	USB_ATTACHED,
	USB_CONFIGURED,
};

/* setup callback may want to use this */
struct usb_setup {
        uint8_t bRequestType;
        uint8_t bRequest;
        uint16_t wValue;
        uint16_t wIndex;
        uint16_t wLength;
} __attribute__((packed));

/* This configures stuff but keeps it detached */
extern int usb_init(struct usb_device *d);

/* Attaches or detaches. In any case it returns vbus (1 = on) */
extern int usb_attach(struct usb_device *d, int on);

/* Run the state machine, callbacks, etc */
extern int usb_poll(struct usb_device *d);

/* OUT direction  is performed via callback only, IN starts here */
extern int usb_ep1_in_submit(struct usb_device *d, void *buf, int len);

/* the setup callback will need to reply (also used internally) */
extern void usb_setup_reply(struct usb_device *d, const void *buf, int len);

#endif /* __USB_H__ */
