//
// Created by ko-artist on 11/1/26.
//

#ifndef STRUCTURES_H
#define STRUCTURES_H
#define DEBUG_MODE
#include "synonyms.h"
#include "assert.h"
#pragma pack(push, 1)

typedef struct {
    u16              limit_0_15   : 16;
    u32              base_0_23    : 24;
    u8               type         :  4;
    u8               S            :  1;
    u8               DPL          :  2;
    u8               P            :  1;
    u8               limit_16_19  :  4;
    u8               available_52 :  1;
    u8               L            :  1;
    u8               D_B          :  1;
    u8               G            :  1;
    u8               base_24_31   :  8;

} segment_descriptor;

typedef struct {
    u16     offset_0_15      : 16;
    u16     segment_selector : 16;
    u8      reserved         : 5;
    u8      fixed1           : 1;
    u8      fixed2           : 1;
    u8      fixed3           : 1;
    u8      type             : 3;
    u8      d                : 1;
    u8      fixed4           : 1;
    u8      dpl              : 2;
    u8      p                : 1;
    u16     offset_16_31     : 16;
} interrupt_descriptor;

typedef struct {
    u16     idt_limit     : 16;
    u32     idt_base_addr : 32;
} idt_pseudo_descriptor;
#pragma pack(pop)

typedef struct {
    u32 edi;
    u32 esi;
    u32 ebp;
    u32 esp;
    u32 ebx;
    u32 edx;
    u32 ecx;
    u32 eax;
    u32 gs;
    u32 fs;
    u32 es;
    u32 ds;
    u32 vector;
    u32 error_code;
    u32 eip;
    u32 cs;
    u32 eflags;
} context;
#endif
