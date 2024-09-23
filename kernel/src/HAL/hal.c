#include "hal.h"

#include "../nposkrnl/kdraw.h"
#include "../nposkrnl/kfont.h"

#include "../nposkrnl/tools/tools.h"







uint8_t inb(uint16_t port){
    uint8_t result;
    __asm__ __volatile__("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

uint32_t get_cpu_frequency() {
    uint32_t eax, ebx, ecx, edx;
    __asm__ volatile("cpuid"
                     : "=b"(ebx), "=a"(eax), "=c"(ecx), "=d"(edx)
                     : "a"(0x16)); 
    return ebx; 
}



void outb(uint16_t port, uint8_t value){
    __asm__ __volatile__("outb %0, %1" : "=a"(value) : "Nd"(port)); 

    NULL;
}

void cli(){
    __asm__ __volatile__("cli"); 

}

void sti(){
    __asm__ __volatile__("sti"); 

}

uint64_t rdtsc() {
    uint32_t lo, hi;
    asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}


void halt(void) {
    for (;;) {
        asm ("hlt");
    }
}




