//
// Created by ko-artist on 10/20/26.
//

#ifndef THANOS_OTHER_UTILS_H
#define THANOS_OTHER_UTILS_H
#include <stddef.h>

void endless_loop();
int get_digit_dec(int number, size_t i);
int get_digit_hex(int number, size_t i);
size_t get_num_len_dec(int number);
size_t get_num_len_hex(int number);
void begin_line();
void new_line();

#endif //THANOS_OTHER_UTILS_H
