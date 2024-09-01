#ifndef HAL_H_INCLUDED
#define HAL_H_INCLUDED

#include <stdint.h>

void halt();
uint8_t read32(volatile uint8_t* addr);
void write8(volatile uint8_t* addr, uint8_t value);
#endif