#include "cmdchecker.h"
#include "../nposkrnl/tools/tools.h"
#include "kterm.h"
#include <stdbool.h>
#include <stdint.h>
#include "../nposkrnl/timer/timer.h"
#include "../nposkrnl/rndnumgen/rndnumgen.h"


char* cmdarray[] = {"echo", "ver", "crash", "wm", "rm", "test1"};




extern uint32_t milliseconds;


void cmd_checker(char* command, char* arguments){
    int cmdsize = sizeof(cmdarray)/sizeof(cmdarray[0]);

    for(int i = 0; i < cmdsize; i++){
        if(str_cmp(command, cmdarray[i]) == true){
            switch(i){
                case 0:
                    term_print(arguments);
                    break;
                case 1:
                    term_print("Nightpane Version Indev");
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
                    int second = a_to_i(secondbuffer);
                    if(first == NULL || second == NULL){
                        term_print("failure");
                        break;
                    }
                    volatile unsigned int *memory_address = (volatile unsigned int*)0x7fffffff; 
                    *memory_address = second;

                    break;
                }
                case 4:
                {
                    int first = a_to_i(arguments);
                    volatile int *memory_address = (int*)first; 
                    char buffer[512];
                    int value = *memory_address;
                    i_to_a(value, buffer);
                    term_print(buffer);
                    break;
                }
                case 5:
                {
                    term_print("------TSC-----");
                    char buffer[512];
                    i_to_a(milliseconds, buffer);
                    term_print(buffer);
                    term_print("------RTC------");
                    RTC rtc;
                    get_rtc_time(&rtc);
                    i_to_a(rtc.seconds, buffer);
                    term_print(buffer);
                }
            }
            return;
        }
    }
}