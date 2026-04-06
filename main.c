#include "kernel_utils.h"
#include "kernel_geral/io.h"

int main(void){
    k_print("Olá! bem vindo ao SampeOs,um OS feito em C e em CLI!");
    k_print("selecione oque você quer fazer: 1. Calculadora 2.sair");
    int choice=0;
    void* res=k_scanf("i");
    if (res != 0) {
        choice = *(int*)res;
    }
    else if(res==NULL){
        k_print("Você não digitou um número!");
        int check=0;
        while (check==0)
        {
            res=NULL;
            k_print("selecione oque você quer fazer: 1. Calculadora 2.sair");
            if (res!=-1)
            {
                check=1;
            }
            else{
                k_print("Você não digitou um número! retornando...");
            }
            
        }
        
    }
}