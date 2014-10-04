;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;           RED-OS KERNEL           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Starting Point. Multiboot dumps us  ;
; Here because we tell it to in the   ;
;           Symbol table              ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;   MULTIBOOT HEADER SPEC     
;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 
MB_PAGE_ALIGN   equ 1<<0
MB_MEM_INFO     equ 1<<1
MB_MAGIC        equ 0x1BADB002

MB_FLAGS        equ MB_PAGE_ALIGN | MB_MEM_INFO ; Let Mboot know what we need
MB_CHECKSUM     equ -(MB_MAGIC + MB_FLAGS)

[BITS 32]
[GLOBAL mboot]
[GLOBAL start]
[EXTERN main]
[EXTERN code]
[EXTERN bss]
[EXTERN end]
align 4

; Actual Multiboot header location
mboot:
    dd MB_MAGIC
    dd MB_FLAGS
    dd MB_CHECKSUM
    dd mboot
    dd code
    dd bss
    dd end
    dd start

; Kernel Entry Point
start:
    mov esp, K_STACK + 0x8000
    push ebx
    cli
    call main
    cli
    jmp $

section .bss
ALIGN 32
K_STACK:
    resb 0x8000 ; Kernel Stack
