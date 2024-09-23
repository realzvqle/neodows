#ifndef CELLMGMT_H_INCLUDED
#define CELLMGMT_H_INCLUDED







#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>



char* cell_read(uint8_t cellnum);bool cell_write(uint8_t cellnum, char* content);

#endif