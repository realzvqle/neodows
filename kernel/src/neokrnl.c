#include "kfont.h"


__attribute__((used, section(".requests")))
static volatile LIMINE_BASE_REVISION(2);



__attribute__((used, section(".requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};



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


static inline void kend_kernel(struct limine_framebuffer* framebuffer){
    kputs(framebuffer, 30, 30, "nothing to do", 1, 0x8B0101);
    kputs(framebuffer, 30, 31, "halting kernel", 1, 0x8B0101);

    halt();
}

void kbug_check(struct limine_framebuffer* framebuffer){
    kbackground(framebuffer, 0x9905C2);
    kputs(framebuffer, 20, 20, "Zc", 3, 0xffffff);
    kputs(framebuffer, 10, 10, "neokrnl has ran into an issue and has been shutdown to prevent damage", 1, 0xffffff);
    kputs(framebuffer, 10, 11, "please contact zvqle with this error codes", 1, 0xffffff);
    kputs(framebuffer, 10, 14, "insert error codes here", 1, 0xffffff);


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


    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    kbackground(framebuffer, 0x2429A);
    kputs(framebuffer, 0, 0, "neodows build indev", 1, 0xffffff);


    kbug_check(framebuffer);
    
    kend_kernel(framebuffer);
}
