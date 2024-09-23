#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED







#include <stdint.h>
#include <stdbool.h>
#include "../malloc.h"






char* str_cat(char* destination, const char* source);

char* i_to_a(int num, char* str);
char* i_to_hex(int num, char* str);
bool str_cmp(char* first_string, char* second_string);

void str_tok(char** firststring, size_t firststringsize, char** secondstring, size_t secondstringsize, char delimiter, char* sourcestring);
char* os_version();
int a_to_i(const char* str);
void slice_string(const char* sourcestring, char delimiter, char* firststring, char* secondstring, size_t firstsize, size_t secondsize);
#endif