//
// Created by ko-artist on 10/19/26.
//

#ifndef THANOS_KERNEL_PANIC_H
#define THANOS_KERNEL_PANIC_H

extern void clear_interrupt();
extern void endless_loop();
void kernelpanic(const char* fmt, ...);

#endif //THANOS_KERNEL_PANIC_H

