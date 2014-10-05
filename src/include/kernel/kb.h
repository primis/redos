#ifndef _KERNEL_KB_H
#define _KERNEL_KB_H

#include <kernel/idt.h>


#define ScrollLock (unsigned char)0x01
#define NumLock (unsigned char)0x02
#define CapsLock (unsigned char)0x04

int kb_special(unsigned char key);
void UpdateLeds(unsigned char led);
void FlushBuffer();
char getchar_int();

#endif
