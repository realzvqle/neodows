#include "timer.h"
#include "hal.h"
#include <stdint.h>



static volatile uint32_t *timermem = (uint32_t *) 0x09010000; 


uint32_t get_timer_value() {
    return read32(timermem);  
}

void sleep(uint32_t seconds) {
    uint32_t start_time = get_timer_value();
    uint32_t target_time = start_time + seconds;
    while (get_timer_value() < target_time) {
        continue;  
    }
}