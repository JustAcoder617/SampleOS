; --- Multiboot Header ---
MB_ALIGN     equ  1 << 0
MB_MEMINFO   equ  1 << 1
MB_MAGIC     equ  0x1BADB002
MB_CHECKSUM  equ -(MB_MAGIC + (MB_ALIGN | MB_MEMINFO))

section .multiboot
align 4
    dd MB_MAGIC
    dd MB_ALIGN | MB_MEMINFO
    dd MB_CHECKSUM

; --- Stack com Canário ---
section .bss
align 16
stack_buffer:
    resb 16380         ; Reserva o espaço da stack

section .data
align 16
global stack_bottom
stack_bottom:
    dd 0xDEADC0DE      ; O Canário fica no fundo da stack
stack_top: equ stack_buffer + 16380

; --- GDT (Global Descriptor Table) ---
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

; --- Código Principal ---
section .text
global _start
global dummy_handler
extern setup_start      ; Agora chamamos o seu setup_start no C

; --- DUMMY HANDLER ---
dummy_handler:
    pusha
    mov al, 0x20
    out 0x20, al       
    popa
    iret

_start:
    ; 1. Configura a GDT
    lgdt [gdt_ptr]
    
    ; 2. Far jump para recarregar o CS (Code Segment)
    jmp 0x08:.reload_cs
.reload_cs:
    
    ; 3. Configura os segmentos de dados
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    
    ; 4. Configura o ponteiro da pilha
    mov esp, stack_top

    ; --- INTEGRAÇÃO COM START.C ---
    ; No momento do boot:
    ; EAX contém o Magic Number (0x2BADB002)
    ; EBX contém o endereço da struct Multiboot Info (RAM, etc)
    
    push ebx            ; Segundo argumento da setup_start (struct pointer)
    push eax            ; Primeiro argumento da setup_start (magic number)

    call setup_start    ; Vai para o start.c fazer as verificações
    
    ; Caso o setup_start retorne (não deveria), entra em loop
    cli
.hang: hlt
    jmp .hang