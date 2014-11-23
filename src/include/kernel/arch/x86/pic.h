#ifndef _KERNEL_ARCH_X86_PIC_H
#define _KERNEL_ARCH_X86_PIC_H
/* 8259 Programmable Interrupt Controller                                     */

/* ICW Stands for Initilizatoin Command Word                                  */
#define PIC1            0x20
#define PIC2            0xA0
#define PIC1_CMD        PIC1
#define PIC1_DATA      (PIC1+1)
#define PIC2_CMD        PIC2
#define PIC2_DATA      (PIC2+1)


/* Bitsets for ICW1 - Named for their enabled position                        */
#define ICW1_ICW4       0x01 /* ICW4 Enable Bit                               */
#define ICW1_SINGLE     0x02 /* Single PIC Mode (Cascade Disable)             */
#define ICW1_INTERVAL4  0x04 /* Address Interval, 4 or 8 byte Vectors         */
#define ICW1_LEVEL      0x08 /* Line Level Trigger instead of edge triggered  */
#define ICW1_INIT       0x10 /* Start Init Sequence Flag                      */

/* Bitsets for ICW4                                                           */
#define ICW4_8086       0x01 /* 8086 mode if Enabled, 8085 mode if disabled   */
#define ICW4_AUTO       0x02 /* Auto End of interrupt if Enabled.             */
#define ICW4_MASTER     0x04 /* Master PIC if 1, Slave if 0                   */
#define ICW4_SFNM       0x08 /* Special Fully Nested Mode                     */

/* Commands                                                                   */
#define PIC_EOI         0x20 /* End of Interrupt Command                      */
#define PIC_INIT        (ICW1_INIT+ICW1_ICW4) /* Start Init Sequence          */
#define PIC_READ_IRR    0x0A /* Get Value of IRQ Request Register             */
#define PIC_READ_ISR    0x0B /* Get Value of the IRQ In Service Register      */

#endif
