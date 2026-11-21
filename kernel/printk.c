#include <stdarg.h>
#include <include/unix/console.h>
#include <include/libc/string.h>

void printk(const char* fmt, ...)
{
    va_list args;
    char buf[16];
    size_t len = strlen(fmt);
    va_start(args, fmt);

    for (size_t i = 0; i < len; i++)
    {
        if (fmt[i] == '%')
        {
            i++;
            if (fmt[i] == 'i')
            {
                int arg = va_arg(args, int);
                itoa(arg, buf, 10);
                printk(buf);
            }
        
        } else if (fmt[i] == '\033' || fmt[i] == '\e')
        {
            i++;
            if (fmt[i] == '[')
            {
                i++;

                if (fmt[i] == 'H')
                {
                    move_cursor_vga(0, 0);
                
                } else if (fmt[i] == '2')
                {
                    i++;
                    if (fmt[i] == 'J')
                    {
                        clear_screen();
                    
                    }

                }
            }
        } else if (fmt[i] == '\b')
        {
            backspace_vga();
        }
        
        else
        {
            send_char(fmt[i]);
        }
    }
}