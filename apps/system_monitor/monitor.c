#include "../../kernel_utils.h"
#include "../../kernel_geral/io.h"
#include "../../kernel_geral/text.h"
#include "../../panic/panic.h"

extern int check_funcionando;
extern int check_interrupter;

void monitor_setup() {
    if (check_funcionando == 0) {
        k_print("O sistema de verificacao geral do kernel esta funcionando corretamente.");
        k_print("\n");
    } else {
        k_print("ATENCAO: A VERIFICAO GERAL DE ERROS DESTE KERNEL ESTA DESATIVADA POR UM MOTIVO DESCONHECIDO. E ALTAMENTE RECOMENDADO REINICIAR O COMPUTADOR, POIS, A QUALQUER MOMENTO, ELE PODE REINICIAR OU TRAVAR SEM JUSTIFICATIVA.");
        k_print("\n");
        return;
    }

    if (check_interrupter == 0) {
        k_print("A funcao do time interrupter handler está funcionando corretamente.");
        k_print("\n");
    } else {
        k_print("ATENCAO: A FUNCAO TIME INTERRUPTER HANDLER NAO ESTA FUNCIONANDO POR UM MOTIVO DESCONHECIDO. A VERIFICACAO CONTRA STACK_OVERFLOW ESTA DESATIVADA. E RECOMENDADO REINICIAR O COMPUTADOR.");
        k_print("\n");
    }
}