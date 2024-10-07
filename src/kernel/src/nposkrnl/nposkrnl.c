#include "kdraw.h"
#include "kfont.h"
#include "../kshell/kterm.h"
#include "../kshell/kshell.h"
#include "../HAL/hal.h"
#include "../brainfuck/bf.h"
#include "malloc.h"
#include "rndnumgen/rndnumgen.h"
#include "tools/tools.h"
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





NPSTATUS GLOBAL_STATUS = 0xc000000;
int STATE = SINGLE_TASKED;
dev npdev;


static inline void kend_kernel(){
    kputs(620, 10, "nothing to do", 1, 0x8B0101);
    kputs(620, 20, "halting kernel", 1, 0x8B0101);
    kputs(780, 10, "it is safe to turn off your computer", 1, 0x8B0101);

    halt();
}

void flash_bang(){
    while(1){
        kbackground(generate_random_numbers(0x000000, 0xffffff));
    }
}



void rainbow_kernel_suicide(char* error){
    
    kbackground(0x000000);

    while(1){
        kputs(700, 600, ":(", 10, generate_random_numbers(0x000000, 0xffffff));
        kputs(10, 10, "Nightpane has ran into an issue and has been shutdown to prevent damage", 1, generate_random_numbers(0x000000, 0xffffff));
        kputs(10, 20, "please contact zvqle with this error code", 1, generate_random_numbers(0x000000, 0xffffff));
        kputs(10, 60, error, 1, generate_random_numbers(0x000000, 0xffffff));
    }
    cli();
    halt();
}

void kernel_suicide(char* error){
    
    kbackground(0x9905C2);
    kputs(700, 600, ":(", 10, 0xffffff);
    kputs(10, 10, "Nightpane has ran into an issue and has been shutdown to prevent damage", 1, 0xffffff);
    kputs(10, 20, "please contact zvqle with these error code", 1, 0xffffff);
    kputs(10, 60, error, 1, 0xffffff);
    cli();
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
    kheap_init();
    //NPSTATUS status = serial_install();
//     if(!NP_SUCCESS(status)){
//         kernel_suicide("Failed Installing Serial Driver");
//     }
//    // write_serial('a');
    int color = generate_random_numbers(0x111111, 0xffffff);
    kputs(0, 0, os_version(), 1, color);
    kputs(0, 0, "\nCopyright \"zvqle\"", 1, color);
    
    term_print("\n");
    bf_interperter("waaaaaaaaaaaaaaaaaaaah");
    while(1){
        if(!NP_SUCCESS(GLOBAL_STATUS)){
            rainbow_kernel_suicide("GLOBAL STATUS INVALID");
        } 
        GLOBAL_STATUS = shell_start();
        continue;
    }
    
    
    
    
    kend_kernel();
}



