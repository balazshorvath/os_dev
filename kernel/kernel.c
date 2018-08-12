#include "terminal.h"

void main(void) {
	init_terminal();
	putstr("Fuck yea.\nNew line");
	run_terminal();
	putstr("Another Fck yea!");
}