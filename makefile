CC=gcc
CFLAGS=-m32 -c

AS=nasm
ASFLAGS=-f elf

LDFLAGS=-m elf_i386 -T link.ld

all: kernel
.PHONY: all

install:
	echo Nothing to install
.PHONY: install

kernel: base.o kernel.o com0.o lpt0.o
	ld $(LDFLAGS) -o kernel *.o

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
