#include <kernel/idt.h>
#include <string.h>
#include <kernel/vga.h>

extern void idt_flush(uint32_t);

static void idtSetGate(uint8_t, uint32_t, uint16_t, uint8_t);
void unhandeldInterrupt(uint32_t intNum, ...);
void_callback_arg_t interruptHandlers[256];

idt_entry_t idt[256];
idt_ptr_t   idt_ptr;

static void idtSetGate(uint8_t n, uint32_t base, uint16_t sel, uint8_t flags) 
{
    idt[n].base_low = base & 0xFFFF;
    idt[n].base_high= (base >> 16) & 0xFFFF;
    idt[n].selector = sel;
    idt[n].always0  = 0;
    idt[n].flags    = flags;
}

void interruptHandlerRegister(uint32_t intNum, void_callback_arg_t f) 
{
    interruptHandlers[intNum] = f;
}

void unhandledInterrupt(uint32_t intNum, ...) 
{
    vgaWrite("Unhandled Interrupt!");
    for(;;); 
}

void isrHandler(struct regs *r) 
{
    void_callback_arg_t handler = interruptHandlers[r->int_no];
    handler(r->int_no,r->err_code,r->eax,r->ebx,r->ecx,r->edx,r->edi,r->esi);   
}

void idtInit() 
{
    int32_t      i;
    uint32_t delta;
    delta         = (uint32_t)isr1 - (uint32_t)isr0;
    idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    idt_ptr.base  = (uint32_t)&idt;
    memset(&idt, 0, sizeof(idt_entry_t)*256);
    for(i=0;i<128;i++) {
        idtSetGate(i, (uint32_t)isr0 + (delta*i), 0x8, 0x8E);
    }
    for(i=0;i<128;i++) {
        interruptHandlerRegister(i, unhandledInterrupt);
    }
    idt_flush((uint32_t)&idt_ptr);
}
