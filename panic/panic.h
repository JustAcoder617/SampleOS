#ifndef PANIC_H
#define PANIC_H

#include <stdint.h>

/**
 * Para tudo, limpa a tela e exibe o erro fatal.
 * @param exception_num O número da interrupção/exceção capturada.
 */
void k_panic(int exception_num);

/**
 * Uma versão para erros de software (mensagens customizadas).
 */
void k_panic_message(const char* message);

#endif