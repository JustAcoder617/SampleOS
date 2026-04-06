# Variáveis de Compilação
CC = gcc
AS = nasm
LD = ld

# Flags para o Kernel (O segredo está aqui)
CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -fno-stack-protector
LDFLAGS = -m elf_i386 -T linker.ld

# Arquivos (Ajuste os nomes conforme os seus)
OBJS = boot.o kernel.o io.o text.o 

all: kernel.bin

# Compila o Assembly (Bootloader/Entry)
boot.o: boot.asm
	$(AS) -f elf32 boot.asm -o boot.o

# Compila os arquivos C
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Faz o Linkage de tudo usando o script linker.ld
kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o kernel.bin $(OBJS)

# Limpa a sujeira
clean:
	rm -f *.o kernel.bin