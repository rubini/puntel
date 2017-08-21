#include <io.h>
#include <time.h>
#include <string.h>
#include <board.h>
#include <neopixel.h>


/* Count... */
uint8_t npvals[8 * 7 * 5 * 3];

uint8_t codes[] = {0x00, 0x44, 0x6b, 0x6e, 0x5c, 0x3e,
		   0x3f, 0x64, 0x7f, 0x7e, 0x77, 0x08};
void main(void)
{
	int dig, seg, led, code, codeoff = 0;
	unsigned long j = jiffies + HZ/2;

	gpio_dir_af(GPIO_NEOPIXEL, GPIO_DIR_OUT, 0, GPIO_AF_GPIO);

	while (1) {
		uint8_t *p;

		memset(npvals, 0, sizeof(npvals));

		/* do this code in all 8 digits */
		for (dig = 0; dig < 8; dig++) {
			uint8_t *p = npvals + dig * 7 * 5  * 3;

			code = codes[codeoff];
			/* 7 segments */
			for (seg = 0; seg < 7; seg++) {
				/* 5 leds each */
				for (led = 0; led < 5; led++) {
					if (code & 1)
						*p = 0x30; /* green */
					p += 3; /* next led */
				}
				code >>= 1;
			}
		}

		neopix_array(npvals, sizeof(npvals), 1);

		codeoff++;
		if (codeoff >= sizeof(codes))
			codeoff = 0;
		while (time_before(jiffies, j))
			;
		j += HZ/2;
	}
}

