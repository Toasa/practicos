#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#include <stdint.h>
#include "libc_self_made/stdio.h"
#include "syscallnum.h"

uint32_t syscall_interrupt(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

#endif