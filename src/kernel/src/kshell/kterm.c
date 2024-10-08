#include "kterm.h"
#include "../nposkrnl/kfont.h"
#include "../nposkrnl/malloc.h"
#include "../drivers/keyboard/keyboard.h"
extern struct limine_framebuffer *framebuffer;




int i = 15;
int j = 0;


void term_print(char* status) {
    static bool init = false;
    if(!init){
        krect(0, 100, framebuffer->height - 100, framebuffer->width, 0x1e1e2e);
        init = true;
    }               
    
    kputs(1 + j, 12 * i, status, 1, 0xcdd6f4);
    j += 5;
    i++;
    j = 0;
   
    if ((12 * i) >= framebuffer->height) {
        krect(0, 100, framebuffer->height - 100, framebuffer->width, 0x1e1e2e);
        i = 15;
    } 
}

void term_puts(char* status) {
    static bool init = false;
    if(!init){
        krect(0, 100, framebuffer->height - 100, framebuffer->width, 0x1e1e2e);
        init = true;
    }               
    
    kputs(1 + j, 12 * i, status, 1, 0xcdd6f4);
    j += 10;
    
   
    if ((12 * i) >= framebuffer->height) {
        krect(0, 100, framebuffer->height - 100, framebuffer->width, 0x1e1e2e);
        i = 15;
    } 
}

void term_clear(){
    krect(0, 100, framebuffer->height - 100, framebuffer->width, 0x1e1e2e);
    i = 15;
}



static inline char* array_adder(size_t size) {
    char* array = kmalloc(size);
    // if (!array) {
    //     return NULL;  
    // }

    for (int jj = 0; jj < size - 1; jj++) {
        array[jj] = '\0';  
    }
    static char former_char;
    char character;
    int index = 0;
    while (index < (size - 1)) { 

        uint8_t scan_code = read_ps2_key_from_port();
        if(scan_code == 14){
            if(index == 0) continue;
            array[index] = '\0';
            index--;
            if(j > 0) j-=10;
            krect(1 + j, 12 * i, 10, 10, 0x1e1e2e);
            continue;
        }
        
        else character = code_to_char(scan_code);
        
        // if(character == former_char){
        //     continue;
        // }
        if(character == NULL){
            continue;
        }
        if (character == '\n') {
            array[index] = '\0';  
            break;
        }
        array[index] = character; 
        char temp[2];
        temp[0] = character;
        temp[1] = '\0';  
        index++;
        kputs(1 + j, 12 * i, temp, 1, 0xcdd6f4);
        if (j >= framebuffer->width) {
            
            i++;
            j = 0;
        }
        j += 10;
        former_char = character;
        
    }

    if (index == (size - 1)) {
        array[size - 1] = '\0';  
    }

    return array;
}


char* term_get(size_t size) {
    static bool init = false;
    if(!init){
        krect(0, 100, framebuffer->height - 100, framebuffer->width, 0x1e1e2e);
        init = true;
    }               
    if ((10 + j) >= framebuffer->width) {
        i++;
        j = 0;
    }
    kputs(1 + j, 12 * i, ">   ", 1, 0xcdd6f4);
    j += 10;
    
    //j += 5;
    //i++;
    char* result = array_adder(size);
    // for(int i = 0; i < size; i++){
    //     term_print("ARRAY");
    //     term_print(&result[i]);
    // }
    //kputs(90, 10, result, 2, 0x9905C2);
    
    //j = 0;
    i++;
    if ((12 * i) >= framebuffer->height) {
        krect(0, 100, framebuffer->height - 100, framebuffer->width, 0x1e1e2e);
        i = 15;
    } 
    term_print("");
    return result;
}
