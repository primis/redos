################################################################################
## Red OS Kernel Makefile - Updated 10/27/2014 (primis)	                      ##
################################################################################

X86_C_SOURCES = $(shell ls arch/x86/*.c) 
X86_S_SOURCES = $(shell ls arch/x86/*.s)
X86_OBJECTS   = $(X86_S_SOURCES:.s=.o) $(X86_C_SOURCES:.c=.o) 

LIBC_SOURCES = $(shell ls libc/*.c)
LIBC_OBJECTS = $(LIBC_SOURCES:.c=.o)

CORE_SOURCES = $(shell ls core/*.c)
CORE_OBJECTS = $(CORE_SOURCES:.c=.o)

# Kernel Makefile
LD		= i586-elf-ld
CC		= i586-elf-gcc
AS		= nasm
STRIP   = i586-elf-strip

#### Flags ####
CFLAGS	= -ffreestanding -c -I./include
LDFLAGS	= -Tlink.ld
ASFLAGS	= -felf

#### Targets ####
all: $(X86_OBJECTS) $(CORE_OBJECTS) $(LIBC_OBJECTS) link
clean:
	find . -type f -name '*.o' -exec rm {} +
link:
	$(LD) $(LDFLAGS) -o sys.mod $(X86_OBJECTS) $(CORE_OBJECTS) $(LIBC_OBJECTS)
	$(STRIP) --strip-all sys.mod
.c.o:
	$(CC) $(CFLAGS) $< -o $@
.s.o:
	$(AS) $(ASFLAGS) $< -o $@
