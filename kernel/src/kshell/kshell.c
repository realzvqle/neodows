#include "kshell.h"
#include "../nposkrnl/kfont.h"

extern struct limine_framebuffer *framebuffer;




int i = 3;
int j = 0;


void shell_print(char* status) {
    static bool init = false;
    if(!init){
        krect(0, 40, framebuffer->height - 40, framebuffer->width, 0xffffff);
        init = true;
    }               
    if ((10 + j) >= framebuffer->width) {
        i++;
        j = 0;
    }
    kputs(1 + j, 20 * i, status, 1, 0x000000);
    j += 5;
    i++;
    j = 0;
    if ((20 * i) >= framebuffer->height) {
        krect(0, 40, framebuffer->height - 40, framebuffer->width, 0xffffff);
        i = 3;
    } 
}
