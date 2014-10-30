#ifndef _KERNEL_PS2_H
#define _KERNEL_PS2_H

#include <kernel/idt.h>

#define ScrollLock (uint8_t)0x01
#define NumLock (uint8_t)0x02
#define CapsLock (uint8_t)0x04

int32_t kb_special(uint8_t key);
void    updateLeds(uint8_t led);
void    flushBuffer();
int8_t getchar_int();

#endif
