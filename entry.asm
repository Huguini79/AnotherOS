BITS 32

section .multiboot

align 4
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002 + 0x00)

section .text

global start
extern kernel_main

start:
    cli
    push dword 0x202
    popfd
    call kernel_main
    hlt

section .bss
stack_space: resb 65535