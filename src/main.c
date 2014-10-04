// Red-OS Kernel Main entry point.
// this is where we set up the drivers, then load init.

#include <kernel/vga.h>
#include <kernel/setup.h>

int main() {
    
    vgaInit();

    vgaWrite("Setting up the GDT...\t\t");
    gdtInit();
    vgaSetAttribute(0x42);
    vgaWrite("[ OK ]\n");
    vgaSetAttribute(0);
    
    vgaWrite("Setting up the IDT...\t\t");
    idtInit();
    vgaSetAttribute(0x42);
    vgaWrite("[ OK ]\n");
    vgaSetAttribute(0);

    vgaWrite("Turning on the PIC's...\t\t");
    vgaSetAttribute(0x42);
    picInit();
    vgaWrite("[ OK ]\n");
    vgaSetAttribute(0);

    vgaWrite("Welcome To Red-OS!\n");
    for(;;);
}
