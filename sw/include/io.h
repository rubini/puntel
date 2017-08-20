#include <stdarg.h>

#define NULL 0

extern int uart_puts(const char *s);
extern int puts(const char *s);
extern void putc(int c);

/* buffered puts; needs Kconfig and main must turn put_is_buffered on */
extern int puts_is_buffered;
extern void puts_poll(void);
extern int try_putc(int c);

/* We turn printf to pp_printf and so on. Give "std" prototypes here */
extern int printf(const char *fmt, ...)
	__attribute__((format(printf,1,2)));

extern int sprintf(char *s, const char *fmt, ...)
	__attribute__((format(printf,2,3)));

extern int vprintf(const char *fmt, va_list args);

extern int vsprintf(char *buf, const char *, va_list)
	__attribute__ ((format (printf, 2, 0)));
