#ifndef MALLOC_H_INCLUDED
#define MALLOC_H_INCLUDED



#include <stdint.h>
#include <stddef.h>

#define MEMORY_SIZE 10960  


typedef struct Block {
    size_t size;       
    struct Block* next; 
} Block;

void kheap_init(void);
void* kmalloc(size_t size);
void kfree(void* ptr);

#endif