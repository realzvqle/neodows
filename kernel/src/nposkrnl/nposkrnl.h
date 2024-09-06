#ifndef NPOSKRNL_H_INCLUDED
#define NPOSKRNL_H_INCLUDED




#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "../limine.h"





typedef struct {
    int index;;
    char* dev[512];
    
} dev;

void kernel_suicide(char* error);





#endif