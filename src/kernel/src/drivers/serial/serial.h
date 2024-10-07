#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED






#include "../drivers.h"





char serial_getchar();
void write_serial(char a);
NPSTATUS serial_install();

#endif