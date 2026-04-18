#include "../../kernel_utils.h"
#include "../../kernel_geral/io.h"
#include "../../kernel_geral/text.h"
#include "../../panic/panic.h"

extern int check_funcionando;
extern int check_interrupter;

void monitor_setup() {
    k_clear_screen();
    k_print("------ System Monitor-------\n\n\n");
    k_print("bem vindo ao monitor de sistema do sample os!\n");
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