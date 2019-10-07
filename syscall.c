#include "syscall.h"

uint32_t syscall_interrupt(uint32_t syscall_num,
                           uint32_t arg1,
                           uint32_t arg2,
                           uint32_t arg3,
                           uint32_t arg4,
                           uint32_t arg5) {
    switch(syscall_num) {
    case SYSCALL_WRITE:
        // SYSCALL_WRITE, fd, buffer, byte
        sm_printf("----- SYSTEMCALL -----\n");
        sm_printf("system call num: %d\n", syscall_num);
        sm_printf("file descripter: %d\n", arg1);
        sm_printf("buf: %s\n", arg2);
        sm_printf("byte: %d\n", arg3);
        sm_printf("----- SYSTEMCALL -----\n");
        break;
    case SYSCALL_READ:
        break;
    }
    return 0;
}