#include "aleatorial.h"
#include "../../kernel_utils.h"
#include "../../kernel_geral/math_utils.h"
#include "../../kernel_geral/io.h"
void aleatorial(){
    k_clear_screen();
    k_print("------------- Aleatorial -----------");
    k_print("\n");
    k_print("Tente adivinhar um numero que eu (sua cpu) pensou dica: é de 1 a 10: ");
    uint16_t numero=rdtsc() % 11;
    int c=0;
    while (c==0)
    {
         int resposta=k_scanf("i");
        int choice=*(int*)resposta;
        if (choice>resposta)
        {
            k_print("O numero e maior que esse.");
        } else if (choice<resposta)
        {
            k_print("O numero e menor que esse");
        } else if (choice==resposta)
        {
            k_print("Parabens! voce acertou!!");
        }
    }
}