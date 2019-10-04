#include "keyboard.h"
#include "inb_outb.h"

key_buf kb;

void keyboard_init(void) {
    change_trate_delay(TYPEMATICDELAY_SET2);
    if (enable_keyboard() == 0xFA) {
        terminal_writestring("Keyboard enable... OK\n");
    }
    if (ps2_keyboard_init() == 0) {
        terminal_writestring("Initialize PS/2 Keyboard... OK\n");
    }
}

uint8_t ps2_keyboard_init(void) {
    change_codeset(SCAN_CODE_SET2);
    uint8_t scodeset = getscodeset();
    if (scodeset == 0x43) {
        terminal_writestring("Scan code set 1\n");
    } else if (scodeset == 0x41) {
        terminal_writestring("Scan code set 2\n");
    } else if (scodeset == 0x3F) {
        terminal_writestring("Scan code set 3\n");
    } else {
        terminal_writestring("Unknown scan code set\n");
        return 1;
    }
    outb(KEYBOARD_PORT1, 0xFA);
    return 0;
}

void keyboard_input_int(uint8_t scan_code) {
    uint8_t us_keytable_set2[0x73] = {
        '0', '0', '1', '2', '3', '4', '5', '6', '7', '8',
        '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',
        't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', '0',
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
        '\'', '`', '0', '\\', 'z', 'x', 'c', 'v', 'b', 'n',
        'm', ',', '.', '/', '0', '0', '0', ' ', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0'
    };

    if (scan_code <= 0x80) {
        if (kb.len < 128) {
            kb.pdata[kb.write++] = us_keytable_set2[scan_code];
            kb.len++;
            if (kb.write == 128) {
                kb.write = 0;
            }
        }
    }
}

uint8_t enable_keyboard(void) {
    outb(KEYBOARD_PORT1, ENABLE_KEYBOARD);
    return getscode();
}

uint8_t getscode(void) {
    uint8_t c = 0;

    // こっちではキーが余分に重複して認識される
    // while (1) {
    //     c = inb(KEYBOARD_PORT1);
    //     if (c > 0) {
    //         return c;
    //     }
    // }

    do {
        if (inb(KEYBOARD_PORT1) != c) {
            c = inb(KEYBOARD_PORT1);
            if (c > 0) {
                return c;
            }
        }
    } while (1);
}

uint8_t getchar(void) {
    return getscode();
}

uint8_t getscodeset(void) {
    while (inb(KEYBOARD_PORT2) & 0x02);
    // inb(KEYBOARD_PORT2) & 0x02;

    outb(KEYBOARD_PORT1, SET_SCANCODESET);
    if (getscode() == 0xFA) {
        while (inb(KEYBOARD_PORT2) & 0x02);
        // inb(KEYBOARD_PORT2) & 0x02;

        outb(KEYBOARD_PORT1, 0x00);
        return getscode();
    } else {
        return 0x00;
    }
}

void change_codeset(uint8_t set) {
    outb(KEYBOARD_PORT1, SET_SCANCODESET);
    outb(KEYBOARD_PORT1, set);
}

void change_trate_delay(uint8_t set) {
    while (inb(KEYBOARD_PORT2) & 0x02);
    outb(KEYBOARD_PORT1, SET_TYPEMATIC_RATE);
    while (inb(KEYBOARD_PORT2) & 0x02);
    outb(KEYBOARD_PORT1, set);
}