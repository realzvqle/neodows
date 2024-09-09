#include "timer.h"











uint8_t read_rtc_register(uint8_t reg) {
    outb(0x70, reg); 
    return inb(0x71); 
}

uint8_t get_rtc_seconds() {
    return read_rtc_register(0x00); 
}