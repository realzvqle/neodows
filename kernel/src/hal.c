#include "hal.h"
#include <stdint.h>



uint8_t read32(uint8_t* addr) {
    return *((volatile uint8_t *) addr);
}

void write8(volatile uint8_t* addr, uint8_t value) {
    *addr = value;
}

void halt(){
    for(;;){
        asm ("wfi");
    }
}

