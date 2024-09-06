#include "kdraw.h"
#include "kfont.h"
#include "../kshell/kshell.h"
#include "../drivers/keyboard/keyboard.h"
#include "../drivers/speaker/speaker.h"

#include "rndnumgen/rndnumgen.h"

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

void rainbow_kernel_suicide(char* error){
    kbackground(0x000000);
    while(1){
        kputs(700, 600, ":(", 10, generate_random_numbers(0x000000, 0xffffff));
        kputs(10, 10, "Nightpane has ran into an issue and has been shutdown to prevent damage", 1, generate_random_numbers(0x000000, 0xffffff));
        kputs(10, 20, "please contact zvqle with this error code", 1, generate_random_numbers(0x000000, 0xffffff));
        kputs(10, 60, error, 1, generate_random_numbers(0x000000, 0xffffff));
    }
    halt();
}


bool NP_SUCCESS(NPSTATUS status){
    if(status == 0xc000000) return true;
    else return false;
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

    kputs(0, 0, "Nightpane Build Indev\nCopyright \"zvqle\"", 1, generate_random_numbers(0x111111, 0xffffff));
    
    NPSTATUS status = keyboard_install();
    if(NP_SUCCESS(status)) shell_print("pass");
    else shell_print("fail");
    shell_print("\n\n\n");

    NPSTATUS statu = speaker_install();
    if(NP_SUCCESS(statu)) shell_print("pass");
    else shell_print("fail");

    shell_print("\n\n\n");
    shell_print("Devices_______________________");
    for(int i = 0; i < npdev.index; i++){
        shell_print(npdev.dev[i]);
    }
    
    
    
    
    kend_kernel();
}
