all: create

boot.o: boot.s
	i686-elf-as boot.s -o boot.o

terminal.o: terminal.h terminal.c vga.h
	i686-elf-gcc -c terminal.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra

kernel.o: kernel.c
	i686-elf-gcc -c kernel.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra

create: boot.o terminal.o kernel.o
	i686-elf-gcc -T linker.ld -o os.bin -ffreestanding -O2 -nostdlib *.o -lgcc
	grub2-file --is-x86-multiboot os.bin
	\cp -f os.bin isodir/boot/os.bin
	grub2-mkrescue -o os.iso isodir

clean:
	rm -f *.o os.bin