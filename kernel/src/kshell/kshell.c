#include "kshell.h"
#include "../drivers/keyboard/keyboard.h"
#include "../nposkrnl/kfont.h"
#include "../nposkrnl/kmem.h"

extern struct limine_framebuffer *framebuffer;




int i = 0;

// void kshell_add_to_buffer(char* buffer, size_t size, char key) {
//     
// }

void init_shell() {

    krect(0, 40, framebuffer->height - 40, framebuffer->width, 0xffffff);

    int i = 1;
    int j = 0;
    char buffer[512] = { 0 };
    bool shoulddrawcursor = true;
    while (1) {
        if (shoulddrawcursor) {
            kputs(0, 60 * i, "> ", 1, 0x000000);
        }

        char key = read_key();
        if (key != '\n') {
            if (key == '\b') {
                // idk what to do here lol
            }
            if ((10 + j) >= framebuffer->width) {
                shoulddrawcursor = false;
                i++;
                j = 0;
            }
            char temp[2] = { key, '\0'};
            kputs(10 + j, 60 * i, temp, 1, 0x000000);
            j += 5;
        } else {
            shoulddrawcursor = true;
            i++;
            j = 0;
            kputs(10 + j, 60 * i, buffer, 1, 0x000000);
            memset(buffer, 0, sizeof(buffer));
        }

        if ((60 * i) >= framebuffer->height) {
            krect(0, 40, framebuffer->height - 40, framebuffer->width, 0xffffff);
            i = 1;
        }
    }
}
