#ifndef __ASSERT_H__
#define __ASSERT_H__

#define CONFIG_HAS_ASSERT 1

extern void __assert(const char *func, int line, int ledvalue, int forever,
		     const char *fmt, ...)
	__attribute__((format(printf, 5, 6)));


#define assert(cond, ledvalue, fmt, ...) \
	if (CONFIG_HAS_ASSERT && !(cond)) \
		__assert(__func__, __LINE__, ledvalue, 1, fmt, ##  __VA_ARGS__)

#define assert_warn(cond, ledvalue, fmt, ...) \
	if (CONFIG_HAS_ASSERT && !(cond)) \
		__assert(__func__, __LINE__, ledvalue, 0, fmt, ##  __VA_ARGS__)


/* ledvalue is an integer number being bitbanged on the tile's leds */
extern void panic(unsigned ledvalue, const char *fmt, ...)
        __attribute__((format(printf,2,3)));

extern void panic_loop(unsigned ledvalue);


#endif /* __ASSERT_H__ */
