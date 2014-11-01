#ifndef _KERNEL_PORT_H
#define _KERNEL_PORT_H

inline void outb(unsigned short _port, unsigned char _data);
inline unsigned char inb(unsigned short _port);
inline unsigned short inw(unsigned short _port);

#endif

