#include "serial.h"


#define PORT 0x3f8 



extern dev npdev;

// doesn't work (yet) =(
NPSTATUS serial_install(){
    NPSTATUS status = add_device("Serial");
    if(!status){
        return 0xc000008;

    }
    outb(PORT + 1, 0x00);   
    outb(PORT + 3, 0x80);    
    outb(PORT + 0, 0x03);    
    outb(PORT + 1, 0x00);    
    outb(PORT + 3, 0x03);    
    outb(PORT + 2, 0xC7);    
    outb(PORT + 4, 0x0B);    
    outb(PORT + 4, 0x1E);    
    outb(PORT + 0, 0xAE);   

    if(inb(PORT + 0) != 0xAE) {
        return 0xc000009;
    }

   
    outb(PORT + 4, 0x0F);
    return 0xc000000;
}

static inline int receive(){
    return inb(PORT + 5) & 1;
}


static inline int is_transmit_empty() {
   return inb(PORT + 5) & 0x20;
}



char serial_getchar() {
   while (receive() == 0);

   return inb(PORT);
}

void write_serial(char a) {
   while (is_transmit_empty() == 0);

   outb(PORT,a);
}