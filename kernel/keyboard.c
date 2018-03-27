#include "types.h"
#include "io.h"
#include "keyboard.h"

#define KEYBOARD_CONF_PORT 0x64
#define KEYBOARD_PORT_READ 0x60



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
int8_t kb_get_key(){
    return inb(KEYBOARD_PORT_READ);
}
