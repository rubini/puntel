#ifndef __TIME_H__
#define __TIME_H__

#define HZ 1000

extern volatile unsigned long jiffies;
extern void udelay(unsigned usec);

/* The following ones come from the kernel, but simplified */
#define time_after(a,b)         \
        ((long)(b) - (long)(a) < 0)
#define time_before(a,b)        time_after(b,a)
#define time_after_eq(a,b)      \
         ((long)(a) - (long)(b) >= 0)
#define time_before_eq(a,b)     time_after_eq(b,a)

#define time_in_range(a,b,c) \
        (time_after_eq(a,b) && \
         time_before_eq(a,c))

#endif /* __TIME_H__ */
