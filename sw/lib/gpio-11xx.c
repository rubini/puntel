/*
 * GPIO interface for LPC-11xx (derived from my work on 1143)
 * Alessandro Rubini, 2011-2012, 2016 -- GNU GPL2 or later
 */
#include <init.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

/*
 * This table is needed to turn gpio number to address. The hairy
 * macros are used to shrink the source code. This is not really
 * needed in 11xx as the iocon registers are laid out in order.
 */
#define CFG_REG(port, bit)  __GPIO_CFG_P ## port ## _ ## bit
#define __A(port, bit)  [GPIO_NR(port,bit)] = CFG_REG(port,bit)
static const uint8_t gpio_addr[] = {
	__A(0, 0), __A(0, 1), __A(0, 2), __A(0, 3), __A(0, 4), __A(0, 5),
	__A(0, 6), __A(0, 7), __A(0, 8), __A(0, 9), __A(0,10), __A(0,11),
	__A(0,12), __A(0,13), __A(0,14), __A(0,15), __A(0,16), __A(0,17),
	__A(0,18), __A(0,19), __A(0,20), __A(0,21), __A(0,22), __A(0,23),
	__A(1, 0), __A(1, 1), __A(1, 2), __A(1, 3), __A(1, 4), __A(1, 5),
	__A(1, 6), __A(1, 7), __A(1, 8), __A(1, 9), __A(1,10), __A(1,11),
	__A(1,12), __A(1,13), __A(1,14), __A(1,15), __A(1,16), __A(1,17),
	__A(1,18), __A(1,19), __A(1,20), __A(1,21), __A(1,22), __A(1,23),
	__A(1,24), __A(1,25), __A(1,26), __A(1,27), __A(1,28), __A(1,29),
	__A(1,30), __A(1,31),
};

#define GPIO_MAX  (ARRAY_SIZE(gpio_addr) - 1)

/* This other table marks the ones where AF0 is swapped with AF1 */
static const uint32_t gpio_weird[] = {
	__GPIO_WEIRDNESS_0, __GPIO_WEIRDNESS_1,
};

/*
 * Initialization of the clock is done at initcall time, so it's automatic
 * whenever a function from this file is used by the application
 */
static int hw_gpio_init(void)
{
	regs[REG_AHBCLKCTRL] |= REG_AHBCLKCTRL_GPIO | REG_AHBCLKCTRL_IOCON;
	return 0;
}
subsys_initcall(hw_gpio_init);

/*
 * What follows is the public interface.
 * Note that only gpio_dir_af() checks the gpio is valid. Other
 * functions are expected to be called often and only after setting the mode.
 */

/* This is a documented part of the API, so offer it */
void gpio_init(void) {}

void gpio_dir(int gpio, int output, int value)
{
	int port = GPIO_PORT(gpio);
	int bit = GPIO_BIT(gpio);
	uint32_t reg;

	if (output)
		gpio_set(gpio, value);

	reg = readl(__GPIO_DIR(port));
	if (output)
		reg |= (1 << bit);
	else
		reg &= ~(1 << bit);

	writel (reg , __GPIO_DIR(port));

	/* After changing the direction we must re-force the value (really?) */
	if (output)
		gpio_set(gpio, value);
}

int gpio_dir_af(int gpio, int output, int value, int afnum)
{
	if (gpio > GPIO_MAX || gpio < 0)
		return -1;

	if (afnum < 2) { /* if weird bit, swap AF0 and AF1 */
		int port = GPIO_PORT(gpio);
		int bit = GPIO_BIT(gpio);
		if (gpio_weird[port] & (1 << bit))
			afnum ^= 1;
	}
	/* First set dir to prevent glitches when moving to AF0 */
	gpio_dir(gpio, output, value);
	writel(afnum | 0x80, /* This 0x80 for "digital mode" */
	       __GPIO_CFG_BASE + gpio_addr[gpio]);
	/* Finally, dir again to force value when moving to gpio-out */
	gpio_dir(gpio, output, value);
	return 0;
}

/* The following functions don't check the gpio value, for speed */
uint32_t __gpio_get(int gpio)
{
	return readl(__GPIO_WORD(gpio)); /* 0 or ~0 */
}

int gpio_get(int gpio)
{
	return __gpio_get(gpio) ? 1 : 0;
}

void __gpio_set(int gpio, uint32_t value)
{
	writel(value, __GPIO_WORD(gpio));
}

void gpio_set(int gpio, int value) /* same as above */
{
	writel(value, __GPIO_WORD(gpio));
}
