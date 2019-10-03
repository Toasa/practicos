#include "gdt.h"

void gdt_init() {
    terminal_writestring("Initialize GDT... ");

    gdtr gdt;
    gdt.size = GDT_LEN * sizeof(gdt_desc) - 1;
    gdt.base = (uint32_t)gdt_entries;

    for (int i = 0; i < GDT_LEN; i++) {
        set_segment_desc(i, 0, 0, 0, 0);
    }
    set_segment_desc(1, 0, 0xffffffff, 0x9A, 0xCF);
    set_segment_desc(2, 0, 0xffffffff, 0x92, 0xCF);
    set_segment_desc(3, 0, 0xffffffff, 0xFA, 0xCF);
    set_segment_desc(4, 0, 0xffffffff, 0xF2, 0xCF);

    load_gdtr((uint32_t)(&gdt));

    terminal_writestring("OK\n");
}

// base:  セグメントの開始番地
// limit: セグメントの大きさ
// gran:  granulatiry(粒度)
//        セグメントの属性にgranビットというフラグがあり
//        フラグを立てるとlimitをバイト単位ではなく、
//        ページ単位(4KB)と解釈してくれる
void set_segment_desc(uint32_t index, uint32_t base, uint32_t limit, uint8_t access_right, uint8_t gran) {
    gdt_desc *sg = &gdt_entries[index];

    sg->limit_high = (gran & 0xF0) | ((limit >> 16) & 0x0F);
    sg->limit_low = limit & 0xFFFF;
    sg->base_high = (base >> 24) & 0xFF;
    sg->base_mid = (base >> 16) & 0xFF;
    sg->base_low = base & 0xFFFF;
    sg->acccess_right = access_right;
}