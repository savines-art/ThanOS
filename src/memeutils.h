#ifndef THANOS_MEMEUTILS_H
#define THANOS_MEMEUTILS_H

#include <stddef.h>
void memmove(void* dst, void* src, size_t n);
void memcpy(void* dst, void* src, size_t n);
void memzero(void* dst, size_t n);

#endif //THANOS_MEMEUTILS_H