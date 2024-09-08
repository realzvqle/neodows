#include "process.h"



PROCESS_TABLE process_table = { .count = 0 };

extern NPSTATUS GLOBAL_STATUS;
extern void call_death(void);
int create_single_threaded_process(TENTRY entry_point, int vm_size, char* arguments){
    if(process_table.count >= MAX_PROCESSES){
        GLOBAL_STATUS = 0xc000100;
        return -1;
    }
    PROCESS* process = kmalloc(sizeof(PROCESS)); 
    if (!process) {
        GLOBAL_STATUS = 0xc000110;
        return -1;
    }

    process->pid = process_table.count; 
    process->vm_size = vm_size;
    process->status = 0;
    process->context = kmalloc(vm_size);
    if (!process->context) {
        kfree(process);
        GLOBAL_STATUS = 0xc000120;
        return -1; 
    }
    call_death();

    process_table.count++;
    process_table.processes[process_table.count] = process;
    int status = entry_point(arguments);
    
    kfree(process->context);
    kfree(process);

    return 0;
}