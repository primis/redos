#ifndef _KERNEL_PORT_H
#define _KERNEL_PORT_H

#include <stdint.h> // So we can use standard types

inline void outb(uint16_t _port, uint8_t _data);
inline uint8_t inb(uint16_t _port);
inline uint16_t inw(uint16_t _port);

#endif

