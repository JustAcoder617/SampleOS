ENTRY(_start)

SECTIONS
{
    /* O Kernel começa em 1MB (padrão Multiboot) */
    . = 1M;

    .text :
    {
        /* O KEEP garante que o linker não jogue fora o cabeçalho */
        KEEP(*(.multiboot))
        *(.text)
        *(.text.*)
    }

    .rodata : { *(.rodata*) }
    .data   : { *(.data) }
    .bss    : { *(.bss) }
}