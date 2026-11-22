OBJECT_FILES = build/entry.asm.o build/main.o build/gdt.o build/vga.o build/console.o build/io.asm.o build/pic.o build/asm.asm.o build/isr.o build/idt.o build/printk.o build/time.o build/paging.asm.o build/paging.o

CC = gcc
CC_FLAGS = -c -m32 -I./ -nostdlib -ffreestanding
AS = nasm
AS_FLAGS = -f elf32
LD = ld
LD_FLAGS = -m elf_i386 -T linker.ld -o iso/boot/kernel $(OBJECT_FILES)

all:
	$(AS) $(AS_FLAGS) entry.asm -o build/entry.asm.o
	$(AS) $(AS_FLAGS) kernel/cpu/x86/io.asm -o build/io.asm.o
	$(AS) $(AS_FLAGS) kernel/memory/paging.asm -o build/paging.asm.o
	$(AS) $(AS_FLAGS) kernel/cpu/x86/asm.asm -o build/asm.asm.o
	$(CC) $(CC_FLAGS) kernel/main.c -o build/main.o
	$(CC) $(CC_FLAGS) kernel/time.c -o build/time.o
	$(CC) $(CC_FLAGS) kernel/printk.c -o build/printk.o
	$(CC) $(CC_FLAGS) kernel/memory/paging.c -o build/paging.o
	$(CC) $(CC_FLAGS) kernel/cpu/x86/isr.c -o build/isr.o
	$(CC) $(CC_FLAGS) kernel/cpu/x86/idt.c -o build/idt.o
	$(CC) $(CC_FLAGS) kernel/cpu/x86/pic.c -o build/pic.o
	$(CC) $(CC_FLAGS) kernel/graphics/vga/vga.c -o build/vga.o
	$(CC) $(CC_FLAGS) kernel/graphics/console.c -o build/console.o
	$(CC) $(CC_FLAGS) kernel/cpu/x86/gdt.c -o build/gdt.o
	$(LD) $(LD_FLAGS)
	grub-mkrescue -o AnotherOS.iso iso/
	qemu-system-x86_64 -m 4096 AnotherOS.iso