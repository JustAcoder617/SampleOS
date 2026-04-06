#include "io.h"
#include "../kernel_utils.h"
#include "text.h"
static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    // 'inb' lê um byte da porta especificada (%1) e joga no registrador al (%0)
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}
// Tabela simplificada de Scancodes para caracteres (Set 1)
// Tabela Scancode Set 1 - US QWERTY padrão
unsigned char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', /* 0x0E */
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     /* 0x1C */
    0, /* 0x1D - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 
    0, /* 0x2A - Left Shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 
    0, /* 0x36 - Right Shift */
    '*',
    0, /* 0x38 - Alt */
    ' ', /* Espaço */
    0, /* 0x3A - Caps Lock */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* F1 a F10 */
    0, /* 0x45 - Num Lock */
    0, /* 0x46 - Scroll Lock */
    '7', '8', '9', '-',
    '4', '5', '6', '+',
    '1', '2', '3', '0', '.',
    0, 0, 0,
    0, /* F11 */
    0, /* F12 */
    0  /* Restante vazio */
};
unsigned char numeros_map[128]={
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, 0, '\b',
    0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, '\n',
    0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0, 0,
    0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0, 0,
    0,  0,   ' ', 0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0, 0,
    0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
    '7', '8', '9', 0,  /* Teclado Numérico (Numpad) */
    '4', '5', '6', 0,
    '1', '2', '3', '0', '.'
};
char k_get_char() {
    char c = 0;
    while (1) {
        // Verifica se há algo na porta do teclado
        if (inb(0x64) & 0x01) { 
            uint8_t scancode = inb(0x60);
            
            // Se o bit 7 for 0, a tecla foi PRESSIONADA
            // Se for 1, a tecla foi SOLTADA (ignora aqui)
            if (!(scancode & 0x80)) {
                return keyboard_map[scancode];
            }
        }
    }
}
void k_fgets(char *buffer, int size) {
    int i = 0;
    char c;

    while (i < size - 1) {
        c = k_get_char();

        if (c == '\n') {
            k_putchar('\n'); // Pula linha na tela
            break;
        } 
        else if (c == '\b') { // Tratamento de Backspace
            if (i > 0) {
                i--;
                k_putchar('\b'); // Move o cursor de volta, apaga e move de novo (depende da sua k_print)
            }
        } 
        else if (c != 0) { // Tecla válida
            buffer[i++] = c;
            k_putchar(c); // Ecoa o caractere na tela
        }
    }
    buffer[i] = '\0'; // Finaliza a string
}
void* k_scanf(const char* tipo) {
    static int resultado_int;
    char buffer[16];

    if (tipo[0] == 'i' && tipo[1] == '\0') { 
        k_fgets(buffer, 16);

        int res = 0;
        int i = 0;
        
        // Se o buffer estiver vazio (usuário só deu enter)
        if (buffer[0] == '\0') return NULL;

        for (i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] < '0' || buffer[i] > '9') {
                return NULL; 
            }
            res = res * 10 + (buffer[i] - '0');
        }

        resultado_int = res;
        return (void*)&resultado_int;
    }

    return NULL; // Sempre NULL para erros!
}