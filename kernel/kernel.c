#include "terminal.h"

void main(void) {
	init_terminal();
	putstr("Fuck yea.\nNew line");
	putc(getc());
	putstr("Another Fck yea!");
}