OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_entry_rom)

MEMORY
{
    flash : ORIGIN = 0x00000000, LENGTH = 0x4000
    stack : ORIGIN = 0x10000000, LENGTH = 0x400
    ram :   ORIGIN = 0x10000400, LENGTH = 0x1800 - LENGTH(stack)
};

_fstack = ORIGIN(stack) + LENGTH(stack) - 4;
regs = 0;
jiffies = 0x40018008;


SECTIONS
{
	.text.boot : {
		KEEP(*(.vectors));
		*(.text.romboot);
		*(.text.anyboot);
	} > flash
	.text : {
		*(.text .text.*)
	} > flash
	.rodata : {
		*(.rodata*)
		romcall_begin = .;
		KEEP(*(.init0));
		romcall_end = .;
		. = ALIGN(16);
		_erom = .;
	} > flash

	.data : AT(_erom) {
		. = ALIGN(16);
		_sdata = .;
		*(.task);
		*(.data .data.*);
		. = ALIGN(16);
		*(.ramcode);
		. = ALIGN(16);
		_edata = .;
	} > ram

	.bss : {
		. = ALIGN(16);
		__bss_start = .;
		*(.bss .bss.* COMMON);
		. = ALIGN(16);
		__bss_end = .;
	} > ram
	/DISCARD/ : { *(.text.ramboot); *(.ARM.exidx); }
}

PROVIDE(printf = pp_printf);
PROVIDE(sprintf = pp_sprintf);
PROVIDE(vprintf = pp_vprintf);
PROVIDE(vsprintf = pp_vsprintf);
