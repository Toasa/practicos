#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <stdint.h>
#include <stddef.h>

static const size_t VGA_WIDTH  = 80;
static const size_t VGA_HEIGHT = 25;
static size_t t_row;
static size_t t_col;
static uint8_t t_color;
static uint16_t *t_buf;

void terminal_init(void);
void terminal_setcolor(uint8_t);
void terminal_putentryat(uint8_t, uint8_t, size_t, size_t);
void terminal_putchar(uint8_t);
void terminal_write(const uint8_t *, size_t);
void terminal_writestring(const uint8_t *);
void terminal_uponerow(void);

#endif