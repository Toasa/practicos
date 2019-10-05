#include "kernel.h"

extern key_buf kb;

void kernel_main(multiboot_info_t *mbt, uint32_t magic) {
    terminal_init();
    gdt_init();
    idt_init();
    pic_init();
    keyboard_init();

    getmmap(mbt);

    terminal_writestring("Howdy? toasa!\n");

    sm_printf("I'm %d years old.\n", 1024);
    sm_printf("Lisa is %x years old.\n", 2035);

    char *portal = "This was a triumph";
    sm_strrev(portal);
    sm_printf("%s\n", portal);
    
    keyboard_input_accept();
}

void keyboard_input_accept() {
    kb.len = 0;
    kb.write = 0;
    kb.read = 0;
    for (;;) {
        asm volatile("cli");
        if (kb.len == 0) {
            asm volatile("sti");
        } else {
            c[0] = kb.pdata[kb.read];
            kb.len--;
            kb.read++;
            if (kb.read == 128) {
                kb.read = 0;
            }
            asm volatile("sti");
            terminal_writestring(c);
        }
    }
}