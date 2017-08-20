#ifndef __CPU_H__
#define __CPU_H__

#ifndef __ASSEMBLER__

#include <stdint.h>
#include <hw.h>

#if defined(CONFIG_LPC11xx)
#  include <cpu-11xx.h>
#else
#  error "Unknown processor"
#endif

#define XTAL_FREQ  (12 * 1000 * 1000)
#define CPU_FREQ (XTAL_FREQ * CONFIG_PLL_CPU)


#endif /* __ASSEMBLER__ */
#endif /* __CPU_H__ */

