#ifndef VIDEO_H
#define VIDEO_H

#include "types.h"
#include "io.h"

#define VIDEO_SCROLL_UP     1
#define VIDEO_SCROLL_DOWN   2
#define VIDEO_SCROLL_LEFT   3
#define VIDEO_SCROLL_RIGHT  4

uint8_t v_init();
void v_set_color(uint16_t c);
void v_putc(uint16_t x, uint16_t y, int8_t c);
void v_update_cursor(uint16_t cursor_x, uint16_t cursor_y);
void v_clear_screen();
void v_scroll(uint8_t direction, uint16_t amount);
void v_clear_lines(uint16_t line_from, uint16_t line_to);

uint16_t v_get_color();
uint16_t v_get_width();
uint16_t v_get_height();

#endif /*VIDEO_H*/
