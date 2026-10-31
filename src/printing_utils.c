//
// Created by ko-artist on 10/18/26.
//

#include <stdarg.h>
#include "printing_utils.h"
#include "other_utils.h"
#include "vga_driver.h"

void init_printer() {
    vga_clear_screen();
    cursor.x = cursor.y = 0;
}

void print_char(char c) {
    vga_print_char(c, cursor.x, cursor.y);
    cursor.x++;
    if (cursor.x >= VGA_WIDTH) {
        new_line();
    }
}

void print_string(char* s) {
    for (size_t i = 0; s[i] != '\0'; i++) {
        print_char(s[i]);
    }
}

void print_dec(int number) {
    if (number < 0) {
        print_char('-');
        number = -number;
    }
    size_t l = get_num_len_dec(number);
    for (size_t i = l; i-- > 0;) {
        int digit = get_digit_dec(number, i);
        char c = (char) digit + 0x30;
        print_char(c);
    }
}

void print_hex(size_t number) {
    print_char('0');
    print_char('x');
    size_t l = get_num_len_hex(number);
    for (size_t i = l; i-- > 0;) {
        int digit = get_digit_hex(number, i);
        char c = (char) digit;
        if (digit < 10) {
            c += '0';
        } else {
            c += 'a' - 10;
        }
        print_char(c);
    }
}

//todo: make print %
void vprintf(const char* fmt, va_list args) {
    for (size_t i = 0; fmt[i] != '\0'; i++) {
        char c = fmt[i];
        switch (c) {
            case '\n': {
                new_line();
                break;
            }

            case '\r': {
                begin_line();
                break;
            }

            case '%': {
                switch (fmt[i + 1]) {
                    case 'c': {
                        print_char((char)va_arg(args, int));
                        i += 1;
                        break;
                    }

                    case 's': {
                        print_string(va_arg(args, char*));
                        i += 1;
                        break;
                    }
                    case 'd': {
                        print_dec(va_arg(args, int));
                        i += 1;
                        break;
                    }

                    case 'x': {
                        print_hex(va_arg(args, int));
                        i += 1;
                        break;
                    }

                    default: print_char(c);
                }
                break;
            }

            default: print_char(c);
        }
    }
}

void printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}