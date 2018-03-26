#include "video.h"
#include "types.h"

uint16* video_segment;
uint16 cursor_x, cursor_y;
uint16 screen_width, screen_height;
uint16 color;

void update_cursor() {
	// About VGA: http://www.osdever.net/FreeVGA/vga/crtcreg.htm
	
	uint32 pos = cursor_y * screen_width + cursor_x;
		
	outb(0x3D4, 14);
	outb(0x3D5, pos >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, pos);
}

uint8 init_video(){
	// TODO: Set the values based on the current mode
	video_segment = (uint8*)0xb8000;
	cursor_x = 0;
	cursor_y = 0;
	screen_height = 25;
	screen_width = 80;
	color = 0x15;
	
	return 0;
}


inline void printc(int8 c) {
	switch(c){
		case '\n':
			cursor_x = 0;
			cursor_y++;
			break;
		case '\r':
			cursor_x = 0;
			break;
		default: {
			uint32 offset = cursor_y * screen_width + cursor_x;
			video_segment[offset] = color << 8 | c;
			cursor_x++;
		}
	}
	update_cursor();
}

