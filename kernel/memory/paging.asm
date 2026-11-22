global load_page_directory
global enable_paging

enable_paging:
    mov ebx, cr0
    or ebx, (1 << 31)
    mov cr0, ebx
    ret

load_page_directory:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]
    mov cr3, eax

    pop ebp
    ret