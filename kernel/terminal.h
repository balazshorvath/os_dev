#ifndef TERMINAL_H
#define TERMINAL_H

#include "types.h"

void init_terminal();
void run_terminal();

void set_terminal_color(uint16_t color);
void clear_screen();

void putc(int8_t c);
int8_t getc();

void putstr(int8_t* str);
/*
 * Returns the about of bytes read from the keyboard.
 * "size" is the maximum amout of bytes to read (the buffer size most likely).
 */
uint32_t getstr(int8_t* buffer, uint32_t size);

#endif /*TERMINAL_H*/
