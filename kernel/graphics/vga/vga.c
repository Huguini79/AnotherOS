#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define DEFAULT_FONT 0x0F

int x_vga = 0;
int y_vga = 0;
unsigned short* fb;

void scroll()
{
    for (int i = VGA_WIDTH; i < VGA_WIDTH * VGA_HEIGHT; i++)
    {
        fb[i-VGA_WIDTH] = fb[i];
    }

    for (int i = VGA_WIDTH * (VGA_HEIGHT - 1); i < VGA_WIDTH * VGA_HEIGHT; i++)
    {
        fb[i] = DEFAULT_FONT << 8 | ' ';
    }
}

void put_c_coord_vga(char c, int x, int y)
{
    fb[(y * VGA_WIDTH) + x] = DEFAULT_FONT << 8 | c;
}

void put_c_vga(char c)
{

     if (x_vga >= VGA_WIDTH)
        {
            x_vga = 0;
            y_vga++;

        }

        if (y_vga >= VGA_HEIGHT)
        {
            scroll();
            x_vga = 0;
            y_vga = (VGA_HEIGHT - 1);
        }

    if (c != '\n')
    {
        put_c_coord_vga(c, x_vga, y_vga);
        x_vga++;
    
    } else
    {
        y_vga++;
        x_vga = 0;
    }

     if (x_vga >= VGA_WIDTH)
        {
            x_vga = 0;
            y_vga++;

        }

        if (y_vga >= VGA_HEIGHT)
        {
            scroll();
            x_vga = 0;
            y_vga = (VGA_HEIGHT - 1);
        }
}

void clear_screen()
{
    for (int i = 0; i < VGA_HEIGHT; i++)
    {
        for (int j = 0; j < VGA_WIDTH; j++)
        {
            put_c_coord_vga(' ', i, j);
        }
    }
}

void init_vga()
{
    fb = (unsigned short*)0xB8000;
    clear_screen();
}