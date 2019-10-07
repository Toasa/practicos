#if !defined(_cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>

#include "terminal.h"
#include "keyboard.h"
#include "inb_outb.h"
#include "gdt.h"
#include "pic.h"
#include "idt.h"
#include "interrupt.h"
#include "multiboot.h"
#include "getmmap.h"
#include "libc_self_made/stdio.h"
#include "libc_self_made/string.h"
#include "libc_self_made/io.h"

bool input_line(char *, char *);
void prompt(void);
int execute(char *);