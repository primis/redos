#ifndef _KERNEL_IDT_H
#define _KERNEL_IDT_H
#include <kernel/callback.h>

void interuptHandlerRegister(unsigned char, void_callback_arg_t);
void clearIRQMask(int);
void setIRQMask(int);

struct idt_entry_struct
{
    unsigned short base_low;
    unsigned short selector;
    unsigned char  always0;
    unsigned char  flags;
    unsigned short base_high;
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct
{
    unsigned short limit;
    unsigned int   base;
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

struct regs
{
    unsigned int ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};

extern void isr0();
extern void isr1();

#endif
