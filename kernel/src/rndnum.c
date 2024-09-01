#include "rndnum.h"
#include <stdint.h>



uint32_t xorshift32(uint32_t state[static 1])
{
    uint32_t x = state[0];
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state[0] = x;
    return x;
}

uint32_t generate_random_numbers(uint32_t seed) {
    uint32_t state[1];
    state[0] = seed; 
    uint32_t random_number = xorshift32(state);

    return random_number;
}