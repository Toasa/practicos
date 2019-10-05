#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define SWITCH_LED         0xED
#define SET_TYPEMATIC_RATE 0xF3
#define ENABLE_KEYBOARD    0xF4
#define SET_SCANCODESET    0xF0

#define SCAN_CODE_SET1 0x01
#define SCAN_CODE_SET2 0x02
#define SCAN_CODE_SET3 0x03

#define TYPEMATICDELAY_SET1 0x01
#define TYPEMATICDELAY_SET2 0x02

#define KEYBOARD_PORT1 0x60
#define KEYBOARD_PORT2 0x64

#define SET_CAPSLOCK_LED  0x60
#define SET_NUMLOCK_LED    0x02
#define SET_SCROLLLOCK_LED 0x01

#define L_SHIFT     0x2A
#define R_SHIFT     0x36
#define CAPS_LOCK   0x3A
#define NUM_LOCK    0x45
#define SCROLL_LOCK 0x46

typedef struct {
    uint8_t pdata[128];
    size_t write;
    size_t read;
    size_t len;
} key_buf;

typedef struct {
    uint8_t base[0x73];
    uint8_t shift[0x73];
    uint8_t numlock[0x73];
} key_map;

typedef struct {
    bool shift_enable:1;
    bool release_enable:1;
    bool caps_lock:1;
    bool num_lock:1;
    bool scr_lock:1;
    uint8_t led_stat;
} kb_stat;

kb_stat ks;
const key_map key_code;
bool ext_input;

void keyboard_init(void);
uint8_t ps2_keyboard_init(void);
void keyboard_input_int(uint8_t);
uint8_t enable_keyboard(void);
uint8_t getscode(void);
uint8_t getchar(void);
uint8_t getscodeset(void);
void change_codeset(uint8_t);
void change_trate_delay(uint8_t);
void switch_kb_led(uint8_t);
void input_bufdata(uint8_t);

#endif