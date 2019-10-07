all: create

OBJ = terminal.o kernel.o keyboard.o inb_outb.o gdt.o \
      idt.o pic.o interrupt.o keymap.o stdio.o string.o \
	  getmmap.o io.o sysdep.o syscall.o
OBJAS = boot.o gdts.o idts.o interruptas.o

CC = i686-elf-gcc
CCAS = i686-elf-as
CFLAGS = -ffreestanding -O2 -Wall

boot.o: boot.s
	$(CCAS) $^ -o boot.o

terminal.o: terminal.c vga.h terminal.h
	$(CC) -c $< -std=gnu99 $(CFLAGS) -Wextra

kernel.o: kernel.c
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

keyboard.o: keyboard.c keyboard.h
	$(CC) -c $< -std=gnu99 $(CFLAGS) -Wextra

inb_outb.o: inb_outb.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

gdts.o: gdt.s
	$(CCAS) $^ -o gdts.o

gdt.o: gdt.c gdt.h
	$(CC) -c $< -std=gnu99 $(CFLAGS) -Wextra

idts.o: idt.s
	$(CCAS) $^ -o idts.o

idt.o: idt.c idt.h
	$(CC) -c $< -std=gnu99 $(CFLAGS) -Wextra

pic.o: pic.c pic.h
	$(CC) -c $< -std=gnu99 $(CFLAGS) -Wextra

interruptas.o: interrupt.s
	$(CCAS) $^ -o interruptas.o

interrupt.o: interrupt.c interrupt.h
	$(CC) -c $< -std=gnu99 $(CFLAGS) -Wextra

keymap.o: keymap.c keyboard.h
	$(CC) -c $< -std=gnu99 $(CFLAGS) -Wextra

stdio.o: libc_self_made/stdio.c libc_self_made/stdio.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

string.o: libc_self_made/string.c libc_self_made/string.h
	$(CC) -c $< -std=gnu99 $(CFLAGS) -Wextra

getmmap.o: getmmap.c getmmap.h
	$(CC) -c $< -std=gnu99 $(CFLAGS) -Wextra

io.o: libc_self_made/io.c libc_self_made/io.h syscallnum.h
	$(CC) -c $< -std=gnu99 $(CFLAGS) -Wextra

sysdep.o: libc_self_made/sysdep.c libc_self_made/sysdep.h syscallnum.h
	$(CC) -c $< -std=gnu99 $(CFLAGS) -Wextra

syscall.o: syscall.c libc_self_made/sysdep.h syscallnum.h
	$(CC) -c $< -std=gnu99 $(CFLAGS) -Wextra

create: $(OBJAS) $(OBJ)
	$(CC) -T linker.ld -o os.bin $(CFLAGS) -nostdlib *.o -lgcc
	grub2-file --is-x86-multiboot os.bin
	\cp -f os.bin isodir/boot/os.bin
	grub2-mkrescue -o os.iso isodir

clean:
	rm -f *.o *.gch os.bin os.iso
	rm -f libc_self_made/*.gch