/*
 * Initcall masterial
 *  Alessandro Rubini, 2013 GNU GPL2 or later
 */
#ifndef __INIT_H__
#define __INIT_H__

typedef int (*initcall_t)(void);

/* Initcalls for flash builds cannot be merged in bigobj.lds */
extern initcall_t  romcall_begin[],  romcall_end[];
extern initcall_t initcall_begin[], initcall_end[];

/* adapted from <linux/init.h> */
#define __initcall(level,fn) static initcall_t __initcall_ ## fn \
        __attribute__((used, __section__(".init" level))) = fn

#define rom_initcall(fn)        __initcall("0", fn)
#define core_initcall(fn)       __initcall("1", fn)
#define subsys_initcall(fn)     __initcall("2", fn)
#define device_initcall(fn)     __initcall("3", fn)
#define task_initcall(fn)       __initcall("4", fn)
#define late_initcall(fn)       __initcall("5", fn)

#ifdef CONFIG_DEBUG_INITCALL
#define debug_initcall 1
#else
#define debug_initcall 0
#endif


#endif /* __INIT_H__ */
