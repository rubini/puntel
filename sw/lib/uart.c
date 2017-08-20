#include <init.h>

static int uart_init(void)
{
	unsigned int val;

	/* Turn on the clock for pin configuration, and gpio too */
	regs[REG_AHBCLKCTRL] |= REG_AHBCLKCTRL_IOCON | REG_AHBCLKCTRL_GPIO;

	/* First fix pin configuration */
#ifdef CONFIG_LPC11xx
	gpio_dir_af(GPIO_NR(0, 18), GPIO_DIR_IN,  0, GPIO_AF(1)); /* 0-18: rx */
	gpio_dir_af(GPIO_NR(0, 19), GPIO_DIR_OUT, 0, GPIO_AF(1)); /* 0-19: tx */
#else
	gpio_dir_af(GPIO_NR(1, 6), GPIO_DIR_IN,  0, GPIO_AF(1)); /* 1-6: rx */
	gpio_dir_af(GPIO_NR(1, 7), GPIO_DIR_OUT, 0, GPIO_AF(1)); /* 1-7: tx */
#endif

	/*
	 * The clock divider must be set before turning on the clock.
	 * We start from 12MHz, undoing the PLL mult, so divide by 6.5:
	 * 12M / 115200 / 16 = 6.510416
	 *
	 */
	regs[REG_UARTCLKDIV] = CONFIG_PLL_CPU; /* Back to 12MHz */

	/* Turn on the clock for the uart */
	regs[REG_AHBCLKCTRL] |= REG_AHBCLKCTRL_UART;

	/* Disable interrupts and clear pending interrupts */
	regs[REG_U0IER] = 0;
	val = regs[REG_U0IIR];
	val = regs[REG_U0RBR];
	val = regs[REG_U0LSR];

	/* Set bit rate: enable DLAB bit and then divisor */
	regs[REG_U0LCR] = 0x80;

	/*
	 * This calculation is hairy: we need 6.5, but the fractional
	 * divisor register makes (1 + A/B) where B is 1..15
	 * 6.510416 = 4 * 1.627604 =~ 4 * 1.625 = 4 * (1+5/8)
	 */
	val = 4;
	regs[REG_U0DLL] = val & 0xff;
	regs[REG_U0DLM] = (val >> 8) & 0xff;
	regs[REG_U0FDR] = (8 << 4) | 5; /* 1 + 5/8 */

	/* clear DLAB and write mode (8bit, no parity) */
	regs[REG_U0LCR] = 0x3;
	regs[REG_U0FCR] = 0x0;
	return 0;
}

rom_initcall(uart_init);

