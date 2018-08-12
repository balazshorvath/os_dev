#include "types.h"
#include "io.h"
#include "keyboard.h"

#define KEYBOARD_CONF_PORT 0x64
#define KEYBOARD_PORT_READ 0x60


#define KEY_LEFTSHIFT 42
#define KEY_RIGHTSHIFT 54
/*---------------------------------------------------------------------------*/
/* From https://github.com/gsingh93/simple-key-logger/blob/master/key_util.c */
/*---------------------------------------------------------------------------*/
#define UNKNOWN_KEY "\0"

/*
 * The order of the keys is defined in linux/input.h
 */
static char *key_names[112] = {
   UNKNOWN_KEY, "<ESC>",
   "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=",
   "<Backspace>", "<Tab>",
   "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
   "[", "]", "<Enter>", "<LCtrl>",
   "a", "s", "d", "f", "g", "h", "j", "k", "l", ";",
   "'", "`", "<LShift>",
   "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/",
   "<RShift>",
   "<KP*>",
   "<LAlt>", " ", "<CapsLock>",
   "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>",
   "<NumLock>", "<ScrollLock>",
   "<KP7>", "<KP8>", "<KP9>",
   "<KP->",
   "<KP4>", "<KP5>", "<KP6>",
   "<KP+>",
   "<KP1>", "<KP2>", "<KP3>", "<KP0>",
   "<KP.>",
   UNKNOWN_KEY, UNKNOWN_KEY, UNKNOWN_KEY,
   "<F11>", "<F12>",
   UNKNOWN_KEY, UNKNOWN_KEY, UNKNOWN_KEY, UNKNOWN_KEY, UNKNOWN_KEY, UNKNOWN_KEY, UNKNOWN_KEY,
   "<KPEnter>", "<RCtrl>", "<KP/>", "<SysRq>", "<RAlt>", UNKNOWN_KEY,
   "<Home>", "<Up>", "<PageUp>", "<Left>", "<Right>", "<End>", "<Down>",
   "<PageDown>", "<Insert>", "<Delete>"
};

static char *shift_key_names[112] = {
   UNKNOWN_KEY, "<ESC>",
   "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+",
   "<Backspace>", "<Tab>",
   "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
   "{", "}", "<Enter>", "<LCtrl>",
   "A", "S", "D", "F", "G", "H", "J", "K", "L", ":",
   "\"", "~", "<LShift>",
   "|", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?",
   "<RShift>",
   "<KP*>",
   "<LAlt>", " ", "<CapsLock>",
   "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>",
   "<NumLock>", "<ScrollLock>",
   "<KP7>", "<KP8>", "<KP9>",
   "<KP->",
   "<KP4>", "<KP5>", "<KP6>",
   "<KP+>",
   "<KP1>", "<KP2>", "<KP3>", "<KP0>",
   "<KP.>",
   UNKNOWN_KEY, UNKNOWN_KEY, UNKNOWN_KEY,
   "<F11>", "<F12>",
   UNKNOWN_KEY, UNKNOWN_KEY, UNKNOWN_KEY, UNKNOWN_KEY, UNKNOWN_KEY, UNKNOWN_KEY, UNKNOWN_KEY,
   "<KPEnter>", "<RCtrl>", "<KP/>", "<SysRq>", "<RAlt>", UNKNOWN_KEY,
   "<Home>", "<Up>", "<PageUp>", "<Left>", "<Right>", "<End>", "<Down>",
   "<PageDown>", "<Insert>", "<Delete>"
};


/**
 * Determines whether the key code is a shift
 * @param  code the key code to check
 * @return      true if the key is a shift key, false otherwise
 */
uint8_t isShift(uint16_t code) {
   return code == KEY_LEFTSHIFT || code == KEY_RIGHTSHIFT;
}

/**
 * Converts a key code to an ascii character. See linux/input.h for more
 * information
 *
 * @param  code the key code to convert
 * @return      the corresponding ascii character
 */
uint8_t* get_key_text(uint16_t code, uint8_t shift_pressed) {
   //ASSERT_ON_COMPILE(ARRAY_SIZE(key_names) == ARRAY_SIZE(shift_key_names));

   // LOG("%s", shift_pressed ? "true" : "false");
   char **arr;
   if (shift_pressed != 0) {
      arr = shift_key_names;
   } else {
      arr = key_names;
   }

   if (code < 112) {
      return arr[code];
   } else {
      return UNKNOWN_KEY;
   }
}

/*---------------------------------------------------------------------------*/
/* From https://github.com/gsingh93/simple-key-logger/blob/master/key_util.c */
/*---------------------------------------------------------------------------*/

void kb_init() {
    uint8_t data;
    // set scan code set to 0x02
    outb(KEYBOARD_CONF_PORT, 0xF0);
    data = inb(KEYBOARD_CONF_PORT);
    // FA-ACK
    if(data != 0xFA){
        return;
    }
    outb(KEYBOARD_CONF_PORT, 0x02);
    //TODO: Check by sendong 0x00 and then receiving the scancode set (0x02 in this case)

}
/*
 * For more info about keyboard controller:
 * https://www.win.tue.nl/~aeb/linux/kbd/scancodes-11.html
 */
int8_t kb_key_pressed() {
    return inb(KEYBOARD_CONF_PORT) & 0x1;
}
/*
 * For scancodes: http://www.ee.bgu.ac.il/~microlab/MicroLab/Labs/ScanCodes.htm
 */
int8_t kb_get_key_code(){
    return inb(KEYBOARD_PORT_READ);
}

int8_t* kb_get_key_text(){
    return get_key_text((uint16_t) kb_get_key_code(), 0);
}
