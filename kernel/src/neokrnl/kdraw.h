#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED






#include "neokrnl.h"



void kpixel(int x, int y, uint32_t color);
void krect(int x, int y, int height, int width, uint32_t color);
void kbackground(uint32_t color);









#endif