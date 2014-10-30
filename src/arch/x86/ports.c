#include <stdint.h>

inline void outb(uint16_t _port, uint8_t _data) 
{
    asm volatile("outb %1, %0"
        :
        : "dN"(_port), "a" (_data)
    );
}

inline uint8_t inb(uint16_t _port) 
{
    uint8_t ret;
    asm volatile("inb %1, %0" 
        : "=a" (ret) 
        : "dN" (_port)
    );
    return ret;
}
uint16_t inw(uint16_t _port)
{
    uint16_t ret;
    asm volatile ("inw %1, %0" 
        : "=a" (ret)
        : "dN" (_port)
    );
    return ret;
} 
