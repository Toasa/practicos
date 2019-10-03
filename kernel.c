#include "kernel.h"

void kernel_main(void) {
    terminal_init();
    gdt_init();
    idt_init();
    pic_init();
    keyboard_init();
    terminal_writestring("Howdy? toasa!\n");
    keyboard_input_int();
}

size_t strlen(const uint8_t *str) {
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}