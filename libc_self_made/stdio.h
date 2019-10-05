#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>

#include "../terminal.h"

bool PRINTF_LEN_FLAG;

int sm_printf(const unsigned char *format, ...);
int sm_vprintf(const unsigned char *format, va_list parameter);

#endif