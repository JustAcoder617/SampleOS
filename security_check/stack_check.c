#include "../kernel_utils.h"
#include <stdint.h>

extern uint32_t stack_bottom;
void desligar_pc();
extern int outw();
#define STACK_MAGIC 0xDEADC0DE

int check_stack() {
    // Usamos o operador '&' porque queremos o endereço onde a stack começa
    uint32_t* canary_address = (uint32_t*)&stack_bottom;
    if (*canary_address != STACK_MAGIC) {
        return 1;
    }
    else{
        return 0;
    }
}
void warning(void){
    k_print("ATENTION:ERROR CODE NOSTACK");
    desligar_pc();
}

void desligar_pc() {
    // 1. Desativa as interrupções (Ninguém pode interromper o adeus)
    __asm__ volatile ("cli");

    // 2. Manda o comando para o Hardware (Exemplo QEMU/ACPI)
    // Nota: O outw precisa estar definido (geralmente em assembly ou via __builtin_outw)
    outw(0x604, 0x2000); 

    while (1) {
        __asm__ volatile ("hlt");
    }
}