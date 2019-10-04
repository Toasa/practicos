#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "pic.h"
#include "inb_outb.h"

#include <stdint.h>
#include <stddef.h>

void interrupt_done(void);

// IRQ
void keyboard_interrupt(void);

// IRQ number
#define IRQ1 0x61

#endif