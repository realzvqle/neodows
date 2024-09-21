#include "cmdchecker.h"
#include "../nposkrnl/tools/tools.h"
#include "kshell.h"
#include <stdbool.h>


char* cmdarray[] = {"hi", "ver", "crash", "trippy", "lcd"};







void cmd_checker(char* command){
    int cmdsize = sizeof(cmdarray)/sizeof(cmdarray[0]);

    for(int i = 0; i < cmdsize; i++){
        if(str_cmp(command, cmdarray[i]) == true){
            switch(i){
                case 0:
                    shell_print("Hello!");
                    break;
                case 1:
                    shell_print("Nightpane Version Indev");
                    break;
                case 2:
                    kernel_suicide(0xc000000);
                    break;
                case 3:
                    rainbow_kernel_suicide(0xc000000);
                    break;
                case 4:
                    flash_bang();
                    break;
            }
            return;
        }
    }
}