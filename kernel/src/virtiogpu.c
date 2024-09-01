#include "virtiogpu.h"
#include "hal.h"
#include "serial.h"



static volatile uint32_t *framebuffermem = (uint32_t *) 0x40000000; 



uint32_t get_framebuffer_info() {
    return read32(framebuffermem);  
}

void set_pixel(int x, int y, uint32_t color, int screen_width) {

}


void clear_screen(uint32_t color, int screen_width, int screen_height) {
    for (int y = 0; y < screen_height; y++) {
        for (int x = 0; x < screen_width; x++) {
            set_pixel(x, y, color, screen_width);
        }
    }
}