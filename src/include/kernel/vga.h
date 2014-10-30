#ifndef _KERNEL_VGA_H
#define _KERNEL_VGA_H

#include <stdint.h>

void vgaPutChar(int8_t _charecter);
void vgaWrite(int8_t *_string);
void vgaInit(void);
void vgaSetAttribute(int8_t _attribute);
#endif
