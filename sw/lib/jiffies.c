#include <init.h>
#include <time.h>
#include <io.h>

static int timer_setup(void)
{
	regs[REG_AHBCLKCTRL] |= 0xffff; //REG_AHBCLKCTRL_CT32B1;

	/* enable timer 1, and count at HZ Hz (e.g.  1000) */
	regs[REG_TMR32B1TCR] = 1;
	regs[REG_TMR32B1TCR] = 3;
	regs[REG_TMR32B1TCR] = 1;
	regs[REG_TMR32B1PR] = (CPU_FREQ / HZ) - 1;
	return 0;
}

core_initcall(timer_setup);

