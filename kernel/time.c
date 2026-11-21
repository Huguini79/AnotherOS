#include <include/unix/time.h>
#include <include/unix/io.h>

struct Time Time = {0};

unsigned char read_cmos(unsigned char value)
{
    outb(0x70, 0x80|value);
    insb(0x71);
}

unsigned char bcd_to_bin(unsigned char value)
{
    return (value >> 4) * 10 + (value & 0x0F);
}

void time_init()
{
    Time.seconds = bcd_to_bin(read_cmos(0));
    Time.minutes = bcd_to_bin(read_cmos(2));
    Time.hour = bcd_to_bin(read_cmos(4));
    Time.weekday = bcd_to_bin(read_cmos(6));
    Time.day = bcd_to_bin(read_cmos(7));
    Time.month = bcd_to_bin(read_cmos(8));
    Time.year = bcd_to_bin(read_cmos(9));
}