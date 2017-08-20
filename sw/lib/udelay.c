/*
 * I initially wrote this code for wrpc-sw (ohwr.org)
 *
 * Copyright (C) 2013 CERN (www.cern.ch)
 * Author: Alessandro Rubini <rubini@gnudd.com>
 *
 * Released according to the GNU GPL, version 2 or any later version.
 */
#include <stdint.h>
#include <init.h>
#include <time.h>
#include <io.h>

static int udelay_lpj; /* loops per jiffy */

static __attribute__((__noinline__, aligned(16))) void __delay(int count)
{
	while (count-- > 0)
		asm("");
}

static int verify_lpj(int lpj)
{
	unsigned long j;

	/* wait for the beginning of a tick */
	j = jiffies + 1;
	while (jiffies != j)
		;

	__delay(lpj);

	/* did it expire? */
	j = jiffies - j;
	if (0)
		printf("check %i: %li\n", lpj, j);
	return j;
}

static int generic_udelay_init(void)
{
	int step = 512;
	int lpj = step, test_lpj;

	/* Increase until we get over it */
	while (verify_lpj(lpj) == 0) {
		lpj += step;
		step *= 2;
	}
	/* Ok, now we are over; half again and restart */
	lpj /= 2; step /= 4;

	/* So, *this* jpj is lower, and with two steps we are higher */
	while (step) {
		test_lpj = lpj + step;
		if (verify_lpj(test_lpj) == 0)
			lpj = test_lpj;
		step /= 2;
	}
	udelay_lpj = lpj;
	printf("Loops per jiffy: %i\n", lpj);
	return 0;
}

subsys_initcall(generic_udelay_init);

void udelay(unsigned usec)
{
	/* Sleep 10ms each time, to prevent overlfows */
	const int step = 10 * 1000;
	const uint32_t usec_per_jiffy = 1000L * 1000 / HZ;
	const uint64_t jiffies_per_usec = (1LL<<32) / usec_per_jiffy;
	const int count_per_step = udelay_lpj * step / usec_per_jiffy;

	while (usec > step)  {
		__delay(count_per_step);
		usec -= step;
	}
	/*
	 * We used to have this:
	 *
	 * __delay(usec * udelay_lpj / usec_per_jiffy);
	 *
	 * but we can't afford a 32-bit division: a 64-bit multiply is faster.
	 */
	__delay(((udelay_lpj * usec) * jiffies_per_usec) >> 32);
}
