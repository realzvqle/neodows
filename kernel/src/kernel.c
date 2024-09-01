#include "npstdlib.h"
#include "rndnum.h"
#include "serial.h"
#include "hal.h"
#include "timer.h"


void kmain(void) {
    serial_print("\n\nNightpane Kernel\n\n");
    
    while(1){
        uint8_t idk = generate_random_numbers(get_timer_value());
        char buffer[612];
        i_to_a(idk, buffer);
        serial_print(buffer);
        serial_print("\n");
        sleep(1);
    }
    
    halt();
}
