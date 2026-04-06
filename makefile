CC = gcc
AS = nasm
LD = ld

CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -fno-stack-protector
LDFLAGS = -m elf_i386 -T linker.ld

OBJS = boot.o main.o io.o text.o kernel_utils.o

all: kernel.bin

kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o kernel.bin $(OBJS)
boot.o: boot.asm
	$(AS) -f elf32 boot.asm -o boot.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

kernel_utils.o: kernel_utils.c
	$(CC) $(CFLAGS) -c kernel_utils.c -o kernel_utils.o

io.o: kernel_geral/io.c
	$(CC) $(CFLAGS) -c kernel_geral/io.c -o io.o

text.o: kernel_geral/text.c
	$(CC) $(CFLAGS) -c kernel_geral/text.c -o text.o
run:
	qemu-system-i386 -kernel kernel.bin -append "quiet"
clean:
	rm -f *.o kernel.bin