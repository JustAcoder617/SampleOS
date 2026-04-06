section .bootstrap_stack, nobits
align 16
stack_bottom:
resb 16384 ; 16 KB de espaço para a pilha
stack_top:

section .text
    global _start
    extern main

_start:
    ; Configura o ponteiro da pilha ANTES de chamar o C
    mov esp, stack_top

    call main

    ; Se o C retornar, para a CPU
    cli
.hang:
    hlt
    jmp .hang