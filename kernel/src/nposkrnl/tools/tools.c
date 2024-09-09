#include "tools.h"
#include "../kmem.h"



char* str_cat(char* destination, const char* source) {
    char* dest = destination;

    while (*dest != '\0') {
        dest++;
    }
    while (*source != '\0') {
        *dest = *source;
        dest++;
        source++;
    }
    *dest = '\0';
    return destination;
}

char* i_to_a(int num, char* str) {
    int i = 0;
    int isNegative = 0;
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }
    do {
        str[i++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);
    if (isNegative) {
        //str[i++] = '-';
    }

    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    str[i] = '\0';

    return str;
}

char* i_to_hex(int num, char* str) {
    int i = 0;
    int isNegative = 0;

    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    do {
        int digit = num % 16;
        str[i++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
        num /= 16;
    } while (num > 0);

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

    return str;
}


bool str_cmp(char* first_string, char* second_string) {
    int index = 0;
    
    while (true) {
        if (first_string[index] != second_string[index]) {
            return false;
        }

        if (first_string[index] == '\0' && second_string[index] == '\0') {
            return true;
        }

        index++;
    }
}



