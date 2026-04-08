#include "calculator.h"
#include "../kernel_geral/io.h"
#include "../kernel_utils.h"
void start_calculator() {
    int n1 = 0;
    int n2 = 0;
    int operacao = 0;
    int resultado_final = 0;

    k_print("\nDigite um numero: ");
    void* ptr1 = k_scanf("i");
    if (ptr1) n1 = *(int*)ptr1; 
    k_print("Agora, digite outro numero: ");
    void* ptr2 = k_scanf("i");
    if (ptr2) n2 = *(int*)ptr2;

    k_print("O que voce quer fazer? (1. somar || 2. subtrair 3.dividir || 4.multiplicar)");
    void* ptr_op = k_scanf("i");
    if (ptr_op) operacao = *(int*)ptr_op;

    if (operacao == 1) {
        resultado_final = n1 + n2;
        k_print("\nResultado da soma: ");
        k_print_int(resultado_final);
    } else if (operacao == 2) {
        resultado_final = n1 - n2;
        k_print("\nResultado da subtracao: ");
        k_print_int(resultado_final);
    } else if (operacao==3)
    {
        resultado_final=n1/n2;
        k_print("O resultaado final é: ");
        k_print_int(resultado_final);
    } else if (operacao==4){
        resultado_final=n1*n2;
        k_print("O resultado final é: ");
        k_print_int(resultado_final);
    }
}