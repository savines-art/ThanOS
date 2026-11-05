[BITS 32]

[EXTERN set_interrupt]

[GLOBAL shit]
shit:
    mov eax, 0
    mov ecx, 1
    mov edx, 2
    mov ebx, 3
    mov ebp, 4
    mov esi, 5
    mov edi, 6
    div dword[esp + 4]
    ret

[GLOBAL syscall]
syscall:
    mov eax, 0
    mov ecx, 1
    mov edx, 2
    mov ebx, 3
    mov ebp, 4
    mov esi, 5
    mov edi, 6
    int 0x3
    ret

[GLOBAL timer_ex]
timer_ex:
    mov eax, 0
    mov ecx, 1
    mov edx, 2
    mov ebx, 3
    mov ebp, 4
    mov esi, 5
    mov edi, 6
    call set_interrupt
    ret