#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED




#include <stdint.h>
#include <stdbool.h>


void sleep(uint32_t seconds);
uint32_t get_timer_value();
#endif