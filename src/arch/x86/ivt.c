#include <kernel/idt.h>
#include <string.h>
#include <kernel/vga.h>

extern void idt_flush(unsigned int);

static void idtSetGate(unsigned char, unsigned int, unsigned short,
 unsigned char);
void unhandeldInterrupt(unsigned int intNum, ...);
void_callback_arg_t interruptHandlers[256];

idt_entry_t idt[256];
idt_ptr_t   idt_ptr;

static void idtSetGate(unsigned char n, unsigned int base,
 unsigned short selector, unsigned char flags) {
    idt[n].base_low = base & 0xFFFF;
    idt[n].base_high= (base >> 16) & 0xFFFF;
    idt[n].selector = selector;
    idt[n].always0  = 0;
    idt[n].flags    = flags;
}
void interruptHandlerRegister(unsigned int intNum, void_callback_arg_t f) {
    interruptHandlers[intNum] = f;
}

void unhandledInterrupt(unsigned int intNum, ...) {
    vgaWrite("Unhandled Interrupt!");
    for(;;); 
}

void isrHandler(struct regs *r) {
    void_callback_arg_t handler = interruptHandlers[r->int_no];
    handler(r->int_no,r->err_code,r->eax,r->ebx,r->ecx,r->edx,r->edi,r->esi);   
}

void idtInit() {
    int i;
    unsigned int delta;
    delta = (unsigned int) isr1 - (unsigned int) isr0;
    idt_ptr.limit   = sizeof(idt_entry_t) * 256 -1;
    idt_ptr.base    = (unsigned int)&idt;
    memset(&idt, 0, sizeof(idt_entry_t)*256);
    for(i=0;i<128;i++) {
        idtSetGate(i, (unsigned int)isr0 + (delta*i), 0x8, 0x8E);
    }
    for(i=0;i<128;i++) {
        interruptHandlerRegister(i, unhandledInterrupt);
    }
    idt_flush((unsigned int)&idt_ptr);
}
