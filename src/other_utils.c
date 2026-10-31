//
// Created by ko-artist on 10/20/26.
//

#include <stddef.h>
#include "vga_driver.h"

//todo: move to printutils
size_t get_num_len_dec(int number) {
    size_t ret = 0;
     do {
        ret++;
        number /= 10;
    } while (number);
    return ret;
}

size_t get_num_len_hex(int number) {
    size_t ret = 0;
    do {
        ret++;
        number = number >> 4;
    } while (number);
    return ret;
}

int get_digit_dec(int number, size_t i) {
    int first = 10;
    for (size_t j = 0; j < i; j++) {
        first = first * 10;
    }
    number = number % first;
    number = number * 10 / first;
    return number;
}

int get_digit_hex(int number, size_t i) {
    return (number >> 4 * i) & 0xF;
}

void begin_line() {
    cursor.x = 0;
}

void new_line() {
    begin_line();
    cursor.y++;
    if (cursor.y >= VGA_HEIGHT) {
        cursor.y = VGA_HEIGHT - 1;
        vga_scroll_down();
    }
}
