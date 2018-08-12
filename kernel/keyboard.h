#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "types.h"
/*
 * For this whole driver: http://www.eecg.toronto.edu/~jayar/ece241_08F/AudioVideoCores/ps2/ps2.html
 * Or: https://wiki.osdev.org/%228042%22_PS/2_Controller
 */
void kb_init();

/*
 * For more info about keyboard controller:
 * https://www.win.tue.nl/~aeb/linux/kbd/scancodes-11.html
 */
int8_t kb_key_pressed();
/*
 * Returns the scancode for the key.
 * For scancodes: http://www.ee.bgu.ac.il/~microlab/MicroLab/Labs/ScanCodes.htm
 */
int8_t kb_get_key_code();

/*
 * Returns the text for the key.
 */
int8_t* kb_get_key_text();

#endif /*KEYBOARD_H*/
