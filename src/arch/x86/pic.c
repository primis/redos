#include <kernel/arch/x86/pic.h>    /* PIC  Declarations                      */
#include <kernel/arch/x86/idt.h>    /* regs, void_callback_arg_t              */ 
#include <kernel/arch/x86/ports.h>  /* inb, outb                              */

extern void_callback_arg_t interruptHandlers[];

void setIRQMask(int IRQ) 
{
    uint16_t port;
    uint8_t  mask;

    if(IRQ < 8) {                   /* Which PIC do we send to?               */
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQ -= 8;
    }
    mask = inb(port) | (1 << IRQ);  /* Get Mask from PIC then bitset IRQ on   */
    outb(port, mask);
}

void clearIRQMask(int IRQ)
{
    uint16_t port;
    uint8_t  mask;

    if(IRQ < 8) {
        port = PIC1_DATA;           /* Which PIC do we send to?               */
    } else {
        port = PIC2_DATA;
        IRQ -= 8;
    }
    mask = inb(port) & ~(1 << IRQ); /* Get mask & unset the IRQ's Bit         */
    outb(port, mask);
}

void picInit()
{
    uint8_t offset1 = 0x20;     /* Vector Table Offsets for the two PICs      */
    uint8_t offset2 = 0x28; 

/*  Init sequence starts with ICW1, then iterates through till ICW4           */
    outb(PIC1_CMD, PIC_INIT);
    outb(PIC2_CMD, PIC_INIT);

    outb(PIC1_DATA, offset1);   /* ICW2: Vector Table Offsets                 */
    outb(PIC2_DATA, offset2);

    outb(PIC1_DATA, 0x4);       /* ICW3 Master: Location of Slave PIC         */
    outb(PIC2_DATA, 0x2);       /* ICW3 Slave:  Cascade ID                    */

    outb(PIC1_DATA, ICW4_8086); /* ICW4: Operating Mode                       */ 
    outb(PIC2_DATA, ICW4_8086); 

    outb(PIC1_DATA, 0xFF);      /* Init over, Mask all Interrupts.            */
    outb(PIC2_DATA, 0xFF);
}

void irqHandler(struct regs *r)
{
    if (r->int_no >= 40) {
        outb(PIC2_CMD, PIC_EOI);
    }
    outb(PIC1_CMD, PIC_EOI);
    void_callback_arg_t handler = interruptHandlers[r->int_no];
    handler(r->int_no,r->err_code,r->eax,r->ebx,r->ecx,r->edx,r->edi,r->esi);
}

