#include "kfont.h"
#include "../kshell/kshell.h"
#include "../drivers/keyboard/keyboard.h"
__attribute__((used, section(".requests")))
static volatile LIMINE_BASE_REVISION(2);



__attribute__((used, section(".requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

struct limine_framebuffer *framebuffer;


__attribute__((used, section(".requests_start_marker")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".requests_end_marker")))
static volatile LIMINE_REQUESTS_END_MARKER;


static void halt(void) {
    for (;;) {
#if defined (__x86_64__)
        asm ("hlt");
#elif defined (__aarch64__) || defined (__riscv)
        asm ("wfi");
#endif
    }
}


dev npdev;


static inline void kend_kernel(){
    kputs(620, 10, "nothing to do", 1, 0x8B0101);
    kputs(620, 20, "halting kernel", 1, 0x8B0101);
    //kputs(30, 10, "it is safe to turn off your computer", 1, 0x8B0101);

    halt();
}

void kernel_suicide(char* error){
    kbackground(0x9905C2);
    kputs(700, 600, ":(", 10, 0xffffff);
    kputs(10, 10, "Nightpane has ran into an issue and has been shutdown to prevent damage", 1, 0xffffff);
    kputs(10, 20, "please contact zvqle with this error code", 1, 0xffffff);
    kputs(10, 60, error, 1, 0xffffff);


    halt();
}

void _entry(void) {

    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        halt();
    }

    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        halt();
    }


    framebuffer = framebuffer_request.response->framebuffers[0];

    kbackground(0x000000);
    kputs(0, 0, "Nightpane Build Indev\nCopyright \"zvqle\"", 1, 0x33FFBD);

    while(1){
        shell_print("Press 1 for Fun, Press 2 for Bad");
        char key = read_key();
        if(key == '2') kernel_suicide("Fuck yoy");
        else continue;

    }
    
    kend_kernel();
}
