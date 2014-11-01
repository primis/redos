#ifndef _KERNEL_VGA_H
#define _KERNEL_VGA_H

void vgaPutChar(char _c);
void vgaWrite(char *_s);
void vgaInit();
void vgaSetAttribute(char a);
#endif
