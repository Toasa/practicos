#include "sysdep.h"

// inline アセンブリの記法

// a: EAX register
// b: EBX register
// c: ECX register
// d: EDX register
// D: EDI register
// S: ESI register

// "=a"(ret): EAXの値を変数retへ格納する
// "a"(ret) : 変数retの値をEAXレジスタに格納する

uint32_t system_call1(uint32_t syscall_num, uint32_t arg1) {
    uint32_t ret;
    asm volatile("\tint $0x80\n"
                 : "=a"(ret)
                 :  "a"(syscall_num), "b"(arg1));
    return ret;
}

uint32_t system_call2(uint32_t syscall_num, uint32_t arg1, uint32_t arg2) {
    uint32_t ret;
    asm volatile("\tint $0x80\n"
                 : "=a"(ret)
                 :  "a"(syscall_num), "b"(arg1), "c"(arg2));
    return ret;
}

uint32_t system_call3(uint32_t syscall_num, uint32_t arg1, uint32_t arg2, uint32_t arg3) {
    uint32_t ret;
    asm volatile("\tint $0x80\n"
                 : "=a"(ret)
                 :  "a"(syscall_num), "b"(arg1), "c"(arg2), "d"(arg3));
    return ret;
}

uint32_t system_call4(uint32_t syscall_num, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4) {
    uint32_t ret;
    asm volatile("\tint $0x80\n"
                 : "=a"(ret)
                 :  "a"(syscall_num), "b"(arg1), "c"(arg2), "d"(arg3), "D"(arg4));
    return ret;
}

uint32_t system_call5(uint32_t syscall_num, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5) {
    uint32_t ret;
    asm volatile("\tint $0x80\n"
                 : "=a"(ret)
                 :  "a"(syscall_num), "b"(arg1), "c"(arg2), "d"(arg3), "D"(arg4), "S"(arg5));
    return ret;
}