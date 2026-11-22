#include <include/unix/io.h>

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

void backspace_vga()
{
    if (x_vga <= 2 && (fb[(y_vga * (VGA_WIDTH)) + (x_vga-2)] & 0xFF) == '#')
    {
        
    } else
    {
        x_vga--;
    }
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

        if (c == '\b')
        {
            fb[(y_vga * VGA_WIDTH) + x_vga] = DEFAULT_FONT << 8 | ' ';
            backspace_vga();
            return;
        }

    if (c != '\n')
    {
        put_c_coord_vga(c, x_vga, y_vga);
        x_vga++;
        fb[(y_vga * VGA_WIDTH) + x_vga] = 0x02 << 8 | '|';
    
    } else
    {
        fb[(y_vga * VGA_WIDTH) + x_vga] = DEFAULT_FONT << 8 | ' ';
        y_vga++;
        x_vga = 0;
        fb[(y_vga * VGA_WIDTH) + x_vga] = 0x02 << 8 | '|';
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

void move_light_cursor_vga()
{
    fb[(y_vga * VGA_WIDTH) + x_vga] = 0x02 << 8 | '|';
}

void delete_light_cursor_vga()
{
    fb[(y_vga * VGA_WIDTH) + x_vga] = 0x02 << 8 | ' ';
}

void put_c_vga_without_increment_x(char c)
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

        if (c == '\b')
        {
            backspace_vga();
            return;
        }

    if (c != '\n')
    {
        put_c_coord_vga(c, x_vga, y_vga);
        //x_vga++;
    
    } else
    {
        fb[(y_vga * VGA_WIDTH) + x_vga] = DEFAULT_FONT << 8 | ' ';
        y_vga++;
        x_vga = 0;
        fb[(y_vga * VGA_WIDTH) + x_vga] = 0x02 << 8 | '|';
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

int saved_x = 0;
int saved_y = 0;

void move_cursor_vga(int x, int y)
{
    saved_x = x_vga;
    saved_y = y_vga;

    x_vga = x;
    y_vga = y;
}

void forward_vga()
{
    x_vga++;
}

void restore_last_pos_cursor()
{
    x_vga = saved_x;
    y_vga = saved_y;
}

void panic_background()
{
    for (int i = 0; i < VGA_HEIGHT * VGA_WIDTH; i++)
    {
        unsigned short copy = fb[i];
        fb[i] = 0x4F << 8 | (copy & 0xFF);
    }
}

void clear_screen()
{
    x_vga = 0;
    y_vga = 0;
    for (int i = 0; i < VGA_HEIGHT; i++)
    {
        for (int j = 0; j < VGA_WIDTH; j++)
        {
            put_c_coord_vga(' ', j, i);
        }
    }
}

void init_vga()
{
    outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
    fb = (unsigned short*)0xB8000;
    clear_screen();
}