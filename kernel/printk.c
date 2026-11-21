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
        
        } else
        {
            send_char(fmt[i]);
        }
    }
}