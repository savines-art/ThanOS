//
// Created by ko-artist on 11/1/26.
//
#include "structures.h"
#include "kernel_panic.h"
void universal_handler(context* ctx) {
    kernelpanic("Kernel panic: unhandled interrupt #%d at %x : %x\n"
                "\n"
                "Registers:\n"
                "EAX: %x, ECX: %x, EDX: %x, EBX: %x\n"
                "ESP: %x, EBP: %x, ESI: %x, EDI: %x\n"
                "DS: %x, ES: %x, FS: %x, GS: %x\n"
                "\n"
                "Error code:\n"
                "common error code, value: %x\n"
                "EFLAGS:\n"
                "value: %x\n",
                ctx->vector, ctx->cs, ctx->eip,
                ctx->eax, ctx->ecx, ctx->edx, ctx->ebx,
                ctx->esp, ctx->ebp, ctx->esi, ctx->edi,
                ctx->ds, ctx->es, ctx->fs, ctx->gs,
                ctx->error_code,
                ctx->eflags);
}
