inline void outb(unsigned short _port, unsigned char _data) {
    asm volatile("outb %1, %0"
        :
        : "dN"(_port), "a" (_data)
    );
}

inline unsigned char inb(unsigned short _port) {
    unsigned char ret;
    asm volatile("inb %1, %0" 
        : "=a" (ret) 
        : "dN" (_port)
    );
    return ret;
}
unsigned short inw(unsigned short _port)
{
    unsigned short ret;
    asm volatile ("inw %1, %0" 
        : "=a" (ret)
        : "dN" (_port)
    );
    return ret;
} 
