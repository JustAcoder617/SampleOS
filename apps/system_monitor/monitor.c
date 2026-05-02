#include "../../kernel_utils.h"
#include "../../kernel_geral/io.h"
#include "../../kernel_geral/text.h"
#include "../../panic/panic.h"
#include "../../start.h"
extern int check_funcionando;
extern int check_interrupter;

void monitor_setup() {
    k_clear_screen();
    k_print("------ System Monitor-------\n\n\n");
    k_print("bem vindo ao monitor de sistema do sample os!\n");
    k_print("Atualmente, o nome do seu processador e: ");
    k_print(System_info.cpu_name);
    k_putchar('\n');
    k_print("e com ");
    k_print(System_info.mm_mx);
    k_print("De memoria ram.");
    if (check_funcionando==0)
    {
        k_print("a verificacao geral do sistema esta funcionando corretamente.\n\n");
    } else{
        k_print("a verificacao geral do sistema nao esta funcionando. E recomendado desligar o pc...\n\n");
    }
    if (check_interrupter>=1)
    {
        k_print("o sistema de interrupcoes de hardware esta funcionando.\n");
    } else{
        k_print("o sistema de interrupcoes de hardware nao esta funcionando. Nao e muito perigoso, mas mesmo assim e recomendado desligar o pc...\n");
    }
}