#include "vga_driver.h"

#include "memeutils.h"

vga_cursor cursor;

void vga_clear_screen() {
    memzero((void*)0xB8000, 0xFA0);
}

void vga_print_char(char c, size_t x, size_t y) {
    void* addr = (void*)(0xB8000 + 2 * (y * 80 + x));
    *((char*) addr) = c;
    *((char*) (addr + 1)) = cursor.color;
}

void vga_scroll_down() {
    for (size_t i = 1; i < 25; i++) {
        memmove((void*)(0xB8000 + 2 * 80 * (i - 1)), (void*)(0xB8000 + 2 * 80 * i), 80 * 2);
    }
    memzero((void*)(0xB8000 + 2 * 80 * 24), 80 * 2);
}