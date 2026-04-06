ENTRY(_start)

SECTIONS
{
    /* Garante que o arquivo comece em 1MB fisicamente e virtualmente */
    . = 1M;

    .text : AT(ADDR(.text))
    {
        /* ISSO AQUI É O QUE O QEMU PROCURA */
        *(.multiboot) 
        *(.text)
        *(.text.*)
    }

    .rodata ALIGN(4K) : AT(ADDR(.rodata)) { *(.rodata*) }
    .data ALIGN(4K)   : AT(ADDR(.data))   { *(.data) }
    .bss ALIGN(4K)    : AT(ADDR(.bss))    { *(.bss) *(COMMON) }

    /DISCARD/ : { *(.comment) *(.eh_frame) *(.note.gnu.property) }
}