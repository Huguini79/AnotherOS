#include <include/unix/io.h>

#define MASTER_PIC_CONTROL 0x20
#define MASTER_PIC_DATA 0x21

#define SLAVE_PIC_CONTROL 0xA0
#define SLAVE_PIC_DATA 0xA1

void remapPIC()
{
    outb(MASTER_PIC_CONTROL, 0x11);
    outb(SLAVE_PIC_CONTROL, 0x11);

    outb(MASTER_PIC_DATA, 0x20);
    outb(SLAVE_PIC_DATA, 0x28);

    outb(MASTER_PIC_DATA, 0x4);
    outb(SLAVE_PIC_DATA, 0x2);

    outb(MASTER_PIC_DATA, 1);
    outb(SLAVE_PIC_DATA, 1);
}