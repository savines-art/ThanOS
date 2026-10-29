//
// Created by ko-artist on 10/19/26.
//

#ifndef THANOS_PRINTING_UTILS_H
#define THANOS_PRINTING_UTILS_H
#include <stdarg.h>
#include <stddef.h>

void init_printer();
void print_char(char c);
void print_string(char* s);
void print_dec(int number);
void print_hex(size_t number);
void vprintf(const char* fmt, va_list args);
void printf(const char* fmt, ...);

#endif //THANOS_PRINTING_UTILS_H

