#include "../kernel_utils.h"
#include <stdint.h>

extern uint32_t stack_bottom;

#define STACK_MAGIC 0xDEADC0DE

void check_stack() {
    // Usamos o operador '&' porque queremos o endereço onde a stack começa
    uint32_t* canary_address = (uint32_t*)&stack_bottom;

    if (*canary_address != STACK_MAGIC) {
        k_print("ATENTION: ERROR CODE: AES924 (se tu n e dev basicamente a stack do seu coracao bugou :D reiniciando o pc...)");
    }
}