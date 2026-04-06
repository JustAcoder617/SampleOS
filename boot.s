# Declaração das constantes para o Multiboot
.set ALIGN,    1<<0             # alinhar módulos em páginas de memória
.set MEMINFO,  1<<1             # fornecer mapa de memória
.set FLAGS,    ALIGN | MEMINFO  # o 'campo' flags do multiboot
.set MAGIC,    0x1BADB002       # 'número mágico' para o bootloader achar o header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum para provar que é multiboot

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .text
.global _start
_start:
    # Chama a sua função kernel_main que está no main.c
    extern main
    call main

    # Se o kernel retornar, entra em loop infinito
    cli
1:  hlt
    jmp 1b