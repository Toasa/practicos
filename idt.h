#ifndef _IDT_H_
#define _IDT_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" void load_idtr(uint32_t);
#else
extern void load_idtr(uint32_t);
#endif

// IDTの中身
typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t dw_count;
    uint8_t access_right;
    uint16_t offset_high;
}__attribute__((packed)) gate_desc;

typedef struct {
    // IDTの大きさ
    uint16_t size;

    // IDTの開始番地
    uint32_t base;
}__attribute__((packed)) idtr;

#define LIDT    0x000007FF
#define IDT_LEN 256
gate_desc idt_entries[IDT_LEN];

void idt_init(void);

// index:        割り込みのベクタ番号(INT命令のオペランドで指定)
//     0x00 - 0x1F: ソフトウェア割り込みの例外
//                  ゼロ除算、オーバーフローなど
//     0x20 - 0x2f: IRQ0からIRQ15に対応
//                  IRQ0: タイマ割り込み
//                  IRQ1: キーボード割り込み
//                  IRQ2: スレーブ PICからの割り込み
//
// offset:       割り込みで呼びたい関数などのハンドラのアドレスを指定
// selector:     ゲートタイプを指定
void set_gate_desc(uint32_t index, uint32_t offset, uint32_t selector, uint8_t access_right);

#endif