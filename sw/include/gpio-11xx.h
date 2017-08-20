/*
 * GPIO interface for LPC-11xx (derived from my work on 1143)
 * Alessandro Rubini, 2011-2012, 2016 -- GNU GPL2 or later
 */
#ifndef __LPC11_GPIO_H__
#define __LPC11_GPIO_H__

/* for gpio_dir() and gpio_dir_af() */
#define GPIO_DIR_IN     0
#define GPIO_DIR_OUT    1

/* for gpio_dir_af()  */
#define GPIO_AF_GPIO    0
#define GPIO_AF(x)      x
#define GPIO_AF_PULLDOWN   0x08
#define GPIO_AF_PULLUP     0x10

/* We have 32 gpio bits per "port", this is hardwired */
#define GPIO_NR(port, bit)	((port) * 32 + (bit))
#define GPIO_PORT(nr)		((nr) / 32)
#define GPIO_BIT(nr)		((nr) % 32)


extern void gpio_init(void);

extern int gpio_dir_af(int gpio, int output, int value, int afnum);
extern void gpio_dir(int gpio, int output, int value);

extern int gpio_get(int gpio);
extern uint32_t __gpio_get(int gpio);

extern void gpio_set(int gpio, int value);
extern void __gpio_set(int gpio, uint32_t value);

/*
 * The following constants and stuff should only be used in gpio.c,
 * but let's export to users who might want to use the internals themselves
 */
#define __GPIO_DIR(port)	(0x50002000 + 4 * (port))
#define __GPIO_DAT(port)	(0x50002100 + 4 * (port))
#define __GPIO_WORD(gpio)	(0x50001000 + 4 * (gpio))

/* The cfg registers for the various pins, even though they are in order */
#define __GPIO_CFG_BASE		0x40044000
#define __GPIO_CFG_P0_0		0x00
#define __GPIO_CFG_P0_1		0x04
#define __GPIO_CFG_P0_2		0x08
#define __GPIO_CFG_P0_3		0x0c
#define __GPIO_CFG_P0_4		0x10 /* open drain */
#define __GPIO_CFG_P0_5		0x14 /* open drain */
#define __GPIO_CFG_P0_6		0x18
#define __GPIO_CFG_P0_7		0x1c
#define __GPIO_CFG_P0_8		0x20
#define __GPIO_CFG_P0_9		0x24
#define __GPIO_CFG_P0_10	0x28
#define __GPIO_CFG_P0_11	0x2c
#define __GPIO_CFG_P0_12	0x30
#define __GPIO_CFG_P0_13	0x34
#define __GPIO_CFG_P0_14	0x38
#define __GPIO_CFG_P0_15	0x3c
#define __GPIO_CFG_P0_16	0x40
#define __GPIO_CFG_P0_17	0x44
#define __GPIO_CFG_P0_18	0x48
#define __GPIO_CFG_P0_19	0x4c
#define __GPIO_CFG_P0_20	0x50
#define __GPIO_CFG_P0_21	0x54
#define __GPIO_CFG_P0_22	0x58
#define __GPIO_CFG_P0_23	0x5c
#define __GPIO_CFG_P1_0		0x60
#define __GPIO_CFG_P1_1		0x64
#define __GPIO_CFG_P1_2		0x68
#define __GPIO_CFG_P1_3		0x6c
#define __GPIO_CFG_P1_4		0x70
#define __GPIO_CFG_P1_5		0x74
#define __GPIO_CFG_P1_6		0x78
#define __GPIO_CFG_P1_7		0x7c
#define __GPIO_CFG_P1_8		0x80
#define __GPIO_CFG_P1_9		0x84
#define __GPIO_CFG_P1_10	0x88
#define __GPIO_CFG_P1_11	0x8c
#define __GPIO_CFG_P1_12	0x90
#define __GPIO_CFG_P1_13	0x94
#define __GPIO_CFG_P1_14	0x98
#define __GPIO_CFG_P1_15	0x9c
#define __GPIO_CFG_P1_16	0xa0
#define __GPIO_CFG_P1_17	0xa4
#define __GPIO_CFG_P1_18	0xa8
#define __GPIO_CFG_P1_19	0xac
#define __GPIO_CFG_P1_20	0xb0
#define __GPIO_CFG_P1_21	0xb4
#define __GPIO_CFG_P1_22	0xb8
#define __GPIO_CFG_P1_23	0xbc
#define __GPIO_CFG_P1_24	0xc0
#define __GPIO_CFG_P1_25	0xc4
#define __GPIO_CFG_P1_26	0xc8
#define __GPIO_CFG_P1_27	0xcc
#define __GPIO_CFG_P1_28	0xd0
#define __GPIO_CFG_P1_29	0xd4
#define __GPIO_CFG_P1_30	0xd8 /* missing */
#define __GPIO_CFG_P1_31	0xdc

/* This is the bitmask of the gpio pins whose function "0" is not the gpio one */
#define __GPIO_WEIRDNESS_0	0x0000fc01
#define __GPIO_WEIRDNESS_1	0x00000000

/*
 * Note that there is more strangeness and asymmetry:
 * - bit 7 must be 1 for AD-able bits (we set it for everyone)
 * - when you turn input to output it forces the _current_ input
 * - some bits are open-drain (to fix the previous bugs for i2c)
 */

#endif /* __LPC11_GPIO_H__ */
