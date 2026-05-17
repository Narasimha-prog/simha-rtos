MEMORY
{
  iram0_0_seg (RX) : org = 0x40080000, len = 0x20000
  dram0_0_seg (RW) : org = 0x3FFB0000, len = 0x20000
}

ENTRY(app_main)

SECTIONS
{
  .text :
  {
    /* The magic fix: include literals before code */
    *(.literal .text .literal.* .text.*)
  } > iram0_0_seg

  .data :
  {
    *(.data)
    *(.rodata)
    *(.rodata.*)
  } > dram0_0_seg

  .bss :
  {
    *(.bss)
    *(COMMON)
  } > dram0_0_seg
}
