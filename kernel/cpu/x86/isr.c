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

    if (second == 100)
    {
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

    printk("%i:%i:%i\n\n", Time.hour, Time.minutes, Time.seconds);

    }

    outb(0x20, 0x20);
}

void keyboard_handler()
{
    send_char('A');
    outb(0x20, 0x20);
}