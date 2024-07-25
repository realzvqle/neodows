#ifndef KFONT_H_INCLUDED
#define KFONT_H_INCLUDED






#include "kdraw.h"



void kchar(struct limine_framebuffer *framebuffer, int x, int y, int size, char c, uint32_t color);
void kputs(struct limine_framebuffer* framebuffer, int x, int y, char* s, int size, uint32_t color);

#endif