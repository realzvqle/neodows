#ifndef KDRAW_H_INCLUDED
#define KDRAW_H_INCLUDED






#include "nposkrnl.h"



void kpixel(int x, int y, uint32_t color);
void krect(int x, int y, int height, int width, uint32_t color);
void kbackground(uint32_t color);









#endif