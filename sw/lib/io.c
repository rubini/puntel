#include <io.h>

int puts_is_buffered;

static char puts_buffer[CONFIG_PUTS_BUFFER];
static unsigned nr, nw;

void puts_poll(void)
{
	if (nr == nw)
		return;
	if (try_putc(puts_buffer[nr % CONFIG_PUTS_BUFFER]) < 0)
		return;
	nr++;
}

static int _puts(const char *s)
{
	while (*s)
		putc (*s++);
	return 0;
}

static int b_puts(const char *s)
{
	/* prefer new bytes, push ahead nr on overflow and warn*/
	while (*s)
		puts_buffer[nw++ % CONFIG_PUTS_BUFFER] = *s++;
	if (nw - nr > CONFIG_PUTS_BUFFER) {
		nr = nw - CONFIG_PUTS_BUFFER;
		puts_buffer[nr % CONFIG_PUTS_BUFFER] = '!';
	}
	if (0) {
		char b[64];
		sprintf(b, "<b_puts: Now: nr %i nw %i>", nr, nw);
		_puts(b);
	}
	return 0;
}

int uart_puts(const char *s)
{
	if (CONFIG_PUTS_BUFFER > 0 && puts_is_buffered)
		return b_puts(s);
	return _puts(s);
}

int __attribute__((weak,alias("uart_puts"))) puts(const char *s);
