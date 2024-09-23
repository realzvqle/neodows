#ifndef NPOSKRNL_H_INCLUDED
#define NPOSKRNL_H_INCLUDED




#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "../limine.h"


#define NPSTATUS uint64_t
#define SINGLE_TASKED 0
#define MULTI_TASKED 1

typedef struct {
    int index;
    char* dev[512]; 
} dev;

void rainbow_kernel_suicide(char* error);
bool NP_SUCCESS(NPSTATUS status);
void flash_bang();
void kernel_suicide(char* error);

#endif