#include "serial.h"
#include "hal.h"




void kmain(void) {
    serial_print("Nightpane Kernel\n");
    halt();
}