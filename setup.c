#include "setup.h"
extern unsigned int memoria_tamanho;
extern char cpu_name[49];
extern int main()//do main.c

void set_cpu_name() {
    unsigned int regs[4];
    for (int i = 0; i < 3; i++) {
        __asm__ __volatile__ ("cpuid" : "=a"(regs[0]), "=b"(regs[1]), "=c"(regs[2]), "=d"(regs[3]) : "a"(0x80000002 + i));
        *((unsigned int*)(cpu_name + (i * 16) + 0)) = regs[0];
        *((unsigned int*)(cpu_name + (i * 16) + 4)) = regs[1];
        *((unsigned int*)(cpu_name + (i * 16) + 8)) = regs[2];
        *((unsigned int*)(cpu_name + (i * 16) + 12)) = regs[3];
    }
    cpu_name[48] = '\0';
}
void set_mm(void* mbi_ptr) {
   unsigned int low = *(unsigned int*)(mbi + 4);
    unsigned int high = *(unsigned int*)(mbi + 8);
    
    // Soma tudo e converte KB -> GB (dividir por 1024*1024)
    memoria_tamanho = (low + high) / 1048576;
}

