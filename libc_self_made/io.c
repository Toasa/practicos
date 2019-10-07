#include "io.h"

size_t sm_write(int fd, const void *buffer, size_t byte) {
    return system_call(SYSCALL_WRITE, fd, buffer, byte);
}