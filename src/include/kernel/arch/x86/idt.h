#ifndef _KERNEL_ARCH_X86_IDT_H
#define _KERNEL_ARCH_X86_IDT_H
#include <kernel/callback.h>

#include <stdint.h>

void interuptHandlerRegister(uint8_t, void_callback_arg_t);
void clearIRQMask(int);
void setIRQMask(int);

struct idt_entry_struct {
    uint16_t base_low;
    uint16_t selector;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_high;
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

struct regs {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

extern void isr0(void);
extern void isr1(void);

#endif
