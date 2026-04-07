; --- Multiboot ---
MB_ALIGN     equ  1 << 0
MB_MEMINFO   equ  1 << 1
MB_MAGIC     equ  0x1BADB002
MB_CHECKSUM  equ -(MB_MAGIC + (MB_ALIGN | MB_MEMINFO))

section .multiboot
align 4
    dd MB_MAGIC
    dd MB_ALIGN | MB_MEMINFO
    dd MB_CHECKSUM

section .bootstrap_stack
align 16
global stack_bottom
stack_bottom:
    dd 0xDEADC0DE      ; O Canário que o C vai vigiar
    resb 16380         ; Restante da stack (16KB total)
stack_top:

section .text
global _start
extern main

_start:
    mov esp, stack_top
    call main          ; Vai para o C
    cli
.hang: hlt
    jmp .hang