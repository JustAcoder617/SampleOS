
#include "pit.h"
#include <stdint.h>

void init_timer(uint32_t frequency) {
    uint32_t divisor = 1193182 / frequency;

    // Envia o comando para o PIT (Porta 0x43)
    // 0x36 = Canal 0, LSB/MSB, Modo 3
    __asm__ volatile("outb %%al, %%dx" : : "a"(0x36), "d"(0x43));

    // Envia o divisor para a porta 0x40 (8 bits por vez)
    __asm__ volatile("outb %%al, %%dx" : : "a"((uint8_t)(divisor & 0xFF)), "d"(0x40));
    __asm__ volatile("outb %%al, %%dx" : : "a"((uint8_t)((divisor >> 8) & 0xFF)), "d"(0x40));

    // DESBLOQUEIA a IRQ0 no PIC (Importante!)
    __asm__ volatile("inb $0x21, %al; andb $0xfe, %al; outb %al, $0x21");
}