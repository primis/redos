// Red-OS Kernel Main entry point.
// this is where we set up the drivers, then load init.

#include <kernel/vga.h>

int main() {
    vgaInit();
    vgaWrite("Hello, World!\n");
    for(;;);
}
