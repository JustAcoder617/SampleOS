#include "aleatorial.h"
#include "../../kernel_utils.h"
#include "../../kernel_geral/math_utils.h"
#include "../../kernel_geral/io.h"

void aleatorial(){
    k_clear_screen();
    k_print("------------- Aleatorial -----------");
    k_print("\n");
    k_print("Tente adivinhar um numero que eu (sua cpu) pensou (1 a 10): ");
    
    uint16_t numero = rdtsc() % 10 + 1;
    int c = 0;

    while (c == 0)
    {
        int resposta = k_scanf("i"); 
        int choice = *(int*)resposta;

        if (numero > choice)
        {
            k_print("O numero e maior que esse.");
            k_print("\n");
            k_print("Digite outro numero: ");
        } 
        else if (numero < choice)
        {
            k_print("O numero e menor que esse.");
            k_print("\n");
            k_print("Digite outro numero: ");
        } 
        else
        {
            k_print("Parabens! voce acertou!!");
            k_print("\n");
            c = 1;
        }
    }
}