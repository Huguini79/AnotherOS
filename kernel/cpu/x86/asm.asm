BITS 32

extern zero_handler
global zero_stub

extern debug_exception_handler
global debug_exception_stub

extern nmi_interrupt_handler
global nmi_interrupt_stub

extern breakpoint_handler
global breakpoint_stub

extern overflow_handler
global overflow_stub

extern bound_range_exceed_handler
global bound_range_exceed_stub

extern invalid_opcode_handler
global invalid_opcode_stub

extern device_not_available_handler
global device_not_available_stub

extern double_fault_handler
global double_fault_stub

extern coprocessor_segment_overrun_handler
global coprocessor_segment_overrun_stub

extern invalid_tss_handler
global invalid_tss_stub

extern segment_not_present_handler
global segment_not_present_stub

extern stack_segment_fault_handler
global stack_segment_fault_stub

extern general_protection_handler
global general_protection_stub

extern page_fault_handler
global page_fault_stub

extern x87_fpu_error_handler
global x87_fpu_error_stub

extern alignment_check_handler
global alignment_check_stub

extern machine_check_handler
global machine_check_stub

extern simd_floating_point_exception_handler
global simd_floating_point_exception_stub

extern virtualization_exception_handler
global virtualization_exception_stub

extern pit_handler
global pit_stub

extern keyboard_handler
global keyboard_stub

zero_stub:
    pushad
    call zero_handler
    popad
    iretd

debug_exception_stub:
    pushad
    call debug_exception_handler
    popad
    iretd

nmi_interrupt_stub:
    pushad
    call nmi_interrupt_handler
    popad
    iretd

breakpoint_stub:
    pushad
    call breakpoint_handler
    popad
    iretd

overflow_stub:
    pushad
    call overflow_handler
    popad
    iretd

bound_range_exceed_stub:
    pushad
    call bound_range_exceed_handler
    popad
    iretd

invalid_opcode_stub:
    pushad
    call invalid_opcode_stub
    popad
    iretd

device_not_available_stub:
    pushad
    call device_not_available_handler
    popad
    iretd

double_fault_stub:
    pushad
    call double_fault_handler
    popad
    iretd

coprocessor_segment_overrun_stub:
    pushad
    call coprocessor_segment_overrun_handler
    popad
    iretd

invalid_tss_stub:
    pushad
    call invalid_tss_handler
    popad
    iretd

segment_not_present_stub:
    pushad
    call segment_not_present_handler
    popad
    iretd

stack_segment_fault_stub:
    pushad
    call stack_segment_fault_handler
    popad
    iretd

general_protection_stub:
    pushad
    call general_protection_handler
    popad
    iretd

page_fault_stub:
    pushad
    call page_fault_handler
    popad
    iretd

x87_fpu_error_stub:
    pushad
    call x87_fpu_error_stub
    popad
    iretd

alignment_check_stub:
    pushad
    call alignment_check_stub
    popad
    iretd

machine_check_stub:
    pushad
    call machine_check_handler
    popad
    iretd

simd_floating_point_exception_stub:
    pushad
    call simd_floating_point_exception_handler
    popad
    iretd

virtualization_exception_stub:
    pushad
    call virtualization_exception_handler
    popad
    iretd

pit_stub:
    pushad
    push esp
    call pit_handler
    popad
    iret

keyboard_stub:
    pushad
    call keyboard_handler
    popad
    iretd