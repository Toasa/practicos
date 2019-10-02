#ifndef _INB_OUT_H_
#define _INB_OUT_H_

#include <stdint.h>

// 指定したポートからデータを取得する
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// 指定したポートへデータを送る
static inline uint8_t outb(uint16_t port, uint8_t val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

#endif