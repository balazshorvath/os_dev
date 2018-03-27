#include "types.h"
#include "video.h"

#define DEF_SCREEN_WIDTH 80
#define DEF_SCREEN_HEIGHT 25

uint16_t* video_segment;
uint16_t screen_width, screen_height;
uint16_t color;

void v_update_cursor(uint16_t cursor_x, uint16_t cursor_y) {
	// About VGA: http://www.osdever.net/FreeVGA/vga/crtcreg.htm
	
	uint32_t pos = cursor_y * screen_width + cursor_x;
		
	outb(0x3D4, 14);
	outb(0x3D5, pos >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, pos);
}

uint8_t v_init(){
	// TODO: Set the values based on the current mode
	video_segment = (uint16_t*)0xb8000;
	screen_height = DEF_SCREEN_HEIGHT;
	screen_width = DEF_SCREEN_WIDTH;
	color = 0x0F;
	
	return 0;
}

void v_set_color(uint16_t c) {
	color = c;
}

inline void v_putc(uint16_t x, uint16_t y, int8_t c) {
	if(x >= screen_width || y >= screen_height) {
		return;
	}
	uint32_t offset = y * screen_width + x;
	video_segment[offset] = color << 8 | c;
}

void v_clear_lines(uint16_t line_from, uint16_t line_to) {
	if(line_to >= screen_height){
		line_to = screen_height - 1;
	}
	uint16_t to = line_to * screen_width;
	for(uint16_t i = line_from; i < to; i++) {
		video_segment[i] = color << 8 | 0x00;
	}
}
void v_clear_screen(){
	v_clear_lines(0, screen_height - 1);
}

void v_scroll(uint8_t direction, uint16_t amount) {
	if(amount < 1){
		return;
	}
	switch(direction) {
		case VIDEO_SCROLL_UP:
			if(amount >= screen_height){
				v_clear_screen();
			}else {
				uint16_t screen_pixels = screen_height * screen_width;
				uint16_t to = 0;
				for(uint16_t from = amount * screen_width; from < screen_pixels; from++) {
					video_segment[to++] = video_segment[from];
				}
				v_clear_lines(screen_height - amount, screen_height);
			}
			break;
		case VIDEO_SCROLL_DOWN:
			if(amount >= screen_height){
				v_clear_screen();
			}
			//TODO
			break;
		case VIDEO_SCROLL_LEFT:
			//TODO
			break;
		case VIDEO_SCROLL_RIGHT:
			//TODO
			break;
	}
}


uint16_t v_get_color() {
	return color;
}

uint16_t v_get_width() {
	return screen_width;
}

uint16_t v_get_height() {
	return screen_height;
}