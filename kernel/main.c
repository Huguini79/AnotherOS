#include <include/unix/gdt.h>
#include <include/unix/console.h>
#include <include/unix/io.h>
#include <include/unix/traps.h>
#include <include/unix/pic.h>
#include <include/unix/time.h>
#include <include/unix/printk.h>

#define HZ 100

void pit_init()
{
    long divisor = 1193180 / HZ;

    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);
}

extern void kernel_identity_mapping();

void kernel_main()
{
    pit_init();
    time_init();
    remapPIC();
    setUpGdt();
    IdtInstall();
    set_graphics_card(VGA); // Select VGA display (80x25x8bpp)
    init_vga(); // Init VGA display
    kernel_identity_mapping();

    send_char();

    printk("\n\n# ");

    __asm__ volatile ("sti");

    while (1) {}
}