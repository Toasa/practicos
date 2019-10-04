#ifndef _PIC_H_
#define _PIC_H_

#include <stdint.h>

// PIC0はマスタPIC(IRQ0 - IRQ7)を
// PIC1はスレーブPIC(IRQ8 - IRQ15)を管理する

// Interrupt Mask Register
// 8ビットがそれぞれIRQ信号の8個に対応しており
// ビットが立っているIRQ信号はPICから無視される
#define PIC0_IMR_PORT  0x21
#define PIC1_IMR_PORT  0xA1

// Initial Control Word
#define PIC0_ICW1_PORT 0x20 // PICのハードウェア的性質
#define PIC0_ICW2_PORT 0x21 // IRQをどの割り込み番号として、
                            // CPUに通知するか決めたもの                            
#define PIC0_ICW3_PORT 0x21 // マスタPICのどのIRQに
                            // スレーブPICを接続するか
#define PIC0_ICW4_PORT 0x21 // PICのハードウェア的性質
#define PIC1_ICW1_PORT 0xA0
#define PIC1_ICW2_PORT 0xA1
#define PIC1_ICW3_PORT 0xA1
#define PIC1_ICW4_PORT 0xA1

// 初期設定が終わるとPICは割り込みを受け付け、通常動作する
// 通常動作時にPICを制御するコマンドをOCW(Operation Command Words)
// という
#define PIC0_OCW2_PORT 0x20
#define PIC1_OCW2_PORT 0xA0

// End of interrupt
#define PIC_EOI        0x20

void pic_init(void);

#endif