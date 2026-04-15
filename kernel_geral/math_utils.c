#include "math_utils.h"
#include "stdint.h"

uint64_t rdtsc() {
    //numeros aleatorios. É usado com , por exemplo: rdtsc() % 10 (gera um numero entre 0 e 9)
    uint32_t lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}