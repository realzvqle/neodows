#ifndef HAL_H_INCLUDED
#define HAL_H_INCLUDED

#include <stdint.h>

void halt();
uint8_t read8(volatile uint8_t* addr);
uint32_t read32(volatile uint32_t* addr);
void write32(volatile uint32_t* addr, uint32_t value);
void write8(volatile uint8_t* addr, uint8_t value);
void temp_halt();

#endif