struct Idt
{
    unsigned short isr_0_15_bits;
    unsigned short selector;
    unsigned char reserved;
    unsigned char type_attributes;
    unsigned short isr_16_31_bits;
    
} __attribute__((packed));

struct Idtr
{
    unsigned short limit;
    long base;

} __attribute__((packed));

struct Idtr idtr;

struct Idt idt_table[256] __attribute__((aligned(8)));

extern void zero_stub();
extern void debug_exception_stub();
extern void nmi_interrupt_stub();
extern void breakpoint_stub();
extern void overflow_stub();
extern void bound_range_exceed_stub();
extern void invalid_opcode_stub();
extern void device_not_available_stub();
extern void double_fault_stub();
extern void coprocessor_segment_overrun_stub();
extern void invalid_tss_stub();
extern void segment_not_present_stub();
extern void stack_segment_fault_stub();
extern void general_protection_stub();
extern void page_fault_stub();
extern void x87_fpu_error_stub();
extern void alignment_check_stub();
extern void machine_check_stub();
extern void simd_floating_point_exception_stub();
extern void virtualization_exception_stub();
extern void pit_stub();
extern void keyboard_stub();

void setIdtDescriptor(int n, unsigned char type_attributes, void* isr)
{
    if (n <= 255)
    {
        struct Idt* Idt = &idt_table[n];
        Idt->isr_0_15_bits = (long)isr & 0xFFFF;
        Idt->selector = 0x08;
        Idt->reserved = 0;
        Idt->type_attributes = type_attributes;
        Idt->isr_16_31_bits = (long)isr >> 16 & 0xFFFF;
    
    } else
    {
        return;
    }
}

extern void pit_handler();

void IdtInstall()
{
    setIdtDescriptor(0, 0x8E, zero_stub);
    setIdtDescriptor(0x01, 0x8E, debug_exception_stub);
    setIdtDescriptor(0x02, 0x8E, nmi_interrupt_stub);
    setIdtDescriptor(0x03, 0x8E, breakpoint_stub);
    setIdtDescriptor(0x04, 0x8E, overflow_stub);
    setIdtDescriptor(0x05, 0x8E, bound_range_exceed_stub);
    setIdtDescriptor(0x06, 0x8E, invalid_opcode_stub);
    setIdtDescriptor(0x07, 0x8E, device_not_available_stub);
    setIdtDescriptor(0x08, 0x8E, double_fault_stub);
    setIdtDescriptor(0x09, 0x8E, coprocessor_segment_overrun_stub);
    setIdtDescriptor(0x10, 0x8E, invalid_tss_stub);
    setIdtDescriptor(0x11, 0x8E, segment_not_present_stub);
    setIdtDescriptor(0x12, 0x8E, stack_segment_fault_stub);
    setIdtDescriptor(0x13, 0x8E, general_protection_stub);
    setIdtDescriptor(0x14, 0x8E, page_fault_stub);
    setIdtDescriptor(0x16, 0x8E, x87_fpu_error_stub);
    setIdtDescriptor(0x17, 0x8E, alignment_check_stub);
    setIdtDescriptor(0x18, 0x8E, machine_check_stub);
    setIdtDescriptor(0x19, 0x8E, simd_floating_point_exception_stub);
    setIdtDescriptor(0x20, 0x8E, pit_handler); // OJO: usando la stub de ensamblador da double fault, con handler no pasa
    setIdtDescriptor(0x21, 0x8E, keyboard_stub);

    idtr.limit = sizeof(idt_table) - 1;
    idtr.base = (long)idt_table;

    __asm__ volatile ("lidt %0" :: "m"(idtr));
}