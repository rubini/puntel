#include <stringify.h>
#include <time.h>
#include <neopixel.h>
#include <board.h>

#define CPU_FREQ_S		__stringify(CPU_FREQ)

/*
 * Calculations here are based on ideas set forth in
 * http://wp.josh.com/2014/05/13/
 *     ws2812-neopixels-are-not-so-finicky-once-you-get-to-know-them/
 *
 *   Symbol     Parameter                     Min   Typical   Max
 *    T0H     0 code ,high voltage time       200     350      500
 *    T1H     1 code ,high voltage time       550     700     5500
 *    TLD     data, low voltage time          450     600      5000
 *    TLL     latch, low voltage time        6000
 */

void neopix_reset(void)
{
	NEOPIX_LOWER();
	udelay(15);
	return;
}

static __attribute__((__noinline__)) void bit_1(void)
{
	NEOPIX_RAISE();
	/*
	 * bit is 1: be 550 min.
	 * 1 nop every clock means FREQ / 2M
	 */

	asm(".set __neopixel_count_1, " CPU_FREQ_S " / 1000 / 1000 / 2 + 1\n");
	asm(".rep __neopixel_count_1\n\tnop\n\t.endr\n");
	NEOPIX_LOWER();
}

static __attribute__((__noinline__)) void bit_0(void)
{
	NEOPIX_RAISE();
	/*
	 * bit is 0: 200 min, 500 max.
	 * 1 nop every clock means FREQ / 5M.
	 * But we have "movs, r1, #0" too, and half the writing insn.
	 */
	asm(".set __neopixel_count_0, " CPU_FREQ_S " / 1000 / 1000 / 5 - 1\n");
	asm(".rep __neopixel_count_0\n\tnop\n\t.endr\n");
	NEOPIX_LOWER();
}

static inline void neopix_byte(uint8_t v)
{
	uint8_t i = 0x80;
	do {
		if (v & i)
			bit_1();
		else
			bit_0();
		i >>= 1;
	} while (i);
}

/* please call this with interrupts disabled */
void neopix_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	neopix_byte(g);
	neopix_byte(r);
	neopix_byte(b);
}

/* please call this with interrupts disabled */
void neopix_array(const uint8_t *a, int len, int fire)
{
	while (len--)
		neopix_byte(*(a++));
	if (fire)
		neopix_reset();
}
