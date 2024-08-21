#include "kfont.h"
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


static inline void kend_kernel(){
    kputs(30, 30, "nothing to do", 1, 0x8B0101);
    kputs(30, 40, "halting kernel", 1, 0x8B0101);
    kputs(30, 50, "it is safe to turn off your computer", 1, 0x8B0101);

    halt();
}

void kbug_check(char* error){
    kbackground(0x9905C2);
    kputs(700, 600, ":(", 10, 0xffffff);
    kputs(10, 10, "neokrnl has ran into an issue and has been shutdown to prevent damage", 1, 0xffffff);
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

    kbackground(0x2429A);
    kputs(0, 0, "Neodows Build Indev", 1, 0xffffff);
    kputs(10, 10, "Type some stuff!", 1, 0xffffff);
    kbug_check("driver initlization failed");

    int i = 0;
    int j = 1;
    while(1){
        i+=5;
        kchar(0 + (i), 30 * j, 1, read_key(), 0xffffff);
        if(i % (51*3) == 0){
            j++;
        }
    }
    

    
    kend_kernel();
}
