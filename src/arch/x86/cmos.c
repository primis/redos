#include <kernel/arch/x86/cmos.h>

int century_register=0;
uint8_t second, minute, hour;
uint8_t    day,  month;
uint32_t  year;
void readRTC();

/* Each Month represented in Seconds */
int months[12] = {
    0,          28857600,   5097600,
    7776000,    10368000,   13046400,
    15638400,   18316800,   20995200,
    23587200,   26265600,   28857600
};

int getCMOSRegister(int reg)    /* Get a register from the Real Time Clock    */
{
    outb(CMOS_ADDRESS, reg);
    return inb(CMOS_DATA);
}

int getUpdateInProgressFlag()
{
    /* Bit 7 of Status Register A                                             */
    return getCMOSRegister(CMOS_REGISTER_STATUS_A) & CMOS_UPDATE_IN_PROGRESS;
}

int getTime()
{
    readRTC();  /* Make sure the time is up to date.                          */

    int leapDays = ((year - 1972)/4) + 1;   /* How many leap days to add on   */
    int time;

    if ((year/4 == 0) && (month <=2)) {     /* Is it before Feb & a leap year */
            leapDays--;                     /* Leap day didn't happen yet.    */
    }       

    time = second;
    time += (minute * 60);
    time += (hour * 3600);
    time += (day * 86400);
    time += ((year - 1970) * 31536000);     /* EPOCH time.                    */
    time += (leapDays * 86400);
    time += months[month];

    return time;
}

void readRTC()
{
    uint8_t century;
    uint8_t last_second, last_minute, last_hour;
    uint8_t last_day, last_month, last_year, last_century;
    uint8_t register_b;
 
    while(getUpdateInProgressFlag());   /* Wait until cmos is available */
    second  = getCMOSRegister(CMOS_REGISTER_SECONDS);
    minute  = getCMOSRegister(CMOS_REGISTER_MINUTES);
    hour    = getCMOSRegister(CMOS_REGISTER_HOURS);
    day     = getCMOSRegister(CMOS_REGISTER_DAY);
    month   = getCMOSRegister(CMOS_REGISTER_MONTH);
    year    = getCMOSRegister(CMOS_REGISTER_YEAR);
    do {
        last_second = second;
        last_minute = minute;
        last_hour   = hour;
        last_day    = day;
        last_month  = month;
        last_year   = year;
        last_century= century;
        while(getUpdateInProgressFlag());
        second  = getCMOSRegister(CMOS_REGISTER_SECONDS);
        minute  = getCMOSRegister(CMOS_REGISTER_MINUTES);
        hour    = getCMOSRegister(CMOS_REGISTER_HOURS);
        day     = getCMOSRegister(CMOS_REGISTER_DAY);
        month   = getCMOSRegister(CMOS_REGISTER_MONTH);
        year    = getCMOSRegister(CMOS_REGISTER_YEAR);

        if(century_register != 0) {
            century = getCMOSRegister(century_register);
        }
    } while ((last_second != second) || (last_minute != minute) || (last_hour != hour) ||
        (last_day != day) || (last_month != month) || (last_year != year) ||
        (last_century != century) );
    
    register_b = getCMOSRegister(0x0B);
    // Convert from BCD if needed
    if (!(register_b & 0x04)) {
        second = (second & 0x0F) + ((second / 16) * 10);
        minute = (minute & 0x0F) + ((minute / 16) * 10);
        hour = ((hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
        day = (day & 0x0F) + ((day / 16) * 10);
        month = (month & 0x0F) + ((month / 16) * 10);
        year = (year & 0x0F) + ((year / 16) * 10);
        if(century_register != 0) {
           century = (century & 0x0F) + ((century / 16) * 10);
        }
    }
    // Convert 12 hour to 24 Hour Clock
    if (!(register_b & 0x02) && (hour & 0x80)) {
        hour = ((hour & 0x7F) + 12) % 24;
    }
    if(century_register != 0) {
        year += century * 100;
    } else {
        year += 2000;
    }
}

