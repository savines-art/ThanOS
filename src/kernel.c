#define DEBUG_MODE
#include "vga_driver.h"
#include "alloc_undead.h"
#include "assert.h"
#include "kernel_panic.h"
#include "memeutils.h"
#include "other_utils.h"
#include "printing_utils.h"


void kernel_entry() {
    init_printer();

    //assert(1 == 2);
    int alignment = 10;
    while (1) {
        void* o = malloc_undead(1024, alignment);
        assert(!((size_t)o % alignment));
        printf("o: %x \\ %d \n", (size_t) o, (size_t) o);
    }

    printf("End!");

    endless_loop();
}