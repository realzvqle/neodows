#include "speaker.h"
#include <stdint.h>
#include "../drivers.h"




extern dev npdev;


NPSTATUS speaker_install(){
    NPSTATUS status = add_device("Speaker");
    return status;
}

static inline void disable_speaker(){
    uint8_t tmp = inb(0x61) & 0xFC;

    outb(0x61, tmp);
}


void play_sound(uint32_t freq){
    uint32_t div;
    uint8_t tmp;

    div = 1193180 / freq; 
    outb(0x43, 0xb6);
    outb(0x42, (uint8_t)(div));
    outb(0x42, (uint8_t)(div >> 8));

    tmp = inb(0x61);
    if(tmp != (tmp | 3)){
        outb(0x61, tmp | 3);
    }
}



void beep(){
    play_sound(440);
    // wait
    disable_speaker();
}