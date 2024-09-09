#include "process.h"
#include "../kshell/kshell.h"


PROCESS_TABLE process_table = { .count = 0 };

extern NPSTATUS GLOBAL_STATUS;
extern int STATE;



NPSTATUS create_process(TENTRY entry_point, int vm_size, char* arguments){
    if(STATE == SINGLE_TASKED) return create_single_threaded_process(entry_point, vm_size, arguments);
    else if(STATE == MULTI_TASKED) shell_print("No Multitasking Code Found");
    else return 0xc000111;
    return 0xc000000;
}


NPSTATUS create_single_threaded_process(TENTRY entry_point, int vm_size, char* arguments){
    if(process_table.count >= MAX_PROCESSES){
        GLOBAL_STATUS = 0xc000100;
        return 0xc000100;
    }
    if(STATE == MULTI_TASKED) return 0xc000130;
    SINGLE_TASKED_PROCESS* process = kmalloc(sizeof(SINGLE_TASKED_PROCESS)); 
    if (!process) {
        GLOBAL_STATUS = 0xc000110;
        return 0xc000110;
    }

    process->pid = process_table.count; 
    process->vm_size = vm_size;
    process->status = 0;
    process->context = kmalloc(vm_size);
    if (!process->context) {
        kfree(process);
        GLOBAL_STATUS = 0xc000120;
        return 0xc000120; 
    }

    process_table.count++;
    process_table.processes[process_table.count] = process;
    int status = entry_point(arguments);
    
    kfree(process->context);
    kfree(process);

    process_table.count--;
    return 0xc000000;
}


