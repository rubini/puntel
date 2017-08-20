/*
 * Trivial string.c, mainly from U-Boot sources
 *
 * Copyright 2010, Alessandro Rubini <rubini@gnudd.com>
 * Copytight 2010, BTicino SpA www.bticino.it
 *
 * Released according to the GNU GPL version 2
 */
#include <string.h>
#include <stdint.h>

char *strcpy(char * d, char *s)
{
	char *res = d;

	while ((*d++ = *s++) != '\0')
		;
	return res;
}

int strlen(const char *s)
{
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}

int strnlen(const char *s, int count)
{
	const char *sc;

	for (sc = s; count-- && *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}

void *memcpy(void *d, const void *s, int count)
{
	intptr_t *dl = (intptr_t *)d, *sl = (intptr_t *)s;
	char *d8, *s8;

	/* while all data is aligned (common case), copy a word at a time */
	if ( (((intptr_t)d | (intptr_t)s) & (sizeof(*dl) - 1)) == 0) {
		while (count >= sizeof(*dl)) {
			*dl++ = *sl++;
			count -= sizeof(*dl);
		}
	}
	/* copy the reset one byte at a time */
	d8 = (char *)dl;
	s8 = (char *)sl;
	while (count--)
		*d8++ = *s8++;

	return d;
}

void * memset(void *s, int c, int count)
{
	intptr_t *sl = (intptr_t *)s;
	unsigned long cl = 0;
	char *s8;
	int i;

	/* do it one word at a time (32 bits or 64 bits) while possible */
	if ( ((intptr_t)s & (sizeof(*sl) - 1)) == 0) {
		for (i = 0; i < sizeof(*sl); i++) {
			cl <<= 8;
			cl |= c & 0xff;
		}
		while (count >= sizeof(*sl)) {
			*sl++ = cl;
			count -= sizeof(*sl);
		}
	}
	/* fill 8 bits at a time */
	s8 = (char *)sl;
	while (count--)
		*s8++ = c;

	return s;
}
