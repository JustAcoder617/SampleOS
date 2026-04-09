# --- Compiladores e Flags ---
CC = gcc
AS = nasm
LD = ld

# -m32: Compila para 32 bits (x86)
# -ffreestanding: Diz que não temos uma biblioteca padrão (estamos por nossa conta!)
# -I.: Permite que o GCC ache os arquivos .h dentro das subpastas
CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -fno-stack-protector -fno-pic -fno-pie -I.
LDFLAGS = -m elf_i386 -T linker.ld

# --- Lista de Objetos (A ordem importa!) ---
# O boot.o PRECISA ser o primeiro para o Multiboot ficar no topo do arquivo
OBJS = boot.o \
       timer.o \
       out.o \
       main.o \
       io.o \
       text.o \
       kernel_utils.o \
       calculator.o \
       stack_check.o \
       idt.o \
       pit.o \
	   panic.o \

# --- Regras Principais ---

all: kernel.bin

kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o kernel.bin $(OBJS)

# --- Pasta: idt (Configuração de Interrupções e Hardware) ---

idt.o: idt/idt.c idt/idt.h
	$(CC) $(CFLAGS) -c idt/idt.c -o idt.o

pit.o: idt/pit.c idt/pit.h
	$(CC) $(CFLAGS) -c idt/pit.c -o pit.o

# --- Pasta: kernel_geral (Utilitários e Sistema) ---
panic.o: panic/panic.c
	$(CC) $(CFLAGS) -c panic/panic.c -o panic.o

io.o: kernel_geral/io.c
	$(CC) $(CFLAGS) -c kernel_geral/io.c -o io.o

text.o: kernel_geral/text.c
	$(CC) $(CFLAGS) -c kernel_geral/text.c -o text.o

# --- Pasta: security_check (O Vigia da Stack) ---

timer.o: security_check/timer.asm
	$(AS) -f elf32 security_check/timer.asm -o timer.o

out.o: security_check/out.asm
	$(AS) -f elf32 security_check/out.asm -o out.o

stack_check.o: security_check/stack_check.c
	$(CC) $(CFLAGS) -c security_check/stack_check.c -o stack_check.o

# --- Pasta: apps (Calculadora e outros) ---

calculator.o: apps/calculator.c
	$(CC) $(CFLAGS) -c apps/calculator.c -o calculator.o

# --- Arquivos da Raiz ---

boot.o: boot.asm
	$(AS) -f elf32 boot.asm -o boot.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

kernel_utils.o: kernel_utils.c
	$(CC) $(CFLAGS) -c kernel_utils.c -o kernel_utils.o

# --- Comandos de Utilidade ---

run:
	qemu-system-i386 -kernel kernel.bin -net none

clean:
	rm -f *.o kernel.bin