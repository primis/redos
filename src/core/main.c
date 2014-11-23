// Red-OS Kernel Main entry point.
// this is where we set up the drivers, then load init.

#include <kernel/vga.h>
#include <kernel/arch/x86/ps2.h>
#include <stdio.h>
#include <kernel/command.h>
#include <kernel/setup.h>
#include <kernel/pit.h>
int main() {

    vgaInit();

    vgaWrite("Setting up the GDT...\t\t\t\t\t");
    gdtInit();
    vgaSetAttribute(0x42);
    vgaWrite("[ OK ]\n");
    vgaSetAttribute(0);

    vgaWrite("Setting up the IDT...\t\t\t\t\t");
    idtInit();
    vgaSetAttribute(0x42);
    vgaWrite("[ OK ]\n");
    vgaSetAttribute(0);

    vgaWrite("Masking Hardware Interrupts...\t\t\t\t");
    vgaSetAttribute(0x42);
    picInit();
    vgaWrite("[ OK ]\n");
    vgaSetAttribute(0);

    vgaWrite("Setting up the Timer at 100Hz...\t\t\t");
    vgaSetAttribute(0x42);
    pitInit(100);
    vgaWrite("[ OK ]\n");
    vgaSetAttribute(0);

    vgaWrite("Setting up Keyboard...\t\t\t\t\t");
    vgaSetAttribute(0x42);
    initKeyboard();
    vgaWrite("[ OK ]\n");
    vgaSetAttribute(0);
    readRTC();
    vgaWrite("\t\t\t    Welcome To Red-OS!\n");
    printf("Boot Time: %d",getTime());
    init_shell();

    for(;;)
        run_shell();
}
