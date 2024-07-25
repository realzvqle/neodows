#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED






#include "neokrnl.h"



void kpixel(struct limine_framebuffer *framebuffer, int x, int y, uint32_t color);
void krect(struct limine_framebuffer *framebuffer, int x, int y, int height, int width, uint32_t color);
void kbackground(struct limine_framebuffer *framebuffer, uint32_t color);









#endif