#include "kernel_utils.h"
#include "kernel_geral/io.h"
#include "apps/calculator.h"
#include "main.h"
int main(int status){
    
    if (status==0){
        k_print("-----Ola! bem vindo ao SampeOs,um OS feito em C e em CLI!-----");
        k_print("selecione oque voce quer fazer: 1. Calculadora 2.sair ");
        k_putchar("\n");
        int choice=0;
        void* res=k_scanf("i");
        if(res==1){
        start_calculator();
    
    }
    

}