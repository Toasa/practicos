#include "interrupt.h"

void interrupt_done(void) {
    outb(PIC0_ICW1_PORT, PIC_EOI);
    outb(PIC1_ICW1_PORT, PIC_EOI);
}

void keyboard_interrupt(void) {
    outb(PIC0_ICW1_PORT, IRQ1);
    keyboard_input_int(getchar());
    interrupt_done();
}