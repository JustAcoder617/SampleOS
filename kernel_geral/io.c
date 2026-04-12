#include "io.h"
#include "../kernel_utils.h"
#include "text.h"

/* * Função para ler um byte de uma porta de I/O.
 * Essencial para comunicar com o controlador de teclado (0x60 e 0x64).
 */
static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* * Tabela Scancode Set 1 - US QWERTY 
 * Mapeia o "código de varredura" do hardware para caracteres ASCII.
 */
unsigned char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', 
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',   
    0, /* 0x1D - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 
    0, /* 0x2A - Left Shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 
    0, /* 0x36 - Right Shift */
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'
};

/*
 * k_get_char: Aguarda uma tecla ser pressionada.
 */
char k_get_char() {
    while (1) {
        // Verifica o Status Register (Porta 0x64). O bit 0 indica se o buffer de saída tem dados.
        if (inb(0x64) & 0x01) { 
            unsigned char scancode = inb(0x60);
            
            // Se o bit 7 estiver definido (0x80), a tecla foi SOLTADA (break code).
            // Nós só queremos o PRESSIONAR da tecla (make code).
            if (!(scancode & 0x80)) {
                char c = keyboard_map[scancode];
                if (c != 0) {
                    return c;
                }
            }
        }
        // Uma pequena pausa para não fritar a CPU no QEMU enquanto espera
        asm volatile("pause");
    }
}

/*
 * k_fgets: Lê uma linha inteira do teclado até encontrar o '\n'.
 * Gerencia o buffer e o eco visual na tela.
 */
void k_fgets(char *buffer, int size) {
    int i = 0;
    while (i < size - 1) {
        char c = k_get_char();

        if (c == '\n') {
            k_putchar('\n');
            break;
        } 
        else if (c == '\b') { // Backspace
            if (i > 0) {
                i--;
                k_putchar('\b'); // k_putchar precisa saber apagar o caractere anterior!
            }
        } 
        else {
            buffer[i++] = c;
            k_putchar(c); // Ecoa o caractere na tela
        }
    }
    buffer[i] = '\0'; // Nulo terminal importante para strings em C
}

/*
 * k_scanf: Versão simplificada para ler inteiros.
 */
void* k_scanf(const char* tipo) {
    static int resultado_int;
    char buffer[16];

    // Se o tipo for "i" (inteiro)
    if (tipo[0] == 'i' && tipo[1] == '\0') { 
        k_fgets(buffer, 16);

        if (buffer[0] == '\0') return (void*)0;

        int res = 0;
        int i = 0;
        int sinal = 1;

        // Trata números negativos
        if (buffer[0] == '-') {
            sinal = -1;
            i = 1;
        }

        for (; buffer[i] != '\0'; i++) {
            if (buffer[i] >= '0' && buffer[i] <= '9') {
                res = res * 10 + (buffer[i] - '0');
            } else {
                // Se encontrar algo que não é número no meio da string
                return (void*)0; 
            }
        }

        resultado_int = res * sinal;
        return (void*)&resultado_int;
    }

    return (void*)0; 
} 