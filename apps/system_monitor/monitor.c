#include "../../kernel_utils.h"
#include "../../kernel_geral/io.h"
#include "../../kernel_geral/text.h"
#include "../../panic/panic.h"

extern int check_funcionando;
extern int check_interrupter;

void monitor_setup() {
    if (check_funcionando == 1) {
        k_print("O sistema de verificação geral do kernel está funcionando corretamente.");
    } else {
        k_panic_message("ATENÇÃO: A VERIFICAÇÃO GERAL DE ERROS DESTE KERNEL ESTÁ DESATIVADA POR UM MOTIVO DESCONHECIDO. É ALTAMENTE RECOMENDADO REINICIAR O COMPUTADOR, POIS, A QUALQUER MOMENTO, ELE PODE REINICIAR OU TRAVAR SEM JUSTIFICATIVA.");
        return;
    }

    if (check_interrupter == 1) {
        k_print("A função do time interrupter handler está funcionando corretamente.");
    } else {
        k_panic_message("ATENÇÃO: A FUNÇÃO TIME INTERRUPTER HANDLER NÃO ESTÁ FUNCIONANDO POR UM MOTIVO DESCONHECIDO. A VERIFICAÇÃO CONTRA STACK_OVERFLOW ESTÁ DESATIVADA. É RECOMENDADA REINICIAR O COMPUTADOR.");
    }
}