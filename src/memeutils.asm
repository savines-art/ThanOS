[BITS 32]

[GLOBAL memmove]
memmove:
    push esi
        push edi
        mov edi, dword[esp + 12]
        mov esi, dword[esp + 16]
        mov ecx, dword[esp + 20]

        cld
        cmp esi, edi
        jae .move
        lea edx, [esi + ecx]
        dec edx
        cmp edi, edx
        ja .move

        std
        mov esi, edx
        add edi, ecx
        dec edi

        .move:
            rep movsb

        pop edi
        pop esi
        cld
        ret

[GLOBAL memcpy]
memcpy:
    push edi
    push esi

    mov edi, dword [esp + 12] ; dst
    mov esi, dword [esp + 16] ; src
    mov ecx, dword [esp + 20] ; size
    cld
    rep movsb

    pop esi
    pop edi
    ret

[GLOBAL memzero]
memzero:
    mov ecx, dword[esp + 4]
    mov edx, dword[esp + 8]
    .loop:
        cmp edx, 0
        jbe .end
        mov byte[ecx], 0
        dec edx
        inc ecx
        jmp .loop
    .end:
    ret

