#include <kernel/ports.h>
#define CMOS_DATA    0x71
#define CMOS_ADDRESS 0x70

int32_t century_register = 0x00;
uint8_t second;
uint8_t minute;
uint8_t hour;
uint8_t day;
uint8_t month;
uint8_t year;
void readRTC();

int8_t getCMOSRegister(int8_t _reg)
{
    outb(CMOS_ADDRESS, _reg);
    return inb(CMOS_DATA);
}

int32_t getTime()
{
    readRTC();

    int32_t leapDays = ((year - 1972)/4) + 1;
    int32_t time;
    
    if(year/4 == 0) {
        if(month <=2) {
            leapDays--;
        }
    }       
  
    time = second;
    time += (minute * 60);
    time += (hour * 3600);
    time += (day * 86400);
    time += ((year - 1970) * 31536000);
    time += (leapDays * 86400);
    switch (month) {
        case 12:
            time += 28857600;
            break;
        case 11:
            time += 26265600;
            break;
        case 10:
            time += 23587200;
            break;
        case 9:
            time += 20995200;
            break;
        case 8:
            time += 18316800;
            break;
        case 7:
            time += 15638400;
            break;
        case 6:
            time += 13046400;
            break;
        case 5:
            time += 10368000;
            break;
        case 4: 
            time += 7776000;
            break;
        case 3:
            time += 5097600;
            break;
        case 2: 
            time += 28857600;
            break;
        case 1:
            break;
    }
    return time;
}

void readRTC() 
{
    uint8_t century;
    uint8_t last_second;
    uint8_t last_minute;
    uint8_t last_hour;
    uint8_t last_day;
    uint8_t last_month;
    uint8_t last_year;
    uint8_t last_century;
    uint8_t register_b;
 
//    while(get_update_in_progress_flag());   // Updates mean wrong info
    second  = getCMOSRegister(0x00);
    minute  = getCMOSRegister(0x02);
    hour    = getCMOSRegister(0x04);
    day     = getCMOSRegister(0x07);
    month   = getCMOSRegister(0x08);
    year    = getCMOSRegister(0x09);
    
    if(century_register != 0) {
        century = getCMOSRegister(century_register);
    }
    do {
        last_second = second;
        last_minute = minute;
        last_hour   = hour;
        last_day    = day;
        last_month  = month;
        last_year   = year;
        last_century= century;
//        while(get_update_in_progress_flag());
        second  = getCMOSRegister(0x00);
        minute  = getCMOSRegister(0x02);
        hour    = getCMOSRegister(0x04);
        day     = getCMOSRegister(0x07);
        month   = getCMOSRegister(0x08);
        year    = getCMOSRegister(0x09);
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
            hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
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

