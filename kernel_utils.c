#include "kernel_utils.h"

// Variáveis internas (estáticas para não vazarem para outros arquivos)
static uint16_t* const VGA_BUFFER = (uint16_t*) 0xB8000;
static const int MAX_WIDTH = 80;
static const int MAX_HEIGHT = 25;
static int cursor_x = 0;
static int cursor_y = 0;

// Helper interno
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

void k_clear_screen() {
    for (int y = 0; y < MAX_HEIGHT; y++) {
        for (int x = 0; x < MAX_WIDTH; x++) {
            const int index = y * MAX_WIDTH + x;
            VGA_BUFFER[index] = vga_entry(' ', VGA_COLOR_WHITE);
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

void k_putchar(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        const int index = cursor_y * MAX_WIDTH + cursor_x;
        VGA_BUFFER[index] = vga_entry(c, VGA_COLOR_WHITE);
        cursor_x++;
    }

    if (cursor_x >= MAX_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= MAX_HEIGHT) {
        k_clear_screen(); 
    }
}

void k_print(const char* data) {
    for (size_t i = 0; data[i] != '\0'; i++) {
        k_putchar(data[i]);
    }
}

void k_print_int(int n) {
    if (n == 0) {
        k_putchar('0');
        return;
    }
    if (n < 0) {
        k_putchar('-');
        n = -n;
    }
    char buf[12];
    int i = 10;
    buf[11] = '\0';
    while (n > 0) {
        buf[i--] = (n % 10) + '0';
        n /= 10;
    }
    k_print(&buf[i + 1]);
}