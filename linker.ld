ENTRY(_start)

SECTIONS
{
    /* O Kernel começa em 1MB */
    . = 1M;

    /* SEÇÃO DE CÓDIGO */
    .text BLOCK(4K) : AT(ADDR(.text))
    {
        /* FORÇA o Multiboot a ser a PRIMEIRA coisa do arquivo */
        KEEP(*(.multiboot)) 
        *(.text)
        *(.text.*)
    }

    /* SEÇÃO DE DADOS SOMENTE LEITURA */
    .rodata ALIGN(4K) : AT(ADDR(.rodata)) 
    { 
        *(.rodata*) 
    }

    /* SEÇÃO DE DADOS (Onde ficam seus contadores do timer) */
    .data ALIGN(4K) : AT(ADDR(.data))   
    { 
        *(.data) 
    }

    /* SEÇÃO DA STACK (Importante para o seu Vigia de 7s) */
    .bootstrap_stack ALIGN(4K) : AT(ADDR(.bootstrap_stack))
    {
        *(.bootstrap_stack)
    }

    /* SEÇÃO BSS (Variáveis não inicializadas) */
    .bss ALIGN(4K) : AT(ADDR(.bss))    
    { 
        *(.bss) 
        *(COMMON) 
    }

    /* DESCARTA lixo que o GCC coloca e que quebra o Boot */
    /DISCARD/ : 
    { 
        *(.comment) 
        *(.eh_frame) 
        *(.note.gnu.property) 
    }
}