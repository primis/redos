#ifndef _KERNEL_SETUP_H
#define _KERNEL_SETUP_H

#include <stdint.h>

// void vgaInit();
void picInit(void);
void idtInit(void);
void pitInit(uint32_t Hz);
#endif
