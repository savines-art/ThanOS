#ifndef THANOS_VGA_DRIVER_H
#define THANOS_VGA_DRIVER_H

#include <stddef.h>
void vga_clear_screen();
void vga_print_char(char c, size_t x, size_t y);
void vga_scroll_down();

typedef struct vga_cursor {
    size_t x;
    size_t y;
} vga_cursor;

extern vga_cursor cursor;

#define VGA_BEGIN 0xB8000
#define VGA_SIZE 0xFA0
#define SYMBOL_SIZE 2
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#endif //THANOS_VGA_DRIVER_H

