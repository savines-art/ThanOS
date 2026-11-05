#include "vga_driver.h"

#include "memeutils.h"

vga_cursor cursor;
//todo: define constants
void vga_clear_screen() {
    memzero((void*)VGA_BEGIN, VGA_SIZE);
}

void vga_print_char(char c, size_t x, size_t y) {
    void* addr = (void*)(VGA_BEGIN + SYMBOL_SIZE * (y * VGA_WIDTH + x));
    *((char*) addr) = c;
    *((char*) (addr + 1)) = 0b00001111;
}

//todo: one memmove
void vga_scroll_down() {
    memmove((void*)(VGA_BEGIN),
        (void*)(VGA_BEGIN + SYMBOL_SIZE * VGA_WIDTH),
        VGA_SIZE - (VGA_WIDTH * SYMBOL_SIZE));
    //for (size_t i = 1; i < VGA_HEIGHT; i++) {
    //    memmove((void*)(VGA_BEGIN + SYMBOL_SIZE * VGA_WIDTH * (i - 1)), (void*)(VGA_BEGIN + SYMBOL_SIZE * VGA_WIDTH * i), VGA_WIDTH * SYMBOL_SIZE);
    //}
    memzero((void*)(VGA_BEGIN + SYMBOL_SIZE * VGA_WIDTH * (VGA_HEIGHT - 1)), VGA_WIDTH * SYMBOL_SIZE);
}