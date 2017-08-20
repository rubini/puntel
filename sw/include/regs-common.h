/*
 * Hardware registers we use, defined for use in the regs[] abstraction
 */
#ifndef __REGS_COMMON_H__
#define __REGS_COMMON_H__

/* system control */
#define REG_SYSMEMREMAP		(0x40048000 / 4)
#define REG_PRESETCTRL		(0x40048004 / 4)
#define REG_SYSPLLCTRL		(0x40048008 / 4)
#define REG_SYSPLLSTAT		(0x4004800c / 4)
#define REG_USBPLLCTRL		(0x40048010 / 4)
#define REG_USBPLLSTAT		(0x40048014 / 4)
#define REG_SYSOSCCTRL		(0x40048020 / 4)
#define REG_WDTOSCCTRL		(0x40048024 / 4)
#define REG_IRCCTRL		(0x40048028 / 4)
#define REG_SYSRESSTAT		(0x40048030 / 4)
#define REG_SYSPLLCLKSEL	(0x40048040 / 4)
#define REG_SYSPLLCLKUEN	(0x40048044 / 4)
#define REG_USBPLLCLKSEL	(0x40048048 / 4)
#define REG_USBPLLCLKUEN	(0x4004804c / 4)

#define REG_MAINCLKSEL		(0x40048070 / 4)
#define REG_MAINCLKUEN		(0x40048074 / 4)
#define REG_SYSAHBCLKDIV	(0x40048078 / 4)
#define REG_SYSAHBCLKCTRL	REG_AHBCLKCTRL /* shorter name, see later */
#define REG_SSP0CLKDIV		(0x40048094 / 4)
#define REG_UARTCLKDIV		(0x40048098 / 4)
#define REG_SSP1CLKDIV		(0x4004809c / 4)
#define REG_TRACECLKDIV		(0x400480ac / 4) /* not on 11ux */
#define REG_SYSTICKCLKDIV	(0x400480b0 / 4) /* not on 11ux */
#define REG_USBCLKSEL		(0x400480c0 / 4)
#define REG_USBCLKUEN		(0x400480c4 / 4)
#define REG_USBCLKDIVN		(0x400480c8 / 4)
#define REG_USBCLKDIV		(0x400480c8 / 4)
   /* ... */
#define REG_USBCLKCTRL		(0x40048198 / 4)
#define REG_USBCLKST		(0x4004819c / 4)
   /* ... */
#define REG_PDRUNCFG		(0x40048238 / 4)
#define REG_PDRUNCFG_USBPLL		(1 <<  8)
#define REG_PDRUNCFG_USBPAD		(1 << 10)



/* uart */
#define REG_U0THR		(0x40008000 / 4) /* write */
#define REG_U0RBR		(0x40008000 / 4) /* read */
#define REG_U0IER		(0x40008004 / 4)
#define REG_U0IIR		(0x40008008 / 4) /* read */
#define REG_U0FCR		(0x40008008 / 4) /* write */
#define REG_U0LCR		(0x4000800c / 4)
#define REG_U0LSR		(0x40008014 / 4)
#define REG_U0LSR_THRE		0x20

#define REG_U0DLL		(0x40008000 / 4) /* when DLAB=1 */
#define REG_U0DLM		(0x40008004 / 4) /* when DLAB=1 */
#define REG_U0FDR		(0x40008028 / 4) /* fractional divider */


/* clock control */
#define REG_AHBCLKCTRL		(0x40048080 / 4)
#define REG_AHBCLKCTRL_SYS	(1 << 0)
#define REG_AHBCLKCTRL_ROM	(1 << 1)
#define REG_AHBCLKCTRL_RAM	(1 << 2)
#define REG_AHBCLKCTRL_FLASHR	(1 << 3)
#define REG_AHBCLKCTRL_FLASHA	(1 << 4)
#define REG_AHBCLKCTRL_I2C	(1 << 5)
#define REG_AHBCLKCTRL_GPIO	(1 << 6)
#define REG_AHBCLKCTRL_CT16B0	(1 << 7)
#define REG_AHBCLKCTRL_CT16B1	(1 << 8)
#define REG_AHBCLKCTRL_CT32B0	(1 << 9)
#define REG_AHBCLKCTRL_CT32B1	(1 << 10)
#define REG_AHBCLKCTRL_SSP0	(1 << 11)
#define REG_AHBCLKCTRL_UART	(1 << 12)
#define REG_AHBCLKCTRL_ADC	(1 << 13)
#define REG_AHBCLKCTRL_USBREG	(1 << 14)
#define REG_AHBCLKCTRL_WDT	(1 << 15)
#define REG_AHBCLKCTRL_IOCON	(1 << 16)
   /* nothing at 17 */
#define REG_AHBCLKCTRL_SSP1	(1 << 18)
   /* ... */
#define REG_AHBCLKCTRL_USBRAM	(1 << 27)

/* counter 0 */
#define REG_TMR32B0TCR		(0x40014004 / 4)
#define REG_TMR32B0TC		(0x40014008 / 4)
#define REG_TMR32B0PR		(0x4001400c / 4)
#define REG_TMR32B0MCR		(0x40014014 / 4)
#define REG_TMR32B0MR0		(0x40014018 / 4)
#define REG_TMR32B0MR1		(0x4001401c / 4)
#define REG_TMR32B0MR2		(0x40014020 / 4)
#define REG_TMR32B0MR3		(0x40014024 / 4)
#define REG_TMR32B0PWMC		(0x40014074 / 4)

/* counter 1 */
#define REG_TMR32B1TCR		(0x40018004 / 4)
#define REG_TMR32B1TC		(0x40018008 / 4)
#define REG_TMR32B1PR		(0x4001800c / 4)

/* SPI: we use base and offset */
#define REGOFF_SSPCR0		(0x000 / 4)
#define REGOFF_SSPCR1		(0x004 / 4)
#define REGOFF_SSPDR		(0x008 / 4)
#define REGOFF_SSPSR		(0x00C / 4)
#define REGOFF_SSPSR_TFE		0x0001
#define REGOFF_SSPSR_TNF		0x0002
#define REGOFF_SSPSR_RNE		0x0004
#define REGOFF_SSPSR_RFF		0x0008
#define REGOFF_SSPSR_BSY		0x0010
#define REGOFF_SSPCPSR		(0x010 / 4)

#endif /*  __REGS_COMMON_H__ */
