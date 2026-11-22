#include <include/libc/string.h>
#include <include/unix/console.h>
#include <include/unix/printk.h>
#include <include/unix/io.h>
#include <include/unix/time.h>

#include <stdint.h>
#include <stddef.h>

void panic(const char* str)
{
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++)
    {
        send_char(str[i]);
    }

    panic_background();
    while (1) {}
}

void zero_handler()
{
    panic("KERNEL PANIC: DIVIDE BY ZERO ERROR");
}

void debug_exception_handler()
{
    panic("KERNEL PANIC: DEBUG EXCEPTION");

}
void nmi_interrupt_handler()
{
    panic("KERNEL PANIC: NMI INTERRUPT");

}
void breakpoint_handler()
{
    panic("KERNEL PANIC: BREAKPOINT");

}
void overflow_handler()
{
    panic("KERNEL PANIC: OVERFLOW");

}
void bound_range_exceed_handler()
{
    panic("KERNEL PANIC: BOUND RAGE EXCEED");
}
void invalid_opcode_handler()
{
    panic("KERNEL PANIC: INVALID OPCODE");

}
void device_not_available_handler()
{
    panic("KERNEL PANIC: DEVICE NOT AVAILABLE");

}
void double_fault_handler()
{
    panic("KERNEL PANIC: DOUBLE FAULT");

}
void coprocessor_segment_overrun_handler()
{
    panic("KERNEL PANIC: COPROCESSOR SEGMENT OVERRUN");

}
void invalid_tss_handler()
{
    panic("KERNEL PANIC: INVALID TSS");

}
void segment_not_present_handler()
{
    panic("KERNEL PANIC: SEGMENT NOT PRESENT");

}
void stack_segment_fault_handler()
{
    panic("KERNEL PANIC: STACK SEGMENT FAULT");

}
void general_protection_handler()
{
    panic("KERNEL PANIC: GENERAL PROTECTION");

}
void page_fault_handler()
{
    panic("KERNEL PANIC: PAGE FAULT");

}
void x87_fpu_error_handler()
{
    panic("KERNEL PANIC: X87 FPU ERROR");

}
void alignment_check_handler()
{
    panic("KERNEL PANIC: ALIGNMENT CHECK");

}
void machine_check_handler()
{
    panic("KERNEL PANIC: MACHINE CHECK");

}
void simd_floating_point_exception_handler()
{
    panic("KERNEL PANIC: SIMD FLOATING POINT EXCEPTION");

}
void virtualization_exception_handler()
{
    panic("KERNEL PANIC: VIRTUALIZATION EXCEPTION");

}

volatile long jiffies = 0;
volatile long second = 0;

extern void clear_screen();

void pit_handler()
{
    jiffies += 1;
    second += 1;

    if (second == 50)
    {
        move_light_cursor_vga();
    }

    if (second == 100)
    {
        delete_light_cursor_vga();
        Time.seconds++;

        if (Time.seconds == 60)
        {
            Time.seconds = 0;
            Time.minutes++;
        }

         if (Time.minutes == 60)
        {
            Time.seconds = 0;
            Time.minutes = 0;
            Time.hour++;

        }

        
        if (Time.hour == 24)
        {
            Time.hour = 0;
            Time.minutes = 0;
            Time.seconds = 0;
        }

        second = 0;

        // clear_screen();

    //move_cursor_vga((80/2) - 6, 0);
    printk("\033[H");
    printk("%i:%i:%i", Time.hour, Time.minutes, Time.seconds);
    for (int i = 0; i < 80-8; i++)
    {
        printk("_");
    }
    delete_light_cursor_vga();
    restore_last_pos_cursor();

    }

    outb(0x20, 0x20);
}

char keyboard_buf[1024];
int pos = 0;

void add_character(char c)
{
    keyboard_buf[pos++] = c;
    keyboard_buf[pos] = 0;
}

void del_character()
{
    pos--;
    keyboard_buf[pos] = 0;
}

void keyboard_handler()
{
    unsigned char scancode = insb(0x60);

    const char scancode_to_ascii[128] = {
        0,   27,  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 0x00 - 0x0E
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',    // 0x0F - 0x1C
        0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',          // 0x1D - 0x29
        0,  '\\','z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,           // 0x2A - 0x36
    '*',   0, ' '                                                              // 0x37 - 0x39
    };

    if (scancode & 0x80)
    {

    } else
    {
        send_char(scancode_to_ascii[scancode]);

        if (scancode_to_ascii[scancode] == '\b')
        {
            del_character();
            put_c_vga_without_increment_x(' ');
            move_light_cursor_vga();

        } else if (scancode_to_ascii[scancode] == '\n')
        {
            if (strncmp(keyboard_buf, "help", 4) == 0)
            {
                printk("date echo clear triangle\n");
            
            } else if (strncmp(keyboard_buf, "date", 4) == 0)
            {
                printk("%i:%i:%i\n", Time.hour, Time.minutes, Time.seconds);
            
            } else if (strncmp(keyboard_buf, "echo", 4) == 0)
            {
                size_t len = strlen(keyboard_buf);

                for (size_t i = 5; i < len; i++)
                {
                    send_char(keyboard_buf[i]);
                }

                printk("\n");
            
            } else if (strncmp(keyboard_buf, "triangle", 8) == 0)
            {
                int y = 1;
                for (int i = 5; i > 0; i--)
                {
                    for (int j = 0; j < i; j++)
                    {
                        printk(" ");
                    }

                    for (int j = 0; j < y; j++)
                    {
                        printk("*");
                    }

                    y += 2;
                    printk("\n");

                    printk("\n");
                }
            }
            
            else if (strncmp(keyboard_buf, "clear", 5) == 0)
            {
                clear_screen();
                move_cursor_vga(0, 0);
            }
            
            else if (strncmp(keyboard_buf, "", 1) == 0)
            {
                
            }
            
            else
            {
                size_t len = strlen(keyboard_buf);
                for (size_t i = 0; i < len; i++)
                {
                    send_char(keyboard_buf[i]);
                }

                printk(": command not found\n", keyboard_buf);
            }

            send_char('#');
            send_char(' ');
            keyboard_buf[0] = 0;
            pos = 0;

        } else
        {
            add_character(scancode_to_ascii[scancode]);
        }
    }

    outb(0x20, 0x20);
}