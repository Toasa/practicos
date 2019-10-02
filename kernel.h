#if !defined(_cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>

#include "terminal.h"
#include "keyboard.h"
#include "inb_outb.h"

size_t strlen(const uint8_t*);

#if defined(__cplusplus)
us_keytableextern "C"
#endif