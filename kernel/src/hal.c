#include "hal.h"




void halt(){
    for(;;){
        asm ("wfi");
    }
}