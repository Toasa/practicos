#include "kernel.h"

void kernel_main(void) {
    terminal_init();
    terminal_writestring("Howdy? toasa!\n");
}

size_t strlen(const uint8_t *str) {
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}