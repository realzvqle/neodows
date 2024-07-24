#include "draw.h"



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


void _entry(void) {

    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        halt();
    }

    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        halt();
    }


    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
    set_background(framebuffer, 0x2429A);
    place_rect(framebuffer, 120, 140, 20, 20, 0xFF0000);
    place_rect(framebuffer, 284, 387, 20, 20, 0x3cdfff);
    place_rect(framebuffer, 254, 587, 20, 20, 0x00FF00);
    place_rect(framebuffer, 300, 300, 20, 20, 0xFFFF00);

    place_rect(framebuffer, 400, 400, 20, 20, 0xFFFF00);
    

    
    halt();
}
