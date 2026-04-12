#include "panic.h"
#include "kernel_geral/io.h" // Para usar seu k_print e k_clear

void k_panic(int exception_num) {
    // 1. Desliga interrupções imediatamente
    __asm__ volatile("cli");

    k_clear_screen();
    
    k_print("###########################################\n");
    k_print("            SAMPE OS - KERNEL PANIC        \n");
    k_print("###########################################\n\n");

    k_print("ERRO FATAL DETECTADO: ");

    switch(exception_num) {
        case 0:  k_print("DIVISAO POR ZERO (0)"); break;
        case 13: k_print("GENERAL PROTECTION FAULT (13)"); break;
        case 14: k_print("PAGE FAULT (14) - MEMORIA INVALIDA"); break;
        case 99: k_print("STACK OVERFLOW / SEGURANCA"); break;
        case 12: k_print("STACK_FAULT (12) / MEMORIA");
        default: k_print("EXCECAO DESCONHECIDA"); break;
    }

    k_print("\n\nO sistema foi paralisado para proteger o hardware.\n");
    k_print("Por favor, reinicie a maquina virtual (QEMU) ou o seu Pc..");

    // 2. Trava o processador
    while(1) {
        __asm__ volatile("hlt");
    }
}

void k_panic_message(const char* message) {
    k_clear_screen();
    k_print("!!! KERNEL PANIC !!!\n\n");
    k_print("ERRO: ");
    k_print(message);
    
    __asm__ volatile("cli");
    while(1) { __asm__ volatile("hlt"); }
}