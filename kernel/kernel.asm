; Multiboot header
; For this, check https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
; starting from section 3.3.1
	; dd		0x1BADB002		; Magic identifier
	; dd		0x00			; Flags
	; dd		- 0x1BADB002	; Checksum (Magic + Flag + Checksum = 0)
section .multiboot_header
header_start:
    dd 0xe85250d6                ; magic number
    dd 0                         ; protected mode code
    dd header_end - header_start ; header length

    ; checksum
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    ; required end tag
    dw 0    ; type
    dw 0    ; flags
    dd 8    ; size
header_end:
;	
; Later:
;		1. Additional miltiboot headers for paging and graphics
;		2. GDT
;

PAGE_SIZE 		EQU 0x200000  	; 2MiB
PAGE_DESCRIPTOR	EQU 0b10000011	; 2MiB pages in memory+writable
PAGE_AMOUNT		EQU 512			; 512 * PAGE_SIZE = 1 GiB

GLOBAL start
SECTION .text
BITS 32

EXTERN main
start:
	;
	; The  bottom two bits are "page is in memory" and "writable" respectively
	; Source: https://intermezzos.github.io/book/first-edition/paging.html
	;
	mov EAX, p3_table
	or EAX, 0b11
	mov DWORD [p4_table], EAX
	; Page table 3
	mov EAX, p2_table
	or EAX, 0b11
	mov DWORD [p3_table], EAX
	; Page table 2
	mov ECX, PAGE_AMOUNT
setup_pages_loop:
	mov EAX, PAGE_SIZE
	mul ECX
	or ECX, PAGE_DESCRIPTOR
	mov [p2_table + 8 * ECX], EAX
	loop setup_pages_loop

	; Setup CPU
	mov EAX, p4_table
	mov CR3, EAX
	; PAE Physical Address Extension
	mov EAX, CR4
	or EAX, 1 << 5 ; 0b100000
	mov CR4, EAX
	; Enable paging and set "the CPU can't write to read-only pages when privilege level is 0"
	; https://en.wikipedia.org/wiki/Control_register
	mov EAX, CR0
	or EAX, 1 << 31
	or EAX, 1 << 16
	; This will enable protected mode (should try long mode 64 bit)
	or EAX, 1
	mov CR0, EAX

	lgdt [gdt_zero.pointer]

	mov AX, gdt_zero.data
	mov SS, AX
	mov DS, AX
	mov ES, AX

	cli			; Clear interrupts
	jmp gdt_zero.code:main

;
; BSS section's values will be zero by default, so it's good
;
SECTION .bss

ALIGN 4096

p4_table:
	RESB 4096

p3_table:
	RESB 4096

p2_table:
	RESB 4096
;
; rodata stans for "read only data"
;

SECTION .rodata

gdt_zero:
	DQ 0	;quad word
	; descriptor table | present (this is valid) | read/write | executable | 64 bit
.code: EQU $ - gdt_zero
    DQ (1 << 44) | (1 << 47) | (1 << 41) | (1 << 43) ; This is for 64 bit: | (1<<53)
.data: EQU $ - gdt_zero
    DQ (1 << 44) | (1 << 47) | (1 << 41)
.pointer:
    DW .pointer - gdt_zero - 1
    DQ gdt_zero


