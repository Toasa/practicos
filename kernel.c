#include "kernel.h"

void kernel_main(void) {
    terminal_init();
    terminal_writestring("Howdy? toasa!\n");
    terminal_writestring("a\n");
    terminal_writestring("bb\n");
    terminal_writestring("ccc\n");
    terminal_writestring("dddd\n");
    terminal_writestring("eeeee\n");
    terminal_writestring("ffffff\n");
    terminal_writestring("ggggggg\n");
    terminal_writestring("hhhhhhhh\n");
    terminal_writestring("iiiiiiiii\n");
    terminal_writestring("hhhhhhhh\n");
    terminal_writestring("ggggggg\n");
    terminal_writestring("ffffff\n");
    terminal_writestring("eeeee\n");
    terminal_writestring("dddd\n");
    terminal_writestring("ccc\n");
    terminal_writestring("bb\n");
    terminal_writestring("a\n");
    terminal_writestring("bb\n");
    terminal_writestring("ccc\n");
    terminal_writestring("dddd\n");
    terminal_writestring("eeeee\n");
    terminal_writestring("ffffff\n");
    terminal_writestring("ggggggg\n");
    terminal_writestring("hhhhhhhh\n");
}

size_t strlen(const uint8_t *str) {
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}