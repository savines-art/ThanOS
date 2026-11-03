[BITS 32]

%define push_eax 50
%define push_imm 68
%define jmp_code 0xE9

[GLOBAL make_trampolin_e]
[GLOBAL make_trampolin_ne]
[EXTERN collect_context]

make_trampolin_ne:
    mov ecx, dword[esp + 4]
    mov edx, dword[esp + 8]
    mov byte[ecx], push_eax
    mov byte[ecx + 1], push_imm
    bswap edx
    mov dword[ecx + 2], edx
    mov dword[ecx + 6], jmp_code
    mov eax, collect_context
    lea edx, [ecx + 11]
    sub eax, edx
    mov dword[ecx + 7], eax
    ret

make_trampolin_e:
    mov ecx, dword[esp + 4]
    mov edx, dword[esp + 8]
    mov byte[ecx], push_imm
    bswap edx
    mov dword[ecx + 1], edx
    mov dword[ecx + 5], jmp_code
    mov eax, collect_context
    lea edx, [ecx + 10]
    sub eax, edx
    mov dword[ecx + 6], eax
    ret
