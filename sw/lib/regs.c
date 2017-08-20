#include <pp-printf.h>

unsigned __regs[8];

void __print_regs(void)
{
	int i;
	for (i = 0; i < 8; i++)
		pp_printf("%08x%c", __regs[i], i == 7 ? '\n' : ' ');
}
