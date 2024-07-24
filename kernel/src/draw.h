#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED






#include "neokrnl.h"



void place_pixel(struct limine_framebuffer *framebuffer, int x, int y, uint32_t color);
void place_rect(struct limine_framebuffer *framebuffer, int x, int y, int height, int width, uint32_t color);
void place_char(struct limine_framebuffer *framebuffer, int x, int y, char c, uint32_t color);













#endif