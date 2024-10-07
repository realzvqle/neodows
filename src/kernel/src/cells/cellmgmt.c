#include "cellmgmt.h"



char* cells[255];






bool cell_write(uint8_t cellnum, char* content){
    if(cellnum >= 255 || cellnum < 0){
        return false;
    }
    cells[cellnum] = content;
    return true;
}


char* cell_read(uint8_t cellnum){
    if(cellnum >= 255 || cellnum < 0){
        return NULL;
    }
    return cells[cellnum];
}