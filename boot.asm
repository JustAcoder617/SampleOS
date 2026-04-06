; --- Constantes Multiboot ---
MB_ALIGN     equ  1 << 0            ; Alinha módulos carregados em páginas de 4KB
MB_MEMINFO   equ  1 << 1            ; Fornece mapa de memória
MB_FLAGS     equ  MB_ALIGN | MB_MEMINFO
MB_MAGIC     equ  0x1BADB002        ; Número mágico para o bootloader
MB_CHECKSUM  equ -(MB_MAGIC + MB_FLAGS)

; --- Seção Multiboot (Deve estar no início do binário) ---
section .multiboot
align 4
    dd MB_MAGIC
    dd MB_FLAGS
    dd MB_CHECKSUM

; --- Seção da Pilha ---
section .bootstrap_stack, nobits
align 16
stack_bottom:
    resb 16384 ; 16 KB
stack_top:

; --- Código ---
section .text
    global _start
    extern main

_start:
    ; 1. Configura o ponteiro da pilha
    mov esp, stack_top

    ; 2. (Opcional) Passa info do Multiboot para o C
    ; push ebx ; Ponteiro para a estrutura multiboot_info
    ; push eax ; Magic number (deve ser 0x2BADB002)

    ; 3. Chama o kernel em C
    call main

    ; 4. Se o C retornar, entra em loop infinito
    cli
.hang:
    hlt
    jmp .hang

