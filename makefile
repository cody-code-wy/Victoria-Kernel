CC=clang
CFLAGS=-O2 -ffreestanding -fno-builtin -nostdlib -Wall -Wextra -march=i686 --target=i686-pc-none-elf

# reference flags for using i686_elf_gcc if clang is not available
# CC=i686_elf_gcc
# CFLAGS=-O2 -ffreestanding -fno-builtin -nostdlib -Wall -Wextra -march=i686

CXX=clang++
CXXFLAGS=-O2 -ffreestanding -fno-builtin -nostdlib -fno-exceptions -Wall -Wextra -march=i686 --target=i686-pc-none-elf

AS=nasm
ASFLAGS=-f elf

LDFLAGS=-T link.ld -nostdlib

all: kernel victoria.iso
.PHONY: all

install:
	echo Nothing to install
.PHONY: install

kernel:
	$(AS) $(ASFLAGS) *.asm
	$(CC) $(CFLAGS) $(LDFLAGS) -o kernel *.c *.o -lgcc

victoria.iso: kernel
	mkdir -p isodir/boot/grub
	cp kernel isodir/boot/victoria.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o victoria.iso isodir

clean:
	echo Cleaning
	-rm *.o
	-rm -rf isodir
.PHONY: clean

clean_output: clean
	echo Cleaning artifacts
	-rm kernel
	-rm victoria.iso
.PHONY: clean_output

test: kernel
	qemu-system-i386 -kernel kernel
.PHONY: test

test_iso: victoria.iso
	qemu-system-i386 -cdrom victoria.iso
.PHONY: test_iso

.SUFFIXES: .asm .o

.asm.o:
	$(AS) $(ASFLAGS) -o $*.o $<
