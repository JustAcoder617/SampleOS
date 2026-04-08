; --- interrupts.asm ---

[bits 32]               ; Garante que estamos em 32 bits (Protected Mode)

; Importamos a função de pânico do C
extern k_panic

; Exportamos os nomes para o idt.c conseguir enxergar
global div_zero_handler
global gpf_handler
global page_fault_handler
global timer_interrupt_handler

section .text

; ---------------------------------------------------------
; 1. DIVISÃO POR ZERO (Vetor 0)
; ---------------------------------------------------------
div_zero_handler:
    pusha               ; Salva EAX, EBX, ECX, EDX, ESP, EBP, ESI, EDI
    push ds             ; Salva os segmentos de dados
    push es
    
    ; Garante que estamos usando o segmento de dados do Kernel
    mov ax, 0x10        
    mov ds, ax
    mov es, ax

    push 0              ; Empilha o código da exceção (0) para o k_panic
    call k_panic        ; Pula para o C
    
    ; O k_panic tem um loop infinito, então o código abaixo 
    ; tecnicamente nunca será executado, mas é boa prática ter:
    add esp, 4          
    pop es
    pop ds
    popa
    iret

; ---------------------------------------------------------
; 2. GENERAL PROTECTION FAULT (Vetor 13)
; ---------------------------------------------------------
gpf_handler:
    pusha               
    push ds
    push es

    mov ax, 0x10
    mov ds, ax
    mov es, ax

    push 13             ; Identificador da Exception 13
    call k_panic
    
    add esp, 4
    pop es
    pop ds
    popa
    add esp, 4          ; O GPF empilha um "error code" extra, precisamos limpar!
    iret

; ---------------------------------------------------------
; 3. PAGE FAULT (Vetor 14)
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

    add esp, 4
    pop es
    pop ds
    popa
    add esp, 4          ; Page Fault também empilha error code
    iret

; ---------------------------------------------------------
; 4. TIMER INTERRUPT (Vetor 32)
; ---------------------------------------------------------
; Este é o único que NÃO chama o panic, ele faz o check de 7s
extern status_flag
extern check_stack
extern timer_counter

timer_interrupt_handler:
    pusha
    push ds
    push es

    mov ax, 0x10        ; FIX: Carrega segmento de dados para ler status_flag
    mov ds, ax
    mov es, ax

    ; Lógica do contador (mesma de antes)
    extern timer_counter
    inc dword [timer_counter]
    cmp dword [timer_counter], 127
    jb .finalizar_irq

    mov dword [timer_counter], 0

    ; Verifica a flag do C
    mov eax, [status_flag]
    cmp eax, 1
    je .finalizar_irq    ; Se flag for 1, pula o check da stack

    call check_stack
    cmp eax, 1
    je .morreu_tudo

.finalizar_irq:
    mov al, 0x20        ; EOI (End of Interrupt) - LIBERA O TECLADO
    out 0x20, al
    
    pop es
    pop ds
    popa
    iret

.morreu_tudo:
    push 99             ; Código customizado para "Stack Explodiu"