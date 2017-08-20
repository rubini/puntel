#include <init.h>
#include <time.h>

#if XTAL_FREQ != 12 * 1000 * 1000
#error "This code only works with 12MHz xtals"
#endif

/* Program CPU PLL and USB PLL */
static int pll_init(void)
{
	int m, msel, p, psel;
	int fcco_min = 156 * 1000 * 1000;
	int fcco_max = 320 * 1000 * 1000;
	int fout;

	fout = CPU_FREQ; /* xtal * PLL_CPU */
	m = CONFIG_PLL_CPU;
	msel = m - 1;

	/* find value for P */
	for (p = 2, psel = 0; p < 16; p *= 2, psel++) {
		if (fout * p < fcco_min)
			continue;
		if (fout * p > fcco_max)
			continue; /* can't happen, I hope */
		break;
	}

	/* power up oscillator (FIXME: is it down?) */
	regs[0x40048238/4] = regs[0x40048238/4] & ~(1<<5);

	/* setting the system oscillator: board-dependent (xtal o clkin) */
	regs[REG_SYSOSCCTRL] = BOARD_SYSOSCCTRL;

	 /* a little wait */
	{ volatile int i; for (i=0; i<300; i++);}

	regs[REG_SYSPLLCLKSEL] = 1; /* SYSOSC */
	if (CONFIG_CPU_IS_11U35) {
		/* 1347 does *not* have REG_SYSPLLCLKUEN, but 1343 does! */
		regs[REG_SYSPLLCLKUEN] = 0;
		regs[REG_SYSPLLCLKUEN] = 1;
		while((regs[REG_SYSPLLCLKUEN] & 1) == 0)
			;
	}
	regs[REG_SYSPLLCTRL] = (psel << 5) | msel;

	/* power up pll, which is down by default */
	regs[0x40048238/4] = regs[0x40048238/4] & ~(1<<7);

	while (regs[REG_SYSPLLSTAT] == 0) /* wait for the pll lock */
		;

	regs[REG_MAINCLKSEL] = 3 /* SYSPLLOUT */;
	if (CONFIG_CPU_IS_11U35) {
		/* 1347 does *not* have REG_MAINCLKUEN, but 1343 does! */
		regs[REG_MAINCLKUEN] = 0;
		regs[REG_MAINCLKUEN] = 1;
		while((regs[REG_MAINCLKUEN] & 1) == 0)
			;
	}

	/*
	 * USB PLL, similar to above
	 */
	regs[REG_SYSAHBCLKCTRL] |=
		REG_AHBCLKCTRL_USBREG | REG_AHBCLKCTRL_USBRAM;


	/* power down pll and pads before changing divisors */
	regs[REG_PDRUNCFG] |=
		(REG_PDRUNCFG_USBPLL | REG_PDRUNCFG_USBPAD);

	regs[REG_USBPLLCLKSEL] = 1; /* SYSOSC */
	if (CONFIG_CPU_IS_11U35) {
		regs[REG_USBPLLCLKUEN] = 0;
		regs[REG_USBPLLCLKUEN] = 1;
		while((regs[REG_USBPLLCLKUEN] & 1) == 0)
			;
	}
	psel = 1; msel = 3; /* 2p = 4:    12 -> 192 -> 48 */
	regs[REG_USBPLLCTRL] = (psel << 5) | msel;

	/* power up pll and pads */
	regs[REG_PDRUNCFG] &=
		~(REG_PDRUNCFG_USBPLL | REG_PDRUNCFG_USBPAD);

	while (regs[REG_USBPLLSTAT] == 0) /* wait for the pll lock */
		;

	regs[REG_USBCLKDIV] = 1;
	regs[REG_USBCLKSEL] = 0; /* PLL */
	udelay(100 * 1000);
	regs[REG_USBCLKUEN] = 0;
	regs[REG_USBCLKUEN] = 1;
	udelay(100 * 1000);
	return 0;
}


core_initcall(pll_init);
