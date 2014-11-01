#include <kernel/gdt.h>

extern void gdt_flush(unsigned int);

void gdtSetGate(int, unsigned long, unsigned long, unsigned char, unsigned char);

gdt_entry_t gdt[5];
gdt_ptr_t   gdtPointer;

void gdtInit() {
    gdtPointer.limit = (sizeof(gdt_entry_t)*5) - 1;
    gdtPointer.base  = (unsigned int)&gdt;
    
    gdtSetGate(0, 0, 0, 0, 0);
    gdtSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdtSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdtSetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdtSetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    gdt_flush((unsigned int)&gdtPointer);
}

void gdtSetGate(int n, unsigned long base, unsigned long limit, 
 unsigned char access, unsigned char gran) {
    gdt[n].base_low     = (base & 0xFFFF);
    gdt[n].base_mid     = (base >> 16) & 0xFF;
    gdt[n].base_high    = (base >> 24) & 0xFF;
    gdt[n].limit_low    = (limit & 0xFFFF);
    gdt[n].granularity  = ((limit >> 16) & 0x0F);
    gdt[n].granularity  |= gran & 0xF0;
    gdt[n].access       = access;
}

