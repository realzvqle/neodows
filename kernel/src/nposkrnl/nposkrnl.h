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

void kernel_suicide(NPSTATUS error);
void rainbow_kernel_suicide(NPSTATUS error);
bool NP_SUCCESS(NPSTATUS status);



#endif