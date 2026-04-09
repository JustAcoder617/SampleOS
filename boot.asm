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

section .data
gdt_start:
    dq 0 ; null descriptor
gdt_code:
    dw 0xFFFF ; limit low
    dw 0 ; base low
    db 0 ; base middle
    db 10011010b ; access (present, ring 0, code, executable, readable)
    db 11001111b ; granularity (4K pages, 32-bit)
    db 0 ; base high
gdt_data:
    dw 0xFFFF
    dw 0
    db 0
    db 10010010b ; access (present, ring 0, data, writable)
    db 11001111b
    db 0
gdt_end:

gdt_ptr:
    dw gdt_end - gdt_start - 1
    dd gdt_start

section .text
global _start
extern main

_start:
    ; Load GDT
    lgdt [gdt_ptr]
    
    ; Far jump to reload CS
    jmp 0x08:.reload_cs
.reload_cs:
    
    ; Set data segments
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    
    mov esp, stack_top
    call main          ; Vai para o C
    cli
.hang: hlt
    jmp .hang