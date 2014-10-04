SOURCES = start.o main.o vga.o ports.o

# Kernel Makefile
LD		= i586-elf-ld
CC		= i586-elf-gcc
AS		= nasm

#### Flags ####
CFLAGS	= -fno-builtin -c -I./include
LDFLAGS	= -Tlink.ld
ASFLAGS	= -felf

#### Targets ####
all: $(SOURCES) link
clean:
	-rm *.o kernel.mod
link:
	$(LD) $(LDFLAGS) -o kernel.mod $(SOURCES)
.c.o:
	$(CC) $(CFLAGS) $< -o $@
.s.o:
	$(AS) $(ASFLAGS) $< -o $@
