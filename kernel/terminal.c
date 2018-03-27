#include "types.h"
#include "video.h"
#include "keyboard.h"
#include "terminal.h"

uint16_t cursor_x, cursor_y;

void run_terminal() {
    uint8_t cmd[128];
    while() {

    }
}

void init_terminal(){
    v_init();
    // kb_init();
    cursor_x = 0;
    cursor_y = 0;
}

void set_terminal_color(uint16_t color){
    v_set_color(color);
}

void clear_screen(){
    v_clear_lines(0, v_get_height() - 1);
}

void update_cursor(){
    if(cursor_x >= v_get_width()) {
        cursor_x = 0;
        cursor_y++;
    }
    if(cursor_y >= v_get_height()) {
        cursor_y = v_get_height() - 1;
        v_scroll(VIDEO_SCROLL_UP, 1);
    }
	v_update_cursor(cursor_x, cursor_y);
}

void putc(int8_t c){
	switch(c){
		case '\n':
			cursor_x = 0;
			cursor_y++;
			break;
		case '\r':
			cursor_x = 0;
			break;
		default: {
			v_putc(cursor_x, cursor_y, c);
			cursor_x++;
		}
	}
    update_cursor();
}

int8_t convert_scancode(int8_t sc) {
    if(sc >= 0x02 && sc <= 0x0B){
        return 0x30 + ((sc - 1) % 10);
    }else {
        switch(sc){
            case 0x1C:
                return '\n';
            // Backspace
            case 0x0E:
                return 0x08;
            case 0x10:
                break;
        }
    }
    return 0;
}

int8_t getc(){
    int8_t c;
    while(!kb_key_pressed());
    c = kb_get_key();
    c = convert_scancode(c);
    putc(c);
    return c;
}


void putstr(int8_t* str) {
    if(str == NULL) {
        return;
    }
	while(*str)
		putc(*str++);
}

uint32_t getstr(int8_t* buffer, uint32_t size) {
    if(buffer == NULL || size < 1) {
        return NULL;
    }
    uint32_t bytes = 0;
    do {
        *buffer = getc();
    } while(size > bytes && *buffer++ != '\n');

}
