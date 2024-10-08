#ifndef HAL_H_INCLUDED
#define HAL_H_INCLUDED





#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>



uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t value);
uint64_t rdtsc();
void cli();
void sti();
uint32_t get_cpu_frequency();
void halt(void);

#endif