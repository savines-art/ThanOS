//
// Created by ko-artist on 11/2/26.
//
#include <stddef.h>
#include "alloc_undead.h"
#include "structures.h"
#include "universal_handler.h"
#include "trampolin_maker.h"

#define code_segment_selector 16
#define IDT_SIZE (256 * 8)
#define INTERRUPT_GATE_TYPE 0b110

void load_idt(idt_pseudo_descriptor* pseudo);

_Bool has_err_code(u8 vector) {
    return (vector == 8 || (vector >= 10 && vector <= 14) || vector == 17 || vector == 21);
}

char* create_trampolin(u8 vector) {
    char* tramplin;
    if (has_err_code(vector)) {
        tramplin = (char*) malloc_undead(10, 1);
        make_trampolin_e(tramplin, vector);
    } else {
        tramplin = (char*) malloc_undead(11, 1);
        make_trampolin_ne(tramplin, vector);
    }
    return tramplin;
}

void init_idt() {
    interrupt_descriptor* idt = malloc_undead(sizeof(interrupt_descriptor) * 256, 8);
    for (size_t i = 0; i < 256; i++) {
        char* tramplin = create_trampolin(i);
        idt[i].offset_0_15 = (size_t) tramplin & 0xFFFF;
        idt[i].segment_selector = code_segment_selector; //why???
        idt[i].reserved = idt[i].fixed1 = idt[i].fixed2 = idt[i].fixed3 = 0;
        idt[i].type = INTERRUPT_GATE_TYPE; //why???
        idt[i].d = 1;
        idt[i].fixed4 = 0;
        idt[i].dpl = 0;
        idt[i].p = 1;
        idt[i].offset_16_31 = (size_t) tramplin >> 16;
    }
    u16 limit = IDT_SIZE - 1;
    idt_pseudo_descriptor pseudo;
    pseudo.idt_base_addr = (size_t) idt;
    pseudo.idt_limit = limit;
    load_idt(&pseudo);
}