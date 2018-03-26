ODIR=out
NASM=nasm
NASM_ARGS=-f elf32
CC=clang
CC_ARGS=-m32 -I./
LINK=ld
LINK_CNF=link.ld
LINK_ARGS=-m elf_i386 -T $(LINK_CNF)

QEMU=qemu-system-i386

KERNEL_BIN=$(ODIR)/kernel.bin

#include *.mk


run: compile
	$(QEMU) -kernel $(KERNEL_BIN)

compile: out_folder kernel_compile

kernel_compile: kernel/kernel.asm kernel/kernel.c video_compile
	$(NASM) kernel/kernel.asm -o $(ODIR)/kernel_asm.o $(NASM_ARGS)
	$(CC) -c kernel/kernel.c -o $(ODIR)/kernel.o $(CC_ARGS)
	$(LINK) -o $(KERNEL_BIN) $(LINK_ARGS) $(ODIR)/kernel_asm.o $(ODIR)/kernel.o $(ODIR)/video.o
#$(wildcard $(ODIR)/*.o)

video_compile: kernel/video.h kernel/video.c kernel/types.h
	$(CC) -c kernel/video.c -o $(ODIR)/video.o $(CC_ARGS)

out_folder:
	mkdir -p $(ODIR)

clean:
	rm -rf $(ODIR)
