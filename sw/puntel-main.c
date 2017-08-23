#include <io.h>
#include <time.h>
#include <string.h>
#include <board.h>
#include <neopixel.h>

/* 8 digits, 7 segments, 5 leds per segment, 3 colors per led */
uint8_t npvals[8 * 7 * 5 * 3];

/* pointers to the 8 digits */
uint8_t *digitp[8];

/* the current value of each digit */
uint8_t digitval[8];

/* the color of each digit -- g, r, b -- intensities are  .587, .299, .114*/
uint8_t digitcol[8][3] = {
	{0x10, 0x00, 0x00},
	{0x10, 0x00, 0x00},

	{0x00, 0x10 * .587 / .299, 0x00},
	{0x00, 0x10 * .587 / .299, 0x00},

	{0x00, 0x00, 0x10 * .587 / .114},
	{0x00, 0x00, 0x10 * .587 / .114},

	{0x08, 0x08 * .587 / .299, 0x00},
	{0x08, 0x08 * .587 / .299, 0x00}
};

/* codes for the digits: blank, 1..9, - */
uint8_t codes[] = {0x00, 0x44, 0x6b, 0x6e, 0x5c, 0x3e,
		   0x3f, 0x64, 0x7f, 0x7e, 0x77, 0x08};

static void puntel_draw(int currentd)
{
	int dig, seg, led, code;

	for (dig = 0; dig < 8; dig++) {
		uint8_t *p = digitp[dig];

		code = codes[digitval[dig]];
		/* 7 segments */
		for (seg = 0; seg < 7; seg++) {

			/* 5 leds each */
			for (led = 0; led < 5; led++) {
				if (code & 1)
					memcpy(p, digitcol[dig], 3);
				else
					memset(p, 0, 3);
				p += 3; /* next led */
			}
			code >>= 1;
		}
		/* if this is the current digit, white dot in position 9*/
		if (dig == currentd)
			memset( digitp[dig] + 9 * 3, 0x80, 3);
	}
	neopix_array(npvals, sizeof(npvals), 1);
}

static void puntel_loop(void)
{
	static int currentd = -1, prevb0, prevb1, b0, b1;
	static unsigned long lastpress;
	static int gled;

	/* toggle green led, so I feel safe */
	gpio_set(LED_G, !gled);
	gled = !gled;

	b0 = !gpio_get(0);
	gpio_set(LED_Y, b0);
	if (b0 && !prevb0) {
		/* button 0: increase current digit */
		currentd++;
		if (currentd >= 8)
			currentd = 0;
		lastpress = jiffies;
	}


	b1 = !gpio_get(1);
	gpio_set(LED_R, b1);
	if (b1 && !prevb1) {
		/* button 1: increase value at current digit */
		if (currentd >= 0) {
			digitval[currentd]++;
			if (digitval[currentd] >= sizeof(codes))
				digitval[currentd] = 0;
		}
		lastpress = jiffies;
	}
	prevb0 = b0;
	prevb1 = b1;


	/* If 3s passed, no current digit any more */
	if (currentd >= 0 && time_after(jiffies, lastpress + 3 * HZ))
		currentd = -1;

	puntel_draw(currentd);
}

void main(void)
{
	int i, j;
	unsigned long t;

	/* prepare stuff */
	gpio_dir_af(GPIO_NEOPIXEL, GPIO_DIR_OUT, 0, GPIO_AF_GPIO);

	for (i = 0; i < 8; i++)
		digitp[i] = npvals + (sizeof(npvals) / 8 * i);

	/* blink it all, to show we are alive (and test pixels) */
	for (i = 0; i < 3; i++) {
		t = jiffies + HZ/2;
		memset(npvals, 0, sizeof(npvals));
		for (j = i; j < sizeof(npvals); j +=3)
			npvals[j] = 0x10;
		neopix_array(npvals, sizeof(npvals), 1);
		while (time_before(jiffies, t))
		       ;
	}

	/* configure the two buttons as input, with pull-up */
	gpio_dir_af(0 /* reset */, GPIO_DIR_IN, 0,
		    GPIO_AF_GPIO | GPIO_AF_PULLUP);
	gpio_dir_af(1 /* progr */, GPIO_DIR_IN, 0,
		    GPIO_AF_GPIO | GPIO_AF_PULLUP);

	/* configure the three diag leds as output, briefly on, then off */
	gpio_dir_af(LED_R, GPIO_DIR_OUT, 1, GPIO_AF_GPIO);
	udelay(200 * 1000);
	gpio_dir_af(LED_Y, GPIO_DIR_OUT, 1, GPIO_AF_GPIO);
	udelay(200 * 1000);
	gpio_dir_af(LED_G, GPIO_DIR_OUT, 1, GPIO_AF_GPIO);
	udelay(200 * 1000);
	gpio_set(LED_R, 0); gpio_set(LED_Y, 0); gpio_set(LED_G, 0);

	/* run the state machine, with .1s polling time */
	while (1) {
		t = jiffies + HZ/10;
		puntel_loop();
		while (time_before(jiffies, t))
		       ;
	}



}
