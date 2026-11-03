[BITS 32]

[GLOBAL shit]
shit:
    div dword[esp + 4]
    ret

[GLOBAL syscall]
syscall:
    int 0x3
    ret