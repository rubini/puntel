#include <io.h>
#include <time.h>
#include <string.h>
#include <board.h>
#include <neopixel.h>


/* Blink all of them (8 digits = 56 boards = 280 leds) */

uint8_t npvals[8 * 7 * 5 * 3];

void main(void)
{
	int i, coloff = 0;
	unsigned long j = jiffies + HZ/2;

	gpio_dir_af(GPIO_NEOPIXEL, GPIO_DIR_OUT, 0, GPIO_AF_GPIO);

	while (1) {
		memset(npvals, 0, sizeof(npvals));
		for (i = coloff; i < sizeof(npvals); i += 3)
			npvals[i] = 0x10;
		neopix_array(npvals, sizeof(npvals), 1);

		coloff++;
		if (coloff >= 3)
			coloff = 0;
		while (time_before(jiffies, j))
			;
		j += HZ/2;
	}
}
