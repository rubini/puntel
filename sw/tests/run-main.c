#include <io.h>
#include <time.h>
#include <string.h>
#include <board.h>
#include <neopixel.h>


/* Run a white spot throgh the strip */
uint8_t npvals[8 * 7 * 5 * 3];

void main(void)
{
	int ledoff = 0;
	unsigned long j = jiffies + HZ/2;

	gpio_dir_af(GPIO_NEOPIXEL, GPIO_DIR_OUT, 0, GPIO_AF_GPIO);

	while (1) {
		uint8_t *p;

		memset(npvals, 0, sizeof(npvals));

		p = npvals + 3 * ledoff;
		p[0] = p[1] = p[2] = 0x80;
		neopix_array(npvals, sizeof(npvals), 1);

		ledoff++;
		if (3 * ledoff > sizeof(npvals))
			ledoff = 0;
		while (time_before(jiffies, j))
			;
		j += HZ/50;
	}
}
