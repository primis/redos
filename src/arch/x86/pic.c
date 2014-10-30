/*
 * pic.c - Initialize the two Programmable Interrupt Controller's to awell
 *         known state. This is needed for hardware interrupts to work properly.
 */

#include <kernel/vga.h>
#include <kernel/idt.h>
#include <kernel/ports.h>

extern void_callback_arg_t interruptHandlers[];

void setIRQMask(int32_t IRQ)
{
    uint16_t port;
    uint8_t  mask;
    
    if(IRQ < 8) {
        port = 0x21;
    } else {
        port = 0xA1;
        IRQ -= 8;
    }
    mask = inb(port) | (1 << IRQ);
    outb(port, mask);
}

void clearIRQMask(int32_t IRQ)
{
    uint16_t port;
    uint8_t  mask;
    
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
    uint16_t masterPIC = 0x20;
    uint16_t slavePIC  = 0xA0; 

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

void irqHandler(struct regs *r)
{
    if (r->int_no >= 40) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
    void_callback_arg_t handler = interruptHandlers[r->int_no];
    handler(r->int_no,r->err_code,r->eax,r->ebx,r->ecx,r->edx,r->edi,r->esi);
}

