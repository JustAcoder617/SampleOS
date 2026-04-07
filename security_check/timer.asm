extern check_stack
extern desligar_pc

section .data
    ; No timer padrão (18.2Hz), 127 ticks equivalem a aproximadamente 7 segundos
    timer_counter dd 0 

section .text
global timer_interrupt_handler

timer_interrupt_handler:
    pusha                   ; Preserva o estado do kernel (registradores)
    push ds                 ; Preserva os segmentos de dados
    push es

    inc dword [timer_counter]
    cmp dword [timer_counter], 127
    jb .finalizar_irq       ; Se não deu 7 segundos, pula pro fim

    ; --- Bloco de Checagem (Roda a cada 7s) ---
    mov dword [timer_counter], 0 ; Reseta o contador
    
    call check_stack        ; Sua função C
    cmp eax, 1
    je .morreu_tudo         ; Se erro, desliga
    ; ------------------------------------------

.finalizar_irq:
    ; AVISO AO PIC: "Pode mandar a próxima interrupção quando quiser"
    mov al, 0x20
    out 0x20, al

    pop es
    pop ds
    popa                    ; Restaura o estado original
    iret                    ; O "pulo do gato": volta exatamente onde o C parou

.morreu_tudo:
    call desligar_pc        ; Se a stack explodiu, nem tenta voltar