#ifndef _KERNEL_PIT_H
#define _KERNEL_PIT_H

#include <kernel/ports.h>
#include <kernel/arch/x86/idt.h>

void sleep(int);

#define PIT_BASE_FREQ   1193182     // 1.1061816666 MHz

#define PIT_DATA_0      0x40
#define PIT_DATA_1      0x41
#define PIT_DATA_2      0x43
#define PIT_CMD         0x43

#define PIT_BIN_MODE    0x00
#define PIT_BCD_MODE    0x01

#define PIT_MODE_0      0x00
#define PIT_MODE_1      0x02
#define PIT_MODE_2      0x04
#define PIT_MODE_3      0x06
#define PIT_MODE_4      0x08
#define PIT_MODE_5      0x0A

#define PIT_LATCH       0x00
#define PIT_LOBYTE      0x10
#define PIT_HIBYTE      0x20
#define PIT_LHBYTE      0x30

#define PIT_CHANNEL_0   0x00
#define PIT_CHANNEL_1   0x40
#define PIT_CHANNEL_2   0x80
#define PIT_READBACK    0xC0

#endif    
