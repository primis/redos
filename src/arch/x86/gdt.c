#include <kernel/gdt.h>

extern void gdt_flush(unsigned int);

void gdtSetGate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);

gdt_entry_t gdt[5];
gdt_ptr_t   gdtPointer;

void gdtInit() 
{
    gdtPointer.limit = (sizeof(gdt_entry_t)*5) - 1;
    gdtPointer.base  = (uint32_t)&gdt;
    
    gdtSetGate(0, 0, 0, 0, 0);
    gdtSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdtSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdtSetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdtSetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    gdt_flush((uint32_t)&gdtPointer);
}

void gdtSetGate
(int32_t n, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[n].base_low     = (base & 0xFFFF);
    gdt[n].base_mid     = (base >> 16) & 0xFF;
    gdt[n].base_high    = (base >> 24) & 0xFF;
    gdt[n].limit_low    = (limit & 0xFFFF);
    gdt[n].granularity  = ((limit >> 16) & 0x0F);
    gdt[n].granularity  |= gran & 0xF0;
    gdt[n].access       = access;
}

