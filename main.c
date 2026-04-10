
#include "kernel_utils.h"
#include "kernel_geral/io.h"
#include "apps/calculator.h"
#include "security_check/stack_check.h"
#include "idt/pit.h"
#include "idt/idt.h"

// Função vital para o hardware não conflitar com a CPU
void pic_remap() {
    // Envia comandos para o Master e Slave PIC
    __asm__ volatile (
        "mov $0x11, %%al; out %%al, $0x20; out %%al, $0xa0;"
        "mov $0x20, %%al; out %%al, $0x21;" // Master PIC -> Vector 32
        "mov $0x28, %%al; out %%al, $0xa1;" // Slave PIC  -> Vector 40
        "mov $0x04, %%al; out %%al, $0x21;"
        "mov $0x02, %%al; out %%al, $0xa1;"
        "mov $0x01, %%al; out %%al, $0x21; out %%al, $0xa1;"
        "xor %%al, %%al; out %%al, $0x21; out %%al, $0xa1;"
        : : : "al"
    );
}

volatile int status_flag=1;
volatile uint32_t timer_counter = 0;

int main(){
    k_clear_screen();
    k_print("Iniciando SampeOs...\n");

    // ORDEM OBRIGATÓRIA:
    pic_remap();    // 1. Organiza o hardware
    idt_init();     // 2. Cria o mapa de funções
    init_timer(100);// 3. Liga o tique-taque do relógio
    __asm__ volatile("sti"); // 4. Agora sim: "Pode falar, hardware!"

    k_print("----- Ola! Bem-vindo ao SampeOs! -----\n");
    
    while (1) {
        k_print("\nSelecione: 1. Calculadora | 2. Sair\n");
        k_print("> ");

        void* res = k_scanf("i");
        if (res != (void*)0) {
            int choice = *(int*)res;
            if (choice == 1) {
                start_calculator(); 
            } else if (choice==3){
                k_print("Voce quer desligar o anti-virus do kernel? 1.sim 2.nao");
                void* res=k_scanf("i");
                if (res!=(void*)0)
                {
                    int choice=*(int*)res;
                    if (choice==1)
                    {
                        k_print("Desligando checker da stack...");
                        status_flag=0;
                        while (1);
                    }
                    
                }
                
            }
            else if (choice == 2) {
                k_print("Desligando...");
                desligar_pc();
                break; 
            }
        }
    }

    while(1) { __asm__ volatile("hlt"); }
    return 0;
}