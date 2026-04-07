#ifndef IDT_H
#define IDT_H

#include <stdint.h>

// --- FLAGS DA IDT (O "estilo Linux") ---
#define IDT_FLAG_INTERRUPT_GATE 0x8E  // 32-bit, Presente, Ring 0 (Kernel)
#define KERNEL_CODE_SEGMENT     0x08  // O seletor de segmento definido no seu GDT/Boot

/* * Estrutura de uma entrada na IDT (8 bytes exatos)
 * O atributo 'packed' é OBRIGATÓRIO para o GCC não colocar 
 * espaços vazios entre as variáveis.
 */
struct idt_entry {
    uint16_t base_low;  // Endereço da função (bits 0-15)
    uint16_t sel;       // Seletor de segmento de código
    uint8_t  always0;   // Reservado pela Intel, sempre 0
    uint8_t  flags;     // Configurações de acesso e tipo
    uint16_t base_high; // Endereço da função (bits 16-31)
} __attribute__((packed));

/* * Estrutura do Registro da IDT (IDTR)
 * É isso que a instrução 'lidt' carrega para a CPU.
 */
struct idt_ptr {
    uint16_t limit;     // Tamanho da tabela - 1
    uint32_t base;      // Endereço de memória onde a tabela 'idt' começa
} __attribute__((packed));

/* --- Funções de Controle --- */

// Preenche uma das 256 entradas da tabela
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

// Cria a tabela, limpa o lixo e carrega no processador
void idt_init();

#endif