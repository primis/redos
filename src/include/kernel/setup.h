#ifndef _KERNEL_SETUP_H
#define _KERNEL_SETUP_H

// void vgaInit();
void picInit();
void idtInit();
void pitInit(unsigned int Hz);
#endif
