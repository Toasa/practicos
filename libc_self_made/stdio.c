#include "stdio.h"

// sm: self-made

int sm_printf(const unsigned char *format, ...) {
    va_list parameter;
    va_start(parameter, format);
    sm_vprintf(format, parameter);
    va_end(parameter);
    return 0;
}

int sm_vprintf(const unsigned char *format, va_list parameter) {
    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == 's') {
                char *str = va_arg(parameter, char *);
                terminal_writestring(str);
            } else if (*format == 'c') {
                // bugあり
                char chara = va_arg(parameter, char);
                terminal_putchar(chara);
            } else if (*format == 'd') {
                int n = va_arg(parameter, size_t);
                terminal_writenum(n, 'd');
            } else if (*format == 'x') {
                int n = va_arg(parameter, size_t);
                terminal_writenum(n, 'x');
            }
        } else {
            terminal_putchar(*format);
        }
        format++;
    }
}