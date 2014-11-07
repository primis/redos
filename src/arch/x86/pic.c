#include <kernel/vga.h>
#include <kernel/arch/x86/idt.h>
#include <kernel/arch/x86/ports.h>

extern void_callback_arg_t interruptHandlers[];

void setIRQMask(int IRQ) {
    unsigned short port;
    unsigned char mask;

    if(IRQ < 8) {
        port = 0x21;
    } else {
        port = 0xA1;
        IRQ -= 8;
    }
    mask = inb(port) | (1 << IRQ);
    outb(port, mask);
}

void clearIRQMask(int IRQ) {
    unsigned short port;
    unsigned char mask;

    if(IRQ < 8) {
        port = 0x21;
    } else {
        port = 0xA1;
        IRQ -= 8;
    }
    mask = inb(port) & ~(1 << IRQ);
    outb(port, mask);
}

void picInit()
{
    unsigned short masterPIC = 0x20;
    unsigned short slavePIC  = 0xA0;


    outb(masterPIC, 0x11);
    outb(slavePIC, 0x11);

    outb(masterPIC + 1, 0x20);
    outb(slavePIC  + 1, 0x28);

    outb(masterPIC + 1, 4);
    outb(slavePIC  + 1, 2);

    outb(masterPIC + 1, 1);
    outb(slavePIC  + 1, 1);

    outb(masterPIC + 1, 0xFF);
    outb(slavePIC  + 1, 0xFF);
}

void irqHandler(struct regs *r) {
    if (r->int_no >= 40) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
    void_callback_arg_t handler = interruptHandlers[r->int_no];
    handler(r->int_no,r->err_code,r->eax,r->ebx,r->ecx,r->edx,r->edi,r->esi);
}

