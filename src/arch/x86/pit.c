#include <kernel/pit.h>

volatile uint32_t ticks;
         uint32_t freq;

void pitCallback(uint32_t a, ...)
{
    ticks++;
}

void sleep(int32_t seconds)
{
    uint32_t finished;
    finished = (ticks + (freq * seconds));
    while(ticks < finished) {
        ;
    }
}

void pitInit(uint32_t Hz)
{
    freq = Hz;
    uint8_t low, high;
    asm("cli");
    ticks = 0;
    interruptHandlerRegister(0x20, &pitCallback);
    uint32_t divisor = PIT_BASE_FREQ / Hz;
    outb(PIT_CMD, PIT_CHANNEL_0 | PIT_LHBYTE | PIT_MODE_2 | PIT_BIN_MODE);
    low = (uint8_t)(divisor & 0xFF);
    high= (uint8_t)((divisor >> 8) & 0xFF);
    outb(PIT_DATA_0, low);
    outb(PIT_DATA_0, high);
    clearIRQMask(0);
    asm("sti");
}
