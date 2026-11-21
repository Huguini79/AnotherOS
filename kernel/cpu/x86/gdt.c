struct Gdt
{
    unsigned short limit;
    unsigned short base_0_15_bits;
    unsigned char base_16_23_bits;
    unsigned char access_byte;
    unsigned char granularity;
    unsigned char base_24_31_bits;

} __attribute__((packed));

struct Gdtr
{
    unsigned short limit;
    unsigned long base;

} __attribute__((packed));

struct Gdtr gdtr;

struct Gdt gdt_table[8192] __attribute__((aligned(8)));

void setGdtEntry(unsigned long n, unsigned long limit, unsigned long base, unsigned char access_byte, unsigned char flags)
{
    if (n <= 8191)
    {
        struct Gdt* Gdt = &gdt_table[n];
        Gdt->limit = (limit & 0xFFFF);
        Gdt->base_0_15_bits = base & 0xFFFF;
        Gdt->base_16_23_bits = (base >> 16) & 0xFF;
        Gdt->access_byte = access_byte;
        Gdt->granularity = (limit >> 16) & 0x0F;
        Gdt->granularity |= (flags & 0xF0);
        Gdt->base_24_31_bits = (base >> 24) & 0xFF;
    
    } else
    {
        return;
    }
}

void setUpGdt()
{
    setGdtEntry(0, 0, 0, 0, 0);
    setGdtEntry(1, 0xFFFFFFFF, 0, 0x9B, 0xC0);
    setGdtEntry(2, 0xFFFFFFFF, 0, 0x93, 0xC0);

    gdtr.limit = sizeof(gdt_table) - 1;
    gdtr.base = (long)gdt_table;

    __asm__ volatile ("lgdt %0" :: "m"(gdtr));
}