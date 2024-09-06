#include "kdraw.h"



#include <stdint.h>





extern struct limine_framebuffer *framebuffer;



void kpixel(int x, int y, uint32_t color){
    volatile uint32_t *fb_ptr = framebuffer->address;
    fb_ptr[y * (framebuffer->pitch / 4) + x] = color;
}


void krect(int x, int y, int height, int width, uint32_t color){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            kpixel(x + j, y + i, color);
        }
    }
}




void kbackground(uint32_t color){
    krect(0, 0, framebuffer->height, framebuffer->width, color);
}


