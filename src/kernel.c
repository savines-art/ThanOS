void endless_loop();

void kernel_entry() {
    *((short int*) 0xB8000) = 0; //0xB8000 - beginning of memory buffer for display controler registers
    endless_loop();
}