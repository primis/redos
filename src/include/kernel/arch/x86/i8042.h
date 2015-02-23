#ifndef _KERNEL_ARCH_X86_I8042_H 
#define _KERNEL_ARCH_X86_I8042_H
/*
 * Intel 8042 PS/2 Controller 
 */

#define I8042_CMD_PORT          0x60
#define I8042_DATA_PORT         0x64
#define I8042_STATUS_PORT       0x64

/* Status Register Bitsets                                                    */
#define I8042_OUT_BUFFER_FULL   0x01
#define I8042_IN_BUFFER_FULL    0x02
#define I8042_SYSTEM_FLAG       0x04
#define I8042_WRITE_COMMAND     0x08
#define I8042_WRITE_DATA        0x00 /* Unbitset of above Write Command       */
#define I8042_KEY_LOCK          0x10
#define I8042_RECV_TIME_OUT     0x20
#define I8042_TIMEOUT_ERROR     0x40
#define I8042_PARITY_ERROR      0x80

/* Controller Config Byte                                                     */
#define I8042_PORT_1_INTERRUPT  0x01
#define I8042_PORT_2_INTERRUPT  0x02
/* System Flag is the same in both, so no need to redefine                    */
#define I8042_PORT_1_CLOCK_OFF  0x10
#define I8042_PORT_2_CLOCK_OFF  0x20
#define I8042_PORT_TRANSLATION  0x40

/* Controller Output Port                                                     */
#define I8042_SYSTEM_RESET      0x01    /* MAKE SURE ITS ALWAYS SET!          */
#define I8042_A20_GATE          0x02
#define I8042_PORT_2_CLOCK      0x04
#define I8042_PORT_2_DATA       0x08
#define I8042_PORT_1_BUFF_FULL  0x10
#define I8042_PORT_2_BUFF_FULL  0x20
#define I8042_PORT_1_CLOCK      0x40
#define I8042_PORT_1_DATA       0x80

/* Controller Commands                                                        */
#define I8042_READ_BYTE(x)      ((x) + 0x20)
#define I8042_WRITE_BYTE(x)     ((x) + 0x60)
#define I8042_DISABLE_PORT_2    0xA7 /* Dual Only (duh)                       */
#define I8042_ENABLE_PORT_2     0xA8 /* Dual Only                             */
#define I8042_TEST_PORT_2       0xA9 /* Dual Only                             */
#define I8042_TEST_CONTROLLER   0xAA
#define I8042_TEST_PORT_1       0xAB
#define I8042_DIAGNOSTIC_DUMP   0xAC
#define I8042_DISABLE_PORT_1    0xAD
#define I8042_ENABLE_PORT_1     0xAE
#define I8042_READ_INPUT_PORT   0xC0
#define I8042_COPY_LOW_TO_HIGH  0xC1 /* Copy Low Nybble to High Nybble        */
#define I8042_COPY_HIGH_TO_LOW  0xC2 /* Vice Versa                            */
#define I8042_READ_OUTPUT_PORT  0xD0
#define I8042_WRITE_CONTROLLER  0xD1
#define I8042_WRITE_PORT_1      0xD2 /* Dual Only                             */
#define I8042_WRITE_PORT_2      0xD3 /* Dual Only                             */
#define I8042_WRITE_IN_PORT_2   0xD4 /* Dual Only                             */
#define I8042_PULSE_LINES(x)    ((x) | 0xF0) /* x is bitmask of the lines     */
#define I8042_RESET_CPU         0xF0
#endif
