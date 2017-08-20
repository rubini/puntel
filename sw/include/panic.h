#ifndef __PANIC_H__
#define __PANIC_H__

/*
 * This is used by assert too, for a warning-only iteration
 * Ledvalue is an integer number being bitbanged on the tile's leds.
 */
extern void panic_leds(unsigned ledvalue);

extern void panic(unsigned ledvalue, const char *fmt, ...)
        __attribute__((format(printf,2,3)));


#endif /* __PANIC_H__ */
