#ifndef __HW_H__
#define __HW_H__

//extern volatile uint32_t regs[];
#define regs ((volatile uint32_t *)0)

static inline uint32_t readl(unsigned long reg)
{
	return regs[reg / 4];
}
static inline void writel(uint32_t val, unsigned long reg)
{
	regs[reg / 4] = val;
}

static inline uint16_t readw(unsigned long reg)
{
	volatile uint16_t *regs16 = (void *)regs;
	return regs16[reg / 2];
}
static inline void writew(uint16_t val, unsigned long reg)
{
	volatile uint16_t *regs16 = (void *)regs;
	regs16[reg / 2] = val;
}

static inline uint8_t readb(unsigned long reg)
{
	volatile uint8_t *regs8 = (void *)regs;
	return regs8[reg];
}
static inline void writeb(uint8_t val, unsigned long reg)
{
	volatile uint8_t *regs8 = (void *)regs;
	regs8[reg] = val;
}

#endif /* __HW_H__ */
