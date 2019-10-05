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
    // 0xE0: 拡張キーフラグ
    if (scan_code == 0xE0) {
        if (!ext_input) {
            ext_input = true;
        } else {
            ext_input = false;
        }
    }

    if (scan_code <= 0x80) {
        if (kb.len < 128) {
            if (scan_code == L_SHIFT || scan_code == R_SHIFT) {
                ks.shift_enable == true;
            } else if (scan_code == CAPS_LOCK && !ks.caps_lock) {
                ks.caps_lock = true;
                ks.led_stat += SET_CAPSLOCK_LED;                            
                switch_kb_led(ks.led_stat);
            } else if (scan_code == CAPS_LOCK && ks.caps_lock) {
                ks.caps_lock = false;
                ks.led_stat -= SET_CAPSLOCK_LED;
                switch_kb_led(ks.led_stat);
            } else if (scan_code == NUM_LOCK && !ks.num_lock) {
                ks.num_lock = true;
                ks.led_stat += SET_NUMLOCK_LED;
                switch_kb_led(ks.led_stat);
            } else if (scan_code == NUM_LOCK && ks.num_lock) {
                ks.num_lock = false;
                ks.led_stat -= SET_NUMLOCK_LED;
                switch_kb_led(ks.led_stat);
            } else if (scan_code == SCROLL_LOCK && !ks.scr_lock) {
                ks.scr_lock = true;
                ks.led_stat += SET_SCROLLLOCK_LED;
                switch_kb_led(ks.led_stat);
            } else if (scan_code == SCROLL_LOCK && ks.scr_lock) {
                ks.scr_lock = false;
                ks.led_stat -= SET_SCROLLLOCK_LED;
                switch_kb_led(ks.led_stat);
            } else {
                input_bufdata(scan_code);
                kb.len++;
                if (kb.write == 128) {
                    kb.write = 0;
                }
            }
        }
    } else {
        scan_code -= 0x80;
        if (scan_code == L_SHIFT || scan_code == R_SHIFT) {
            ks.shift_enable = false;
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
    while (1) {
        c = inb(KEYBOARD_PORT1);
        if (c > 0) {
            return c;
        }
    }

    // do {
    //     if (inb(KEYBOARD_PORT1) != c) {
    //         c = inb(KEYBOARD_PORT1);
    //         if (c > 0) {
    //             return c;
    //         }
    //     }
    // } while (1);
}

uint8_t getchar(void) {
    return getscode();
}

uint8_t getscodeset(void) {
    while (inb(KEYBOARD_PORT2) & 0x02);

    outb(KEYBOARD_PORT1, SET_SCANCODESET);
    if (getscode() == 0xFA) {
        while (inb(KEYBOARD_PORT2) & 0x02);

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

void switch_kb_led(uint8_t set_led) {
    while (inb(KEYBOARD_PORT2) & 0x02);
    outb(KEYBOARD_PORT1, SWITCH_LED);
    while (inb(KEYBOARD_PORT2) & 0x02);
    outb(KEYBOARD_PORT1, set_led);
}

void input_bufdata(uint8_t scan_code) {
    const key_map *key = &key_code;
    uint8_t numpad_data = 0;

    if (ks.num_lock) {
        numpad_data = key->numlock[scan_code];
        ext_input = false;
    }

    if (!numpad_data) {
        if (ext_input && scan_code == 0x35) {
            kb.pdata[kb.write++] = '\0';
        } else if (ks.shift_enable && !ks.caps_lock) {
            kb.pdata[kb.write++] = key->shift[scan_code];
        } else if (!ks.shift_enable && ks.caps_lock) {
            numpad_data = key->base[scan_code];
            if ('a' <= numpad_data && numpad_data <= 'z') {
                kb.pdata[kb.write++] = key->shift[scan_code];
            } else {
                kb.pdata[kb.write++] = key->base[scan_code];
            }
        } else if (ks.shift_enable && ks.caps_lock) {
            numpad_data = key->base[scan_code];
            if ('a' <= numpad_data && numpad_data <= 'z') {
                kb.pdata[kb.write++] = key->base[scan_code];
            } else {
                kb.pdata[kb.write++] = key->shift[scan_code];
            }
        } else {
            kb.pdata[kb.write++] = key->base[scan_code];
        }
    } else {
        kb.pdata[kb.write++] = numpad_data;
    }
}