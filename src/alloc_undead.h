//
// Created by ko-artist on 10/19/26.
//

#ifndef THANOS_ALLOC_UNDEAD_H
#define THANOS_ALLOC_UNDEAD_H
#include <stddef.h>

typedef struct {
    char* start;
    char* end;
    char* current;
} undead_arena;

extern undead_arena arena;

void* malloc_undead(size_t size, size_t alignment);
void* calloc_undead(size_t size, size_t alignment);

#endif //THANOS_ALLOC_UNDEAD_H
