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

void kernel_entry() {
    init_printer();
    init_idt();

    timer_ex();
    //exception(0);
    //syscall();

    endless_loop();
}