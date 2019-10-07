#include "idt.h"

void idt_init(void) {
    terminal_writestring("Initialize IDT... ");

    idtr idt;
    idt.size = IDT_LEN * sizeof(gate_desc) - 1;
    idt.base = (uint32_t)idt_entries;

    for (size_t i = 0; i < IDT_LEN; i++) {
        set_gate_desc(i, 0, 0, 0);
    }

    set_gate_desc(0x21, (uint32_t)as_keyboard_interrupt, 0x08, 0x8E);
    set_gate_desc(0x80, (uint32_t)as_software_interrupt, 0x08, 0x8F);

    load_idtr((uint32_t)(&idt));

    terminal_writestring("OK\n");
}

void set_gate_desc(uint32_t index, uint32_t offset, uint32_t selector, uint8_t access_right) {
    gate_desc *gd = &idt_entries[index];
    gd->offset_high = (offset >> 16) & 0xFFFF;
    gd->offset_low = offset & 0xFFFF;

    // なぜ上位6,7ビットを立てる必要がある？
    gd->access_right = access_right | 0x60;
    gd->selector = selector & 0xFFFF;
    gd->dw_count = 0;
}