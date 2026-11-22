#define KERNEL_MAPING_FLAGS 3

unsigned long kernel_page_directory[1024] __attribute__ ((aligned(4096)));
unsigned long kernel_page_tables[1024][1024] __attribute__((aligned(4096)));

extern void load_page_directory(unsigned long page_directory);
extern void enable_paging();

void kernel_identity_mapping()
{
    unsigned long offset = 0;

    for (int i = 0; i < 1024; i++)
    {
        for (int j = 0; j < 1024; j++)
        {
            kernel_page_tables[i][j] = offset | KERNEL_MAPING_FLAGS;
            offset += 4096;
        }

        kernel_page_directory[i] = (unsigned long)kernel_page_tables[i] | KERNEL_MAPING_FLAGS;
    }

    load_page_directory((unsigned long)kernel_page_directory);
    enable_paging();
}