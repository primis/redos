;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;              Red OS               ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;      IDT Related Assembly Code      ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
[BITS 32]
[GLOBAL idt_flush]
[EXTERN isrHandler]
[EXTERN irqHandler]

%macro ISR_NOERRCODE 1
    [GLOBAL isr%1]
    isr%1:
        cli
        push 0
        push %1
        jmp 0x08:isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
    [GLOBAL isr%1]
    isr%1:
        cli
        nop
        nop
        push %1
        jmp 0x08:isr_common_stub
%endmacro

%macro IRQ 2
    [GLOBAL irq%2]
    irq%2:
        cli
        push 0
        push %1
        jmp 0x08:irq_common_stub
%endmacro

isr_common_stub:
    pusha
    mov eax, ds
    push eax
    mov eax, 0x10
    mov ds, eax
    mov es, eax
    mov fs, eax
    mov gs, eax
    mov ebp, esp
    sub esp, 4
    and esp, 0xFFFFFFF0      ; SVR4 Compat
    mov [esp], ebx
    call isrHandler
    mov esp, ebx
    pop eax
    mov ds, eax
    mov es, eax
    mov fs, eax
    mov gs, eax
    popa
    sti
    add esp, 8
    iret

irq_common_stub:
    pusha
    mov eax, ds
    push eax
    mov eax, 0x10
    mov ds, eax
    mov es, eax
    mov fs, eax
    mov gs, eax
    mov ebx, esp
    sub esp, 4
    and esp, 0xFFFFFFF0
    mov [esp], ebx
    call irqHandler
    mov esp, ebx
    pop eax
    mov ds, eax
    mov es, eax
    mov fs, eax
    mov gs, eax
    popa
    add esp, 8
    sti
    iret

idt_flush:
    mov eax, [esp + 4]
    lidt [eax]
    sti
    ret

%assign i 0
%rep 8
    ISR_NOERRCODE i
    %assign i i+1
%endrep

ISR_ERRCODE   8
ISR_NOERRCODE 9
%assign i 10
%rep 5
    ISR_ERRCODE i
    %assign i i+1
%endrep
%rep 17
    ISR_NOERRCODE i
    %assign i i+1
%endrep
%rep 16
    %assign j i-32
    IRQ i, j
    %assign i i+1
%endrep

%rep 80
    ISR_NOERRCODE i
    %assign i i+1
%endrep
