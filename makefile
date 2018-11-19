CC=clang
CFLAGS=-O2 -ffreestanding -fno-builtin -nostdlib -nostdinc -Wall -Wextra -march=i686 --target=i686-pc-none-elf

CXX=clang++
CXXFLAGS=-O2 -ffreestanding -fno-builtin -nostdlib -nostdinc -nostdinc++ -Wall -Wextra -march=i686 --target=i686-pc-none-elf

AS=nasm
ASFLAGS=-f elf

LDFLAGS=-T link.ld

all: kernel
.PHONY: all

install:
	echo Nothing to install
.PHONY: install

kernel:
	$(AS) $(ASFLAGS) *.asm
	$(CC) $(CFLAGS) $(LDFLAGS) -o kernel *.c *.o

clean:
	echo Cleaning
	-rm *.o
.PHONY: clean

clean_output: clean
	echo Cleaning artefacts
	-rm kernel
.PHONY: clean_output

test: all
	qemu-system-i386 -kernel kernel
.PHONY: test

.SUFFIXES: .asm .o

.asm.o:
	$(AS) $(ASFLAGS) -o $*.o $<
