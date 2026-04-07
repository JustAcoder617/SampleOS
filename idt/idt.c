#include "idt.h"
#include "../kernel_utils.h"

// A tabela propriamente dita (256 entradas)
struct idt_entry idt[256];
struct idt_ptr idtp;
extern void timer_interrupt_handler();

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_init() {
    // Configura o "ponteiro" que o processador vai ler
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    // Limpa a IDT com zeros para evitar lixo de memória
    for(int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    /* * AGORA A CONEXÃO:
     * Mapeamos a interrupção 32 (que é o Timer após o remapeamento do PIC)
     * para o endereço da função 'timer_interrupt_handler' que está no seu ASM.
     */
    idt_set_gate(32, (uint32_t)timer_interrupt_handler, 0x08, 0x8E);

    // Instrução Assembly para o processador carregar a tabela
    __asm__ volatile("lidt %0" : : "m"(idtp));
}