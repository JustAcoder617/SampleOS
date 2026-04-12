[bits 32]

; --- IMPORTAÇÕES (Coisas que vêm do C) ---
extern k_panic
extern status_flag
extern check_stack
extern timer_counter
extern dummy_handler
; --- EXPORTAÇÕES (Coisas que o idt.c vai enxergar) ---
global div_zero_handler
global gpf_handler
global page_fault_handler
global stack_fault_handler
global timer_interrupt_handler
global check_funcionando
global check_interrupter

section .data
    check_funcionando dd 0
    check_interrupter dd 0

section .text
; ---------------------------------------------------------
; 1. DIVISÃO POR ZERO (Vetor 0) - Sem Error Code
; ---------------------------------------------------------
div_zero_handler:
    pusha
    push ds
    push es
    mov ax, 0x10        
    mov ds, ax
    mov es, ax

    push 0              ; ID da exceção
    call k_panic
    hlt                 ; Trava se o panic retornar

; ---------------------------------------------------------
; 2. STACK FAULT (Vetor 12) - COM Error Code
; ---------------------------------------------------------
stack_fault_handler:
    ; CPU já empilhou Error Code aqui
    pusha
    push ds
    push es
    mov ax, 0x10
    mov ds, ax
    mov es, ax

    push 12
    call k_panic
    hlt

; ---------------------------------------------------------
; 3. GENERAL PROTECTION FAULT (Vetor 13) - COM Error Code
; ---------------------------------------------------------
gpf_handler:
    pusha               
    push ds
    push es
    mov ax, 0x10
    mov ds, ax
    mov es, ax

    push 13
    call k_panic
    hlt

; ---------------------------------------------------------
; 4. PAGE FAULT (Vetor 14) - COM Error Code
; ---------------------------------------------------------
page_fault_handler:
    pusha
    push ds
    push es
    mov ax, 0x10
    mov ds, ax
    mov es, ax

    push 14
    call k_panic
    hlt

; ---------------------------------------------------------
; 5. TIMER INTERRUPT (Vetor 32)
; ---------------------------------------------------------
timer_interrupt_handler:
    pusha
    push ds
    push es

    mov ax, 0x10
    mov ds, ax
    mov es, ax

    ; Seta flag para o monitor de recursos
    mov dword [check_interrupter], 1 

    inc dword [timer_counter]
    
    ; Lógica de verificação da stack (canário)
    cmp dword [timer_counter], 127
    jb .finalizar_irq

    mov dword [timer_counter], 0

    mov eax, [status_flag]
    cmp eax, 1
    je .finalizar_irq    

    call check_stack
    cmp eax, 1
    je .morreu_tudo

.finalizar_irq:
    mov al, 0x20
    out 0x20, al
    pop es
    pop ds
    popa
    iret

.morreu_tudo:
    push 99             ; Erro: Stack Corrompida (Canário morreu)
    call k_panic
    hlt