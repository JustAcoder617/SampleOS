; boot.asm
%define ALIGN    1 << 0
%define MEMINFO  1 << 1
%define FLAGS    ALIGN | MEMINFO
%define MAGIC    0x1BADB002
%define CHECKSUM -(MAGIC + FLAGS)

section .multiboot        ; SEÇÃO EXCLUSIVA PARA O CABEÇALHO
    align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .text             ; SEÇÃO DE CÓDIGO COMEÇA AQUI
    global _start
    extern main

_start:
    ; Configura o stack (opcional, mas recomendado)
    ; mov esp, stack_space 
    call main
    cli
.hang:
    hlt
    jmp .hang

section .bss
resb 8192                 ; 8KB para o stack
stack_space: