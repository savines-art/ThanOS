//
// Created by ko-artist on 10/19/26.
//

#ifndef THANOS_KERNEL_PANIC_H
#define THANOS_KERNEL_PANIC_H

#include <stdarg.h>
extern void clear_interrupt();
extern void endless_loop();
void kernelpanic(const char* fmt, ...);
void vkernelpanic(const char* fmt, va_list args);

#endif //THANOS_KERNEL_PANIC_H

