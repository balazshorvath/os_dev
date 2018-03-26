BITS 32
SECTION .text

; Multiboot header
; For this, check https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
; starting from section 3.3.1
	dd		0x1BADB002		; Magic identifier
	dd		0x00			; Flags
	dd		- 0x1BADB002	; Checksum (Magic + Flag + Checksum = 0)

;	
; Later:
;		1. Additional miltiboot headers for paging and graphics
;		2. GDT
;

GLOBAL start
EXTERN main
start:
	CLI			; Clear interrupts
	CALL main	; Main entry
	HLT			; Halt
