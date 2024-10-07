#include "kshell.h"
#include "kterm.h"
#include "../nposkrnl/tools/tools.h"


#include <stddef.h>

#include <stddef.h>






NPSTATUS shell_start(){
    char* string = term_get(1024);
    char first[512];
    char second[512];
    slice_string(string, ' ', first, second, 512, 512);;
    cmd_checker(first, second);
    kfree(string);  

    return 0xc000000;
}