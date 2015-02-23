/*
 * Intel 8042 PS/2 Controller Driver
 */

#include <kernel/arch/x86/i8042.h>
#include <kernel/arch/x86/ps2.h>

void i8042_init()
{
    uint8_t temp;
    int port2;
    outb(I8042_CMD_PORT, I8042_DISABLE_PORT_2);
    outb(I8042_CMD_PORT, I8042_DISABLE_PORT_1);
    temp = inb(I8042_CMD_PORT); /* Flush the Buffer.                         */

    outb(I8042_CMD_PORT, I8042_READ_BYTE(0)); /* Get The Controller Config   */
    temp = inb(I8042_DATA_PORT);

    if(temp & I8042_PORT_2_CLOCK_OFF) {   /* If Set, we have 2 PS/2 ports    */
        port2 = 1;
    } else {
        port2 = 0;
    }

    temp &= ~(
            I8042_PORT_1_INTERRUPT |
            I8042_PORT_2_INTERRUPT |
            I8042_PORT_TRANSLATION
    );
    outb(I8042_CMD_PORT, I8042_WRITE_BYTE(0));
    outb(I8042_DATA_PORT, temp);


    outb(I8042_CMD_PORT, I8042_TEST_CONTROLLER);
    temp = inb(I8042_DATA_PORT);
    if(temp != 0x55) {  /* The PS/2 Controller Did not Pass Self Test        */
        return;
    }

    outb(I8042_CMD_PORT, I8042_TEST_PORT_1);
    temp = inb(I8042_DATA_PORT);
    if(temp == 0) {
        // TODO: Init First Port
    }

    if(port2 != 1) {    /* Only Have one port, don't bother to test the 2nd  */
        return;
    }
    outb(I8042_CMD_PORT, I8042_TEST_PORT_2);
    temp = inb(I8042_DATA_PORT);
    if(temp == 0) {
        // TODO: Init Second Port
    }
}
