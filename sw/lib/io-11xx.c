#include <io.h>

void putc(int c)
{
	if (c == '\n')
		putc('\r');
	while ( !(regs[REG_U0LSR] & REG_U0LSR_THRE) )
		;
	regs[REG_U0THR] = c;
}

/* returns negative on failure. But \r\n is two bytes, remember it */
static int pending = -1;
int try_putc(int c)
{

	if ( !(regs[REG_U0LSR] & REG_U0LSR_THRE) )
		return -1;
	if (pending >= 0) {
		regs[REG_U0THR] = pending;
		pending = -1;
		return 0;
	}
	if (c == '\n') {
		pending = c;
		regs[REG_U0THR] = '\r';
		return -1;
	}
	regs[REG_U0THR] = c;
	return 0;
}
