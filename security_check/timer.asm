extern check_stack
extern desligar_pc

timer_interrupt_handler:
    pusha                   ; Salva todos os registradores do "primeiro processo"
    
    call check_stack        ; Chama sua função C
    cmp eax, 1
    je .morreu_tudo         ; Se deu erro, nem volta pro kernel, desliga direto
    
    popa                    ; Restaura tudo
    iret                    ; Volta para o que o PC estava fazendo antes

.morreu_tudo:
    call desligar_pc        ; Tchau!
