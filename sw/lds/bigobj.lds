/*
 * This is used to generate the intermediate .o from all objects.
 */
SECTIONS
{
	.rodata : {
		*(.rodata*);
		. = ALIGN(8);
		initcall_begin = .;
		*(.init1);
		*(.init2);
		*(.init3);
		*(.init4);
		*(.init5);
		*(.init6);
		*(.init7);
		*(.init8);
		initcall_end = .;
	}
	.task : {
		__task_begin = .;
		KEEP(*(.task0))
		KEEP(*(.task))
		__task_end = .;
	}
}
