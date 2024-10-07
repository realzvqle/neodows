#include "timer.h"
#include <sys/types.h>


volatile uint64_t CountDown;






uint8_t read_rtc_register(uint8_t reg) {
    outb(0x70, reg); 
    return inb(0x71); 
}

void get_rtc_time(RTC* rtc) {
    cli();
    rtc->seconds = read_rtc_register(0x00);
    rtc->minutes = read_rtc_register(0x02); 
    rtc->hours = read_rtc_register(0x04); 
    rtc->weekday = read_rtc_register(0x06); 
    rtc->day_of_month = read_rtc_register(0x07); 
    rtc->month = read_rtc_register(0x08); 
    rtc->year = read_rtc_register(0x09);  
    sti();
}


uint32_t get_pit_time(){
    return CountDown;
}

void sleep(uint32_t millis) {
    CountDown = millis;
    while (CountDown > 0) {
        halt();
    }
}

void init_pit(uint32_t frequency) {
    uint32_t divisor = 1193180 / frequency; // PIT clock frequency is 1193180 Hz

    cli();
    outb(0x43, 0x36); // Command byte: square wave generator
    outb(0x40, divisor & 0xFF); // Low byte
    outb(0x40, (divisor >> 8) & 0xFF); // High byte
    sti();
}

volatile uint32_t milliseconds = 0;

void pit_handler() {
    milliseconds++; 
    outb(0x20, 0x20);
}