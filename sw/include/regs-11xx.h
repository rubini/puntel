#ifndef __REGS_11XX_H__
#define __REGS_11XX_H__
/*
 * 11xx and 13xx registers are mostly the same
 *
 * The main difference is in naming: uart0 vs. uart, ssp0 vs. ssp.
 * And the gpio cell, which is completely different.
 */
#include <regs-common.h>

#define REGBASE_SPI0		(0x40040000 / 4)
#define REGBASE_SPI1		(0x40058000 / 4)

#define USBRAM_ADDR 0x20004000

/* usb in 11xx is different from usb in 13xx */
#define REG_DEVCMDSTAT		(0x40080000 / 4)
#define REG_DEVCMDSTAT_DEVADDR_MASK	     0x7f
#define REG_DEVCMDSTAT_DEVEN		(1 <<  7)
#define REG_DEVCMDSTAT_SETUP		(1 <<  8)
#define REG_DEVCMDSTAT_PLLON		(1 <<  9)
#define REG_DEVCMDSTAT_LPMSUP		(1 << 11)
#define REG_DEVCMDSTAT_INTNAK_CO	(1 << 14)
#define REG_DEVCMDSTAT_INTNAK_CI	(1 << 15)
#define REG_DEVCMDSTAT_DCON		(1 << 16)
#define REG_DEVCMDSTAT_DSUS		(1 << 17)
#define REG_DEVCMDSTAT_VBUS		(1 << 28)

#define REG_INFO		(0x40080004 / 4)
#define REG_INFO_FRAMENR_MASK		0x07ff
#define REG_INFO_ERRCODE_MASK		0x7800 /* 0 == noerror */
#define REG_INFO_ERRCODE_SHIFT		11

#define REG_EPLISTSTART		(0x40080008 / 4) /* 256-aligned */
#define REG_DATABUFSTART	(0x4008000c / 4) /* 4M-aligned */
#define REG_DATABUFSTART_MASK	 0xffc00000
#define REG_LPM			(0x40080010 / 4)
#define REG_EPSKIP		(0x40080014 / 4)
#define REG_EPINUSE		(0x40080018 / 4) /* for double-buffer */
#define REG_EPBUFCFG		(0x4008001c / 4) /* single/double buffer */
#define REG_INTSTAT		(0x40080020 / 4)
#define REG_INTEN		(0x40080024 / 4)
#define REG_INTSETSTAT		(0x40080028 / 4)
#define REG_INTROUTING		(0x4008002c / 4)
/* nothing at 0x30 */
#define REG_EPTOGGLE		(0x40080034 / 4)

/* bits for the eplist data words */
#define EPLIST_A		(1 << 31) /* active */
#define EPLIST_D		(1 << 30) /* disabled  */
#define EPLIST_S		(1 << 29) /* stall */
#define EPLIST_TR		(1 << 28) /* toggle reset */
#define EPLIST_TV		(1 << 27) /* toggle value; same as RF */
#define EPLIST_RF		(1 << 27) /* same as TV (rate-fb for int) */
#define EPLIST_T		(1 << 26) /* type 1 = isochronous */
#define EPLIST_NBYTES_MASK	0x03ff0000
#define EPLIST_NBYTES_SHIFT	16
#define EPLIST_OFFSET_MASK	0x0000ffff
#define EPLIST_OFFSET_SHIFT	0

#endif /* __REGS_11XX_H__ */
