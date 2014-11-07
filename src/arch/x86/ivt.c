#include <kernel/arch/x86/idt.h>
#include <string.h>
#include <kernel/vga.h>

extern void idt_flush(uint32_t);
static void idtSetGate(uint8_t, uint32_t, uint16_t, uint8_t);
void unhandeldInterrupt(uint32_t intNum, ...);
void_callback_arg_t interruptHandlers[256];
idt_entry_t idt[256];
idt_ptr_t   idt_ptr;

static void idtSetGate(uint8_t n, uint32_t base, uint16_t sel, uint8_t flags)
{   /* Bit Twiddle the parts into the internal CPU format                     */
    idt[n].base_low = base & 0xFFFF;
    idt[n].base_high= (base >> 16) & 0xFFFF;
    idt[n].selector = sel;
    idt[n].always0  = 0;
    idt[n].flags    = flags;
}

void interruptHandlerRegister(uint32_t intNum, void_callback_arg_t function)
{   /* Jump table for calling functions when an interrupt triggers            */
    interruptHandlers[intNum] = function;
}

void unhandledInterrupt(uint32_t intNum, ...)
{   /* Default Case for an interrupt */
    vgaWrite("Unhandled Interrupt!");
    for(;;);
}

void isrHandler(struct regs *r)
{   /* Jump to the handler and pass the registers as arguments                */
    void_callback_arg_t handler = interruptHandlers[r->int_no];
    handler(r->int_no,r->err_code,r->eax,r->ebx,r->ecx,r->edx,r->edi,r->esi);
}

void idtInit()
{
    int i;
    uint32_t delta;     /* Distance between ISR Stubs                         */
    delta         = (uint32_t) isr1 - (uint32_t) isr0;

    idt_ptr.limit = (sizeof(idt_entry_t) * 256)-1;   /*265 interrupt          */
    idt_ptr.base  = (uint32_t)&idt;

    memset(&idt, 0, sizeof(idt_entry_t)*256); /*Clear ISR's to prevent crashes*/

    for(i=0;i<128;i++) {    /*Set ISR to it's stub using a relative pointer   */
        idtSetGate(i, (uint32_t)isr0 + (delta*i), 0x8, 0x8E);
    }

    for(i=0;i<128;i++) {    /* Initialize jump table to default case          */
        interruptHandlerRegister(i, unhandledInterrupt);
    }

    idt_flush((uint32_t)&idt_ptr);  /*Move the new IDT into the CPU register  */
}
