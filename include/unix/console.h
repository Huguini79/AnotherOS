#ifndef CONSOLE_H
#define CONSOLE_H

/* VGA -> vga.c */
/*                                                  */
extern void init_vga();
extern void put_c_coord_vga(char c, int x, int y);
extern void put_c_vga(char c);
extern void put_c_vga_without_increment_x(char c);
extern void clear_screen();
extern void backspace_vga();
extern void forward_vga();
extern void move_light_cursor_vga();
extern void delete_light_cursor_vga();
extern void move_cursor_vga(int x, int y);
extern void restore_last_pos_cursor();
extern void panic_background();
/*                                                  */

/* DISPLAY SERVICE */
/*                                                  */
/* We get to here using de 0x80 syscall, and with the value of 4 in the eax register */
extern void send_char_coord(char c, int x, int y);
extern void send_char(char c);
/*                                                  */

enum GraphicsCard
{
    VGA, /* We are using this for default */
    NVIDIA,
    IBM,
};

extern enum GraphicsCard current_graphics_card;
extern void set_graphics_card(enum GraphicsCard graphics_card);
extern enum GraphicsCard get_current_graphics_card();

#endif