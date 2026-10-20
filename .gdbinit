target remote localhost:1234
set disassembly-flavor intel
symbol-file .tmp/thanos.elf
set arch i8086
b *0x7C00
c
b kernel_entry
b malloc_undead
b print_char
b print_hex
c
layout src
