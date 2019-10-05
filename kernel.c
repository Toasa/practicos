#include "kernel.h"

extern key_buf kb;
extern size_t prompt_len;
size_t prompt_len;
static size_t cmd_line_pos;

void kernel_main(multiboot_info_t *mbt, uint32_t magic) {
    terminal_init();
    gdt_init();
    idt_init();
    pic_init();
    keyboard_init();
    // getmmap(mbt);
    
    prompt();
}

bool input_line(char *prompt_name, char *cmd_line) {
    asm volatile("cli");
    if (kb.len == 0) {
        asm volatile("sti");
    } else {
        char c = kb.pdata[kb.read];
        kb.len--;
        kb.read++;
        if (kb.read == 128) {
            kb.read = 0;
        }
        asm volatile("sti");

        // commandが確定した場合
        if (c == '\n') {
            cmd_line[cmd_line_pos] = '\0';
            return true;
        // commandが未確定の場合
        } else if (c == '\b') {
            cmd_line[cmd_line_pos] = '\0';
            if (cmd_line_pos > 0) {
                cmd_line_pos--;
            }
        } else {
            cmd_line[cmd_line_pos++] = c;
        }
        terminal_putchar(c);
    }
    return false;
}

bool is_equal_str(char *s1, char *s2) {
    if (sm_strcmp(s1, s2)) {
        return false;
    }
    return true;
}

int execute(char *cmd_line) {
    if (is_equal_str(cmd_line, "clear")) {
        terminal_init();
        return 0;
    } else if (is_equal_str(cmd_line, "reboot")) {
        outb(0x64, 0xFE);
        return 0;
    } else {
        return -1;
    }
}

void prompt(void) {
    bool is_cmd_determined;
    char cmd_line[1024];
    char *prompt_name = "toasa";
    prompt_len = sm_strlen(prompt_name);
    sm_printf("\n%s> ", prompt_name);

    kb.len = 0;
    kb.write = 0;
    kb.read = 0;
    cmd_line_pos = 0;

    for (;;) {
        is_cmd_determined = input_line(prompt_name, cmd_line);
        if (is_cmd_determined) {
            if (0 < cmd_line_pos) {
                if (execute(cmd_line) == -1) {
                    sm_printf("\n  %s: Command not found\n", cmd_line);
                }
                sm_printf("%s> ", prompt_name);
            } else {
                sm_printf("\n%s> ", prompt_name);
            }
            
            cmd_line_pos = 0;
        }
    }
}