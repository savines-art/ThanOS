#define DEBUG_MODE
#include "vga_driver.h"
#include "alloc_undead.h"
#include "assert.h"
#include "kernel_panic.h"
#include "memeutils.h"
#include "printing_utils.h"
#include "synonyms.h"
#include "interrupt_handler.h"
#include "experiments.h"

//todo: experiments with different sizes and alignments
void kernel_entry() {
    init_printer();
    init_idt();
    //static_assert(sizeof(u8) == 2, "aaa");

    //assert(1 == 2);
    //size_t alignment = 8;

    /*for (size_t alignment = 1; alignment < 100; alignment++) {
        for (size_t size = 1; size < 513; size++) {
            void* o = malloc_undead(size, alignment);
            assert(!((size_t)o % alignment));
            printf("o: %x \\ %d \n", (size_t) o, -((size_t) o));
        }
    }*/

    timer_ex();
    //shit(0);
    //syscall();
    //int a = 1 / 0;
    //printf("%d", a);

    endless_loop();
}