#include "npstdlib.h"
#include "serial.h"
#include "hal.h"
#include "malloc.h"
#include <stdint.h>

volatile uint8_t *uaurt = (uint8_t *) 0x09000000;

void kmain(void) {
    serial_print("\n\nNightpane Kernel\n\n");
    
    uint8_t idk = read32(uaurt);
    char buffer[612];
    i_to_a(idk, buffer);
    serial_print(buffer);
    halt();
}