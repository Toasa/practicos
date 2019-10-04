#include "pic.h"
#include "inb_outb.h"

void pic_init(void) {
    terminal_writestring("Initialize PIC... ");

    outb(PIC0_IMR_PORT, 0xFF);  // IRQ0 - IRQ7のすべての割り込みを無視
    outb(PIC1_IMR_PORT, 0xFF);  // IRQ8 - IRQ15のすべての割り込みを無視

    outb(PIC0_ICW1_PORT, 0x11); // エッジトリガモード
    outb(PIC0_ICW2_PORT, 0x20); // マスタPICの割り込み(IRQ0 - IRQ7)は、
                                // 割り込みベクタ番号の0x20 - 0x27で受け付ける
    outb(PIC0_ICW3_PORT, 0x04); // IRQ2にスレーブPICからの割り込みを処理させる
    outb(PIC0_ICW4_PORT, 0x01); // ノンバッファモード

    outb(PIC1_ICW1_PORT, 0x11); // エッジトリガモード
    outb(PIC1_ICW2_PORT, 0x28); // スレーブPICの割り込み(IRQ8 - IRQ15)は、
                                // 割り込みベクタ番号の0x28 - 0x2fで受け付ける
    outb(PIC1_ICW3_PORT, 0x02); // IRQ2にスレーブPICからの割り込みを処理させる
    outb(PIC1_ICW4_PORT, 0x01); // ノンバッファモード
                                
    outb(PIC0_IMR_PORT, 0xF9);  // 11111001
                                // IRQ1(キーボードコントローラ割り込み)と
                                // IRQ2(スレーブPICからの割り込み)のみ許可する
    outb(PIC1_IMR_PORT, 0xEF);  // 11101111
                                // IRQ12(PS/2マウスからの割り込み)のみ許可する

    terminal_writestring("OK\n");
}