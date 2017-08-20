#include <stdarg.h>
#include <panic.h>
#include <time.h>
#include <io.h>
#include <board.h>

#define TICK_DELAY (250 * 1000) /* on and off: two iterations per second */

void panic_leds(unsigned ledvalue)
{
	int i;

	for (i = 0; i < 4; i++) { /* two seconds of red-only */
#if 0 /* no leds here */
		gpio_set(LED_R, 0);
		udelay(TICK_DELAY);
		gpio_set(LED_R, 1);
		udelay(TICK_DELAY);
#endif
	}

	/* Now spit off the number, LSB first. A whole number of bytes */
	do {
		for (i = 0; i < 8; i++) {

#if 0 /* We have no diag leds here */
			/* red on, yellow (clock) on, green = bit */
			gpio_set(LED_R, 0);
			gpio_set(LED_Y, 0);
			gpio_set(LED_G, !(ledvalue & 1));
			udelay(TICK_DELAY);

			/* all off */
			gpio_set(LED_R, 1);
			gpio_set(LED_Y, 1);
			gpio_set(LED_G, 1);
#endif
			udelay(TICK_DELAY);
			ledvalue >>= 1;
		}
	} while (ledvalue);
}

void panic(unsigned ledvalue, const char *fmt, ...)
{
	va_list args;

	while (1) {
		printf("Panic: ");
		va_start(args, fmt);
		vprintf(fmt, args);
		va_end(args);

		panic_leds(ledvalue);
	}
}

/* Lazily, assert goes here too */

void __assert(char *func, int line, int ledvalue, int forever,
		     char *fmt, ...)
{
	va_list args;

	do {
		printf("Assertion failed (%s:%i)", func, line);
		if (fmt && fmt[0]) {
			printf(": ");
			va_start(args, fmt);
			vprintf(fmt, args);
			va_end(args);
		} else {
			printf(".\n");
		}

		panic_leds(ledvalue);
	} while (forever);
}
