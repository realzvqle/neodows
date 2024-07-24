#include "draw.h"



#include <stdint.h>



void place_pixel(struct limine_framebuffer *framebuffer, int x, int y, uint32_t color){
    volatile uint32_t *fb_ptr = framebuffer->address;
    fb_ptr[y * (framebuffer->pitch / 4) + x] = color;
}


void place_rect(struct limine_framebuffer *framebuffer, int x, int y, int height, int width, uint32_t color){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            place_pixel(framebuffer, x + j, y + i, color);
        }
    }
}

void set_background(struct limine_framebuffer *framebuffer, uint32_t color){
    place_rect(framebuffer, 0, 0, framebuffer->height, framebuffer->width, color);
}


