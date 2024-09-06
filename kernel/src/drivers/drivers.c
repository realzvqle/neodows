#include "drivers.h"
#include "../nposkrnl/tools/tools.h"






bool init = false;

extern dev npdev;



NPSTATUS add_device(char* device_name){
    if(init == false){
        npdev.index = 0;
        init = true;
    }
    if(npdev.index >= 512){
        return 0xc000001;
    }
    npdev.dev[npdev.index] = device_name;
    
    char buffer[255];
    str_cat(buffer, "Installed ");
    str_cat(buffer, device_name);
    shell_print(buffer);
    
    npdev.index++;

    for(int i = 0; i < 255; i++){
        buffer[i] = '\0';
    }
    return 0xc000000;

}