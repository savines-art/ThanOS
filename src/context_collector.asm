[BITS 32]
%define data_segment_selector 8

[EXTERN universal_handler]

[GLOBAL collect_context]
collect_context:
    .save_context:
    push ds
    push es
    push fs
    push gs
    pusha

    .save_registers:
    mov ax, data_segment_selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    cld
    .align_stack:
    mov ebx, esp

    sub esp, 4

    and esp, -16
    add esp, 4
    push ebx
    call universal_handler