#include <stdint.h>
#include "panic/panic.h"

struct system_general_info {
    char cpu_name[49];
    uint64_t mm_mx; // Guardaremos a RAM total em KB ou MB aqui
};

// Declarações externas
extern int main();
struct system_general_info System_info;

// Estrutura do Multiboot para ler os dados que o GRUB passou
struct multiboot_info {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
} __attribute__((packed));

void setup_start(uint32_t magic, struct multiboot_info* mbi) {
    // 1. Validar se o boot foi via Multiboot e se há info de memória
    if (magic == 0x2BADB002 && (mbi->flags & (1 << 1))) {
        // mm_mx recebe a RAM alta + 1MB de RAM baixa (convertido para KB)
        System_info.mm_mx = (uint64_t)mbi->mem_upper + 1024;
    } else {
        System_info.mm_mx = 0; // Força o pânico abaixo
    }

    // 2. Pegar o nome da CPU (CPUID)
    uint32_t *cpu_ptr = (uint32_t *)System_info.cpu_name;
    for (uint32_t i = 0; i < 3; i++) {
        __asm__ volatile ("cpuid"
            : "=a"(cpu_ptr[i*4]), "=b"(cpu_ptr[i*4+1]), "=c"(cpu_ptr[i*4+2]), "=d"(cpu_ptr[i*4+3])
            : "a"(0x80000002 + i));
    }
    System_info.cpu_name[48] = '\0';

    if (System_info.mm_mx > 0) {
        main();
        return;
    } else {
        // Se a memória for 0 ou Multiboot falhou, pânico!
        k_panic(-10101);
    }
}