#include "cmdchecker.h"
#include "../nposkrnl/tools/tools.h"
#include "kterm.h"
#include <stdbool.h>
#include <stdint.h>
#include "../nposkrnl/timer/timer.h"
#include "../drivers/keyboard/keyboard.h"
#include "../cells/cellmgmt.h"
#include "../brainfuck/bf.h"
char* cmdarray[] = {"echo", "ver", "crash", "wcell", "rcell", "secondstest", "help", "keyboardtest", "clear",
                    "trippy", "bf", "neovim"};






void cmd_checker(char* command, char* arguments){
    int cmdsize = sizeof(cmdarray)/sizeof(cmdarray[0]);

    for(int i = 0; i < cmdsize; i++){
        if(str_cmp(command, cmdarray[i]) == true){
            switch(i){
                case 0:
                    term_print(arguments);
                    break;
                case 1:
                    term_print(os_version());
                    break;
                case 2:
                    kernel_suicide(arguments);
                    break;
                case 3:
                {
                    char buffer[256];
                    char secondbuffer[255];
                    slice_string(arguments, ' ', buffer, secondbuffer, 256, 255);
                    int first = a_to_i(buffer);
                    if(first == NULL){
                        term_print("Incorrect Cell");
                        break;
                    }
                    
                    bool result = cell_write(first, secondbuffer);
                    if(!result || first >= 255){
                        term_print("cell overflow");
                        break;
                    }

                    break;
                }
                case 4:
                {
                    int first = a_to_i(arguments);
                    char* result = cell_read(first);
                    if(!result || first >= 255){
                        term_print("cell overflow");
                        break;
                    }
                    term_print(result);
                    break;
                }
                case 5:
                {
                    char buffer[512]; 
                    term_print("------RTC------");
                    RTC rtc;
                    get_rtc_time(&rtc);
                    i_to_a(rtc.seconds, buffer);
                    term_print(buffer);
                    break;
                }
                case 6:
                {
                    term_print("COMMANDS:\necho [arg], prints arg\n");
                    term_print("crash [arg], crashes the OS with arg error\n");
                    term_print("wcell [cellnum] [content], writes to specific cell (between 1 and 254) with content\nrcell [cellnum], reads the content of a cell");
                    break;
                }
                case 7:
                {

                    term_print("NIGHTPANE PS/2 KEYBOARD DRIVER TEST\nTo exit press the windows key");
                    while(1){
                        
                        char buffer[512];
                        i_to_a(read_ps2_key_from_port(), buffer);
                        if(str_cmp(buffer, "91") == true){
                            return;
                        }
                        term_print(buffer);
                        
                    }
                    break;
                }
                case 8:
                    term_clear();
                    break;
                case 9:
                    rainbow_kernel_suicide("trippy =3");
                    break;
                case 10:
                    bf_interperter(arguments);
                    break;
                case 11:
                
                    term_print(" %%%%%%%%%%%%%%%                                                                                     ");
                    term_print("%%%=== %%     %%%   ====  ==    ===            ===        ===                                        ");
                    term_print("%% === %%@    @%%   ===== ==  ====+     === == ======   =======   = ===     ===    == ===     ===   ");
                    term_print("%%%%%%%%%%%%%%%%%   ========  =====   ======== ======== ======== ======== ======== ======== ======= ");
                    term_print("%%%%%%%%%%%%%%%%%   ========    ===   ===  === ===  ===   ===    ===  === ======== === ==== ======== ");
                    term_print("%%     %%@    @%%   === ====    ===   ======== ===  ===   ===    ===  === === ==== === ==== ==   == ");
                    term_print("%%     %%     @%%   ===  === =========  ====== ===  ===   +===== =======  ======== ===  ===  ====== ");
                    term_print("%%%%%%%%%%%%%%%%%                       ======                   ===                                 ");

                    //term_print("Neovim!");
                    break;
                
            }
            
            return;
        }
    }
    term_print("Command not found, type \"help\" to see avaliable commands");
    return;
}
