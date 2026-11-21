#include <include/unix/console.h>

enum GraphicsCard current_graphics_card = 0;

enum GraphicsCard get_current_graphics_card()
{
    return current_graphics_card;
}

void set_graphics_card(enum GraphicsCard graphics_card)
{
    current_graphics_card = graphics_card;
}

void vga_char_stub(char c)
{
    put_c_vga(c);
}

void vga_char_coord_stub(char c, int x, int y)
{
    put_c_coord_vga(c, x, y);
}

void send_char(char c)
{
    if (current_graphics_card == VGA)
    {
        vga_char_stub(c);

    } else
    {
        return;
    }
}

void send_char_coord(char c, int x, int y)
{
    if (current_graphics_card == VGA)
    {
        vga_char_coord_stub(c, x, y);

    } else
    {
        return;
    }
}