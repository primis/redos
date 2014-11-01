#include <kernel/pit.h>
unsigned volatile int ticks;
unsigned int freq;

void pitCallback(unsigned int a, ...) {
    ticks++;
}

void sleep(int seconds) {
    unsigned int finished;
    finished = (ticks + (freq * seconds));
    while(ticks < finished) {
        ;
    }
}

void pitInit(unsigned int Hz) {
    freq = Hz;
    unsigned char low, high;
    asm("cli");
    ticks = 0;
    interruptHandlerRegister(0x20, &pitCallback);
    unsigned int divisor = PIT_BASE_FREQ / Hz;
    outb(PIT_CMD, PIT_CHANNEL_0 | PIT_LHBYTE | PIT_MODE_2 | PIT_BIN_MODE);
    low = (unsigned char)(divisor & 0xFF);
    high= (unsigned char)((divisor >> 8) & 0xFF);
    outb(PIT_DATA_0, low);
    outb(PIT_DATA_0, high);
    clearIRQMask(0);
    asm("sti");
}
