#include <init.h>
#include <io.h>

static int do_one_initcall(initcall_t *p, int verbose)
{
	int error;

	if (debug_initcall && verbose)
		printf("Calling initcall %p: ", p);

	error = (*p)();

	if (!verbose)
		return error; /* too early: can't report */
	if (!error && !debug_initcall)
		return 0;

	/* error: we may have already printed part of the message */
	if (!debug_initcall)
		printf("initcall at %p: ", p);
	printf("error %i\n", error);
	return error;
}

void do_initcalls(void)
{
	initcall_t *p;

	/* This list is empty for RAM boot */
	for (p = romcall_begin; p < romcall_end; p++)
		do_one_initcall(p, 0);

	for (p = initcall_begin; p < initcall_end; p++)
		do_one_initcall(p, 1);
}

void setup(void) __attribute__((weak, alias("do_initcalls")));
