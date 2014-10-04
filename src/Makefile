SOURCES = start.o main.o vga.o ports.o gdt.o string.o ivt.o idt.o pic.o pit.o

# Kernel Makefile
LD		= i586-elf-ld
CC		= i586-elf-gcc
AS		= nasm

#### Flags ####
CFLAGS	= -ffreestanding -c -I./include
LDFLAGS	= -Tlink.ld
ASFLAGS	= -felf

#### Targets ####
all: $(SOURCES) link
clean:
	-rm *.o 
cleanall:
	-rm *.o kernel.mod
link:
	$(LD) $(LDFLAGS) -o kernel.mod $(SOURCES)
.c.o:
	$(CC) $(CFLAGS) $< -o $@
.s.o:
	$(AS) $(ASFLAGS) $< -o $@
