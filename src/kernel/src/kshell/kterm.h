#ifndef KTERM_H_INCLUDED
#define KTERM_H_INCLUDED







#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>





void term_print(char* status);
char* term_get(size_t size);
void term_clear();
void term_puts(char* status);















#endif