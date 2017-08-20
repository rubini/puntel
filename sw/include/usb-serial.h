#include <usb.h>

struct usbser {
	struct usb_device *ud;
	unsigned long flags;
};

#define USBSER_USER_FLAGS    0xffff
#define USBSER_FLAG_ECHO     0x0001
#define USBSER_FLAG_INITED  0x10000

#ifndef CONFIG_USBSERIAL_BSIZE
#define CONFIG_USBSERIAL_BSIZE 512
#endif

extern struct usbser *usbser_init(struct usbser *);

/*
 * This should be a "file" instead, with generic calls.
 * Meanwhile, the read method also works as usb polling.
 */
extern int usbser_read(struct usbser *us, void *buf, int len);
extern int usbser_gets(struct usbser *us, void *buf, int len);
extern int usbser_write(struct usbser *us, const void *buf, int len);

