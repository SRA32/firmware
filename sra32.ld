MEMORY
{
	ROM (rx)  : ORIGIN = 0x00000000, LENGTH = 1M
	RAM (rwx) : ORIGIN = 0x00100000, LENGTH = 32M
}

SECTIONS
{
	.text :
	{
		_text_start = .;
		*(.text*)
		*(.rodata*)
		. = ALIGN(4);
		_text_end = .;
	} > ROM

	.data : ALIGN(4)
	{
		_data_start = .;
		*(.data*)
		. = ALIGN(4);
		_data_end = .;
	} > RAM
	AT > ROM

	_data_load = LOADADDR(.data);

	.bss (NOLOAD) : ALIGN(4)
	{
		_bss_start = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		_bss_end = .;
	} > RAM
}