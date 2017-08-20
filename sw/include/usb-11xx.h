#ifndef __USB_11xx_H__
#define __USB_11xx_H__

#ifndef __USB_INT_H__
#  error "Please include <usb-int.h> not the hw-specific header"
#endif

struct usb_hw_eplist {
	uint32_t ep0_out;
	uint32_t setup;
	uint32_t ep0_in;
	uint32_t reserved;
	uint32_t buffers[16]; /* ep 1..4, out0, out1, in0, in1 */
};

struct usb_hw_device {
	void *eplist;
	void *ep0_out_buf;
	void *setup_buf;
	void *ep0_in_buf;
	int state;
};




#endif /* __USB_11xx_H__ */
