#include "kernel.h"

extern key_buf kb;

void kernel_main(void) {
    terminal_init();
    gdt_init();
    idt_init();
    pic_init();
    keyboard_init();
    terminal_writestring("Howdy? toasa!\n");

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

size_t strlen(const uint8_t *str) {
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}