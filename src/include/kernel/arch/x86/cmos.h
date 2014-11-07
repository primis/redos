#ifndef _KERNEL_ARCH_X86_CMOS_H
#define _KERNEL_ARCH_X86_CMOS_H

#include <stdint.h>
#include <kernel/arch/x86/ports.h>

#define CMOS_DATA                   0x71
#define CMOS_ADDRESS                0x70
/* Registers                          */
#define CMOS_REGISTER_SECONDS       0x00
#define CMOS_REGISTER_MINUTES       0x02
#define CMOS_REGISTER_HOURS         0x04
#define CMOS_REGISTER_DAY           0x07
#define CMOS_REGISTER_MONTH         0x08
#define CMOS_REGISTER_YEAR          0x09
#define CMOS_REGISTER_CENTURY       0x32
#define CMOS_REGISTER_STATUS_A      0x0A
#define CMOS_REGISTER_STATUS_B      0x0B
#define CMOS_REGISTER_STATUS_C      0x0C
#define CMOS_REGISTER_STATUS_D      0x0D
#define CMOS_REGISTER_DIAGNOSTIC    0x0E
#define CMOS_REGISTER_SHUTDOWN      0x0F
#define CMOS_REGISTER_FDD_TYPES     0x10
#define CMOS_REGISTER_SYS_CONFIG    0X11
/* Status A Bitsets                   */
#define CMOS_UPDATE_IN_PROGRESS     0x80
#define CMOS_TIME_FREQ_DIVIDER      0x70
#define CMOS_RATE_FREQ_SELECTOR     0x0F
/* Status B Bitsets                   */
#define CMOS_CLOCK_UPDATE_CYCLE     0x80
#define CMOS_PERIODIC_INTERRUPT     0x40
#define CMOS_ALARM_INTERRUPT        0x20
#define CMOS_UPDATE_ENDED_INTERRUPT 0x10
#define CMOS_ENABLE_SQUARE_WAVE     0x08
#define CMOS_BCD_MODE		    0x04
#define CMOS_24_HOUR_CLOCK          0x02
#define CMOS_DAYLIGHT_SAVINGS_TIME  0x01
/* Status C Bitsets                   */
#define CMOS_IRQF_FLAG              0x80 
#define CMOS_PF_FLAG                0x40
#define CMOS_AF_FLAG                0x20
#define CMOS_UF_FLAG                0x10
/* Floppy Disk Identifiers            */
static char *fdd_CMOS_type[8]={
    "none",         
    "360kB 5.25\"",
    "1.2MB 5.25\"",
    "720kB 3.5\"",
    "1.44MB 3.5\"",
    "2.88MB 3.5\"",
    "Area 51 Disk",/* Reserved        */
    "Your CMOS is Corrupt..."
};

#endif
