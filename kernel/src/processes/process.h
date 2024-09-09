#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED





#include "../nposkrnl/nposkrnl.h"
#include "../nposkrnl/malloc.h"



typedef int (*TENTRY)(char*);


#define MAX_PROCESSES 1024



// for multithreading
typedef struct _TTABLE{
    TENTRY entry;
    int vm_size;
    int status;
    int priority;
    int PID;
    void *context;
} TTABLE;

typedef struct _PTABLE{
    TTABLE *threads;  
    int num_threads;
} PTABLE;

// for single tasked mode
typedef struct _SINGLE_TASKED_PROCESS {
    int pid;               
    void *context;         
    int vm_size;           
    int status;            
} SINGLE_TASKED_PROCESS;

typedef struct _PROCESS_TABLE {
    SINGLE_TASKED_PROCESS *processes[MAX_PROCESSES];
    int count;
} PROCESS_TABLE;


NPSTATUS create_single_threaded_process(TENTRY entry_point, int vm_size, char* arguments);
NPSTATUS create_process(TENTRY entry_point, int vm_size, char* arguments);






#endif