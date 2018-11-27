CC=clang
CFLAGS=-O2 -ffreestanding -fno-builtin -nostdlib -Wall -Wextra -march=i686 --target=i686-pc-none-elf
CTESTFLAGS=-DTEST -DDEBUG

test: CFLAGS+=$(CTESTFLAGS)
test_iso: CFLAGS+=$(CTESTFLAGS)

# reference flags for using i686_elf_gcc if clang is not available
# CC=i686_elf_gcc
# CFLAGS=-O2 -ffreestanding -fno-builtin -nostdlib -Wall -Wextra -march=i686

CXX=clang++
CXXFLAGS=-O2 -ffreestanding -fno-builtin -nostdlib -fno-exceptions -fno-rtti -Wall -Wextra -march=i686 --target=i686-pc-none-elf
CXXTESTFLAGS=-DTEST -DDEBUG

test: CXXFLAGS+=$(CXXTESTFLAGS)
test_iso: CXXFLAGS+=$(CXXTESTFLAGS)

AS=nasm
ASFLAGS=-f elf

LDFLAGS=-T link.ld -nostdlib

PROJDIRS := .

AUXFILES := LICENCE README.md grub.cfg makefile

SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.c")
SRCPPFILES := $(shell find $(PROJDIRS) -type f -name "*.cpp")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.h")
HDRPPFILES := $(shell find $(PROJDIRS) -type f -name "*.hpp")
ASMFILES := $(shell find $(PROJDIRS) -type f -name "*.asm")

ALLFILES := $(AUXFILES) $(SRCFILES) $(HDRFILES) $(ASMFILES)

OBJFILES := $(patsubst %.c,%.o,$(SRCFILES)) $(patsubst %.cpp,%.o,$(SRCPPFILES)) $(patsubst %.asm,%.o,$(ASMFILES))
TSTFILES := $(patsubst %.c,%_t,$(SRCFILES)) #Notice NO ASM files included

DEPFILES := $(patsubst %.c,%.d,$(SRCFILES)) $(patsubst %.cpp,%.d,$(SRCPPFILES))
TSTDEPFILES := $(patsubst %,%.d,$(TSTFILES))

all: kernel victoria.iso
.PHONY: all

-include $(DEPFILES) $(TSTDEPFILES)

install:
	@echo Nothing to install
.PHONY: install

dist: victoria.tar

todolist:
	-@for file in $(ALLFILES:makefile=); do fgrep -H -e TODO -e FIXME $$file; done; true

kernel: $(OBJFILES)
	@echo Building Kernel
	@$(CC) $(CFLAGS) $(LDFLAGS) -o kernel *.o -lgcc

victoria.iso: kernel
	@echo Building Iso
	@mkdir -p isodir/boot/grub
	@cp kernel isodir/boot/victoria.bin
	@cp grub.cfg isodir/boot/grub/grub.cfg
	@grub-mkrescue -o victoria.iso isodir

victoria.tar:
	@tar czf victoria.tar $(ALLFILES)

clean:
	-@$(RM) $(wildcard $(OBJFILES) $(DEPFILES) $(TSTFILES) $(TSTDEPFILES) kernel victoria.iso victoria.tar)
	-@$(RM) -rf isodir
.PHONY: clean

test: kernel
	@qemu-system-i386 -kernel kernel
.PHONY: test

test_iso: victoria.iso
	@qemu-system-i386 -cdrom victoria.iso
.PHONY: test_iso

.SUFFIXES: .asm .o

.asm.o:
	$(AS) $(ASFLAGS) -o $*.o $<

%.o: %.c makefile
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

%.o: %.cpp makefile
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@
