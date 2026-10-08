[BITS 16]
N equ 0x64000
mov ax, 0
mov ds, ax
mov ax, 0x07E0
mov es, ax ;setting [es : bx] buffer


;preparing stack
cli
xor ax, ax
mov ss, ax
mov sp, 0x7C00

mov cl, 2 ;number of first sector
mov ch, 0 ;number of first cilinder
mov dh, 0 ;number of first head
mov bx, 0x0 ;setting [es : bx]

cnt: dd 0 ;counter of bytes

load:
  mov ah, 0x02
  mov al, 1

  int 0x13 ;reading of chs
  jc print_error ;error if carry

  mov ax, es
  add ax, 0x20 ;increasing [es:bx] by 512
  mov es, ax

  add dword[cnt], 512 ;increasing counter of read bytes
  cmp dword[cnt], N ;comparing with N and finishing if >=
  jae next
  inc cl ;changing coordinates
  cmp cl, 19
  jne .same_head
    mov cl, 1
    inc dh
    cmp dh, 2
    jne .same_cilinder
      inc ch
      mov dh, 0
    .same_cilinder:
  .same_head:
  jmp load



print_error:
  jmp print_error

next:
lgdt [pseudo_descriptor]
cld

mov eax, cr0
or eax, 1
mov cr0, eax

jmp 0x10:first ;tramplin

[BITS 32]
first:
  mov ax, word[data_segment_selector]
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax



[EXTERN kernel_entry]
call kernel_entry


[GLOBAL endless_loop]
endless_loop:
  jmp endless_loop

pseudo_descriptor:
  dw 0x17
  dd gdt

data_segment_selector:
  dw 0x8
  ; 0b0000000000001 0 00
  ; cpl and rpl are 0
  ; table identificator 0 (global descriptor table)
  ; index 1

code_segment_selector:
  dw 16
  ; 0b0000000000010 0 00
  ; cpl and rpl are 0
  ; table identificator 0 (global descriptor table)
  ; index 2

align 8
gdt:
  .null_descriptor: dq 0

  .data_segment_descriptor:
    dw 0xFFFF ;limit 15:00
    dw 0 ;base 15:00
    db 0 ;base 23:16
    db 0b10010010
    ; accessed flag 0
    ; write-enable 1
    ; some heresy 0
    ; executable 0 (data segment)
    ; common segement 1
    ; dpl 0b00
    ; present flag 1
    db 0b11001111
    ; limit 19:16
    ; avaiable 0
    ; l-flag, but we don't use it
    ; some heresy about 16-bit mode
    ; granularity 1
    db 0 ;base 31:24

  .code_segment_descriptor:
    dw 0xFFFF ;limit 15:00
    dw 0 ;base 15:00
    db 0 ;base 23:16
    db 0b10011010
    ; accessed flag 0
    ; read-enable 1
    ; comforming flag 0
    ; executable 1 (code segment)
    ; common segement 1
    ; dpl 0b00
    ; present flag 1
    db 0b11001111
    ; limit 19:16
    ; avaiable 0
    ; l-flag, but we don't use it
    ; some heresy about 16-bit mode
    ; granularity 1
    db 0 ;base 31:24




times 510-($-$$) db 0
dw 0xAA55
