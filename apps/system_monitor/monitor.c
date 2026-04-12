#include "../../kernel_utils.h"
#include "../../kernel_geral/io.h"
#include "../../kernel_geral/text.h"
#include "../../panic/panic.h"

extern int check_funcionando;
extern int check_interrupter;

void monitor_setup() {
    if (check_funcionando == 0) {
        k_print("O sistema de verificação geral do kernel esta funcionando corretamente.");
    } else {
        k_print("ATENÇAO: A VERIFICAÇÃO GERAL DE ERROS DESTE KERNEL ESTA DESATIVADA POR UM MOTIVO DESCONHECIDO. E ALTAMENTE RECOMENDADO REINICIAR O COMPUTADOR, POIS, A QUALQUER MOMENTO, ELE PODE REINICIAR OU TRAVAR SEM JUSTIFICATIVA.");
        return;
    }

    if (check_interrupter == 0) {
        k_print("A funcao do time interrupter handler está funcionando corretamente.");
    } else {
        k_print("ATENÇAO: A FUNÇÃO TIME INTERRUPTER HANDLER NÃO ESTÁ FUNCIONANDO POR UM MOTIVO DESCONHECIDO. A VERIFICAÇÃO CONTRA STACK_OVERFLOW ESTÁ DESATIVADA. É RECOMENDADA REINICIAR O COMPUTADOR.");
    }
}