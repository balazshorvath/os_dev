#ifndef IO_H
#define IO_H
/*
 * Code from https://github.com/torvalds/linux/blob/master/arch/x86/boot/boot.h
 */


static inline void outb(uint16_t port, uint8_t v) {
	asm volatile("outb %0,%1" : : "a" (v), "dN" (port));
}

static inline uint8_t inb(uint16_t port) {
	uint8_t v;
	asm volatile("inb %1,%0" : "=a" (v) : "dN" (port));
	return v;
}

#endif /*IO_H*/