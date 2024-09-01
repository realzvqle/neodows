#include "hal.h"
#include <stdint.h>



uint8_t read8(volatile uint8_t* addr) {
    return *((volatile uint8_t *) addr);
}

void write8(volatile uint8_t* addr, uint8_t value) {
    *addr = value;
}


uint32_t read32(volatile uint32_t* addr) {
    return *((volatile uint32_t *) addr);
}

void write32(volatile uint32_t* addr, uint32_t value) {
    *((volatile uint32_t *) addr) = value;
}

void halt(){
    for(;;){
        asm ("wfi");
    }
}


void temp_halt(){ 
    asm ("wfi");
}