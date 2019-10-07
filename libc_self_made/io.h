#ifndef _IO_H_
#define _IO_H_

#include <stddef.h>
#include "../syscall.h"
#include "sysdep.h"

size_t sm_write(int, const void *, size_t);

#endif