#include "idt.h"
#include "../kernel_utils.h"
struct idt_entry idt[256];
struct idt_ptr idtp;

// Importa o handler do Timer que você já tinha
extern void timer_interrupt_handler();

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_init() {
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    // 1. Limpa a tabela
    for(int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    idt_set_gate(0,  (uint32_t)div_zero_handler,  KERNEL_CODE_SEGMENT, IDT_FLAG_INTERRUPT_GATE);
    idt_set_gate(13, (uint32_t)gpf_handler,       KERNEL_CODE_SEGMENT, IDT_FLAG_INTERRUPT_GATE);
    idt_set_gate(14, (uint32_t)page_fault_handler, KERNEL_CODE_SEGMENT, IDT_FLAG_INTERRUPT_GATE);

    // 3. Registra as Interrupções de Hardware (IRQs)
    // O Timer fica no 32 por causa do remapeamento do PIC
    for(int i = 32; i < 48; i++) {
        idt_set_gate(i, (uint32_t)dummy_handler, 0x08, 0x8E);
    }
    idt_set_gate(32, (uint32_t)timer_interrupt_handler, KERNEL_CODE_SEGMENT, IDT_FLAG_INTERRUPT_GATE);
    // 4. Carrega a IDT no processador
    __asm__ volatile("lidt %0" : : "m"(idtp));
    
}