//
// Created by ko-artist on 10/19/26.
//

#include <stdarg.h>
#include "kernel_panic.h"
#include "printing_utils.h"

void vkernelpanic(const char* fmt, va_list args) {
    vprintf(fmt, args);
}

void kernelpanic(const char* fmt, ...) {
    clear_interrupt();
    va_list args;
    va_start(args, fmt);
    vkernelpanic(fmt, args);
    va_end(args);
    endless_loop();
}