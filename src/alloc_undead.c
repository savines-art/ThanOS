//
// Created by ko-artist on 10/19/26.
//

#include "memeutils.h"
#include "alloc_undead.h"

#include "kernel_panic.h"

undead_arena arena = {.start = (char*) 0x100000, .current = (char*) 0x100000, .end = (char*) 0x400000};


void* malloc_undead(size_t size, size_t alignment) {
    if (!size) return NULL;

    if ((size_t) arena.current % alignment) {
        arena.current += (alignment - ((size_t) arena.current) % alignment);
    }
    void* ret = arena.current;
    if ((size_t) arena.current + size >= (size_t) arena.end) {
        kernelpanic("Out of memory!\n");
    }
    arena.current += size;
    return ret;
}
void* calloc_undead(size_t size, size_t alignment) {
    if (!size) return NULL;

    void* ret = malloc_undead(size, alignment);
    memzero(ret, size);
    return ret;
}