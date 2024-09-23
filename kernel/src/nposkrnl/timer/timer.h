#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED







#include "../../HAL/hal.h"


typedef struct _RTC{
    uint32_t seconds;
    uint32_t minutes;
    uint32_t hours;
    uint32_t weekday;
    uint32_t day_of_month;
    uint32_t month;
    uint32_t year;
} RTC;



//void sleep(uint32_t seconds);



uint8_t get_rtc_seconds();
uint32_t get_pit_time();
void get_rtc_time(RTC* rtc);
void init_pit(uint32_t frequency);
void pit_handler();


#endif