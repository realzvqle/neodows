#ifndef BF_H_INCLUDED
#define BF_H_INCLUDED





#include "../kshell/kterm.h"
#include "../nposkrnl/malloc.h"



typedef struct _block_data
{
    uint16_t current_block;
    size_t block_size;
    size_t blocks_allocated;
    size_t block_array_cap;
    unsigned char* blocks;
} block_data;


void bf_interperter(char* string);


#endif