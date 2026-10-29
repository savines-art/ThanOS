# =============================================================================
# Variables

# Build tools
NASM = nasm -felf -g
CC = gcc -std=c99 -m32 -O2 -ffreestanding -no-pie -fno-pie -mno-sse -fno-stack-protector -c -g
LINKER = ld -m elf_i386
OBJCOPY = objcopy -I elf32-i386 -O binary

C_SOURCES   = $(wildcard src/*.c)
C_OBJECTS   = $(patsubst src/%.c,.tmp/%.o,$(C_SOURCES))

ASM_SOURCES = $(filter-out src/bootloader.asm,$(wildcard src/*.asm))
ASM_OBJECTS = $(patsubst src/%.asm,.tmp/%.o,$(ASM_SOURCES))

all: clean build test

.tmp/%.o: src/%.c | .tmp
	$(CC) $< -o $@
	#$(NASM) $< -o $@

.tmp/%.o: src/%.asm | .tmp
	$(NASM) $< -o $@

#.tmp/kernel.o: src/kernel.c
	#$(CC) $(C_SOURCE) -o .tmp/kernel.o

.tmp/bootloader.o: src/bootloader.asm $(C_OBJECTS)
	$(NASM) src/bootloader.asm -o .tmp/bootloader.o -DKERNEL_SIZE=$(shell cat $(C_OBJECTS) | wc -c | tr -d ' ')

#.tmp/memutils.o: src/memeutils.asm
	#$(NASM) src/memutils.asm -o .tmp/memutils.o

.tmp/thanos.elf: $(C_OBJECTS) $(ASM_OBJECTS) .tmp/bootloader.o
	$(LINKER) $(C_OBJECTS) $(ASM_OBJECTS) -T linking.ld -o .tmp/thanos.elf

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
