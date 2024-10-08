#include "bf.h"
#include "../nposkrnl/kmem.h"




// credit to https://jpeoples.github.io/blog/2017/11/brainfuck/#the-interpreter-loop

static block_data b;

static inline void create_block_data(block_data* b, size_t b_size){
    b->blocks = kmalloc(b_size);
    b->block_size = b_size;
    b->block_array_cap = b_size;
    b->current_block = 0;
}

static inline void destroy_block_data(block_data* b){
    kfree(b->blocks); 
}

static inline void increment_block(block_data* b){
    b->current_block++;
}

static inline void decrement_block(block_data* b){
    b->current_block--;
}


static inline void increment_block_data(block_data* b){
    b->blocks[b->current_block]++;
}

static inline void decrement_block_data(block_data* b){
    b->blocks[b->current_block]--;
}

void bf_interperter(char* string){

    create_block_data(&b, 1024);
    memset(b.blocks, 0, b.block_size);
    char c;
    while ((c = *string++)) { 
        switch(c){
            case 'w':
                //term_print("Incrementing..");
                increment_block(&b);
                break;
            case 'l':
                //term_print("Decrementing..");
                decrement_block(&b);
                break;
            case 'a':
                //term_print("Incrementing a Block data");

                increment_block_data(&b);
                break;
            case 'f':
                //term_print("Incrementing a Block");
                decrement_block_data(&b);
                break;
            case 'h':
            {
                char temp[2];
                temp[0] = b.blocks[b.current_block];
                temp[1] = '\0';
                term_puts(temp);
                break;
            }
            case 'o':
            {
                char* idk = term_get(2);
                unsigned char temp[2];
                temp[0] = idk[0];
                temp[1] = '\0';
                b.blocks[b.current_block] = temp[0];
                kfree(idk);
            }
        }
    }

    term_print("");
    kfree(b.blocks);
}
