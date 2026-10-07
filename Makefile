# =============================================================================
# Variables

# Build tools
NASM = nasm -felf
CC = gcc -std=c99 -m32 -O2 -ffreestanding -no-pie -fno-pie -mno-sse -fno-stack-protector -c
LINKER = ld -m elf_i386
OBJCOPY = objcopy -I elf32-i386 -O binary


# =============================================================================
# Tasks

all: clean build test

.tmp/kernel.o: src/kernel.c
	$(CC) src/kernel.c -o .tmp/kernel.o

.tmp/bootloader.o: src/bootloader.asm
	$(NASM) src/bootloader.asm -o .tmp/bootloader.o

.tmp/thanos.elf: .tmp/kernel.o .tmp/bootloader.o
	$(LINKER) .tmp/kernel.o .tmp/bootloader.o -T linking.ld -o .tmp/thanos.elf

.tmp/thanos.bin: .tmp/thanos.elf
	$(OBJCOPY) .tmp/thanos.elf .tmp/thanos.bin

thanos.img: .tmp/thanos.bin
	dd if=/dev/zero of=thanos.img bs=512 count=2880
	dd if=.tmp/thanos.bin of=thanos.img conv=notrunc

build: thanos.img

clean:
	rm -f *.img
	rm -rf .tmp
	mkdir .tmp

test: build
	qemu-system-i386 -cpu pentium2 -m 1g -fda thanos.img -monitor stdio -device VGA

debug: build
	qemu-system-i386 -cpu pentium2 -m 1g -fda thanos.img -monitor stdio -device VGA -s -S &
	gdb

.PHONY: all build clean test debug
