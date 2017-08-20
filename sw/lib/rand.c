#include <stdlib.h>

static uint32_t seed = 0xcaffe;

void srand(unsigned int newseed)
{
	seed = newseed;
}

int rand(void)
{
	uint32_t rval;

	/* From uclibc: 11 + 10 + 10 bits */
	seed *= 1103515245;
	seed += 12345;
	rval = (unsigned int) (seed / 65536) % 2048;

	seed *= 1103515245;
	seed += 12345;
	rval <<= 10;
	rval ^= (unsigned int) (seed / 65536) % 1024;

	seed *= 1103515245;
	seed += 12345;
	rval <<= 10;
	rval ^= (unsigned int) (seed / 65536) % 1024;

	return rval;
}
