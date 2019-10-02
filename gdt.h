#ifndef _GDT_H_
#define _GDT_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" void load_gdtr(uint32_t);
#else
void load_gdtr(uint32_t);
#endif

typedef struct {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;

    // セグメントのアクセス権(s_access, R: read, W: write, X: execute)
    // 0x92: システム専用セグメント。RW_
    // 0x9A: システム専用セグメント。R_X
    // 0xF2: アプリケーション専用セグメント。RW_
    // 0xFA: アプリケーション専用セグメント。R_X
    uint8_t acccess_right;

    uint8_t limit_high;
    uint8_t base_high;
}__attribute__((packed)) gdt_desc;

typedef struct {
    // セグメントの大きさ
    uint16_t size;

    // セグメントの開始番地
    uint32_t base; 
}__attribute__((packed)) gdtr;

#define GDT_LEN 8192
gdt_desc gdt_entries[GDT_LEN];

void gdt_init();
void set_segment_sesc(uint32_t, uint32_t, uint32_t, uint8_t, uint8_t);

#endif
