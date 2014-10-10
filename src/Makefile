X86SOURCES = arch/x86/start.o arch/x86/vga.o arch/x86/ports.o arch/x86/gdt.o arch/x86/ivt.o arch/x86/idt.o arch/x86/pic.o arch/x86/pit.o arch/x86/cmos.o arch/x86/ps2.o 

LIBCSOURCES = libc/string.o libc/stdio.o

CORESOURCES = core/main.o core/shell.o

# Kernel Makefile
LD		= i586-elf-ld
CC		= i586-elf-gcc
AS		= nasm

#### Flags ####
CFLAGS	= -ffreestanding -c -I./include
LDFLAGS	= -Tlink.ld
ASFLAGS	= -felf

#### Targets ####
all: $(X86SOURCES) $(CORESOURCES) $(LIBCSOURCES) link
clean:
	-rm *.o 
cleanall:
	-rm *.o kernel.mod
link:
	$(LD) $(LDFLAGS) -o kernel.mod $(X86SOURCES) $(CORESOURCES) $(LIBCSOURCES)
.c.o:
	$(CC) $(CFLAGS) $< -o $@
.s.o:
	$(AS) $(ASFLAGS) $< -o $@
