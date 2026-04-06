#ifndef KERNEL_UTILS_H
#define KERNEL_UTILS_H

#include <stdint.h>
#include <stddef.h>

enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_WHITE = 15,
};

// Assinaturas das funções
void k_clear_screen();
void k_print(const char* data);
void k_putchar(char c);
void k_print_int(int n);

#endif