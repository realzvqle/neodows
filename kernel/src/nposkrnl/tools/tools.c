#include "tools.h"



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


int a_to_i(const char* str) {
    int result = 0;        
    int sign = 1;         
    size_t i = 0;          

    while (str[i] == ' ') {
        i++;
    }

    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return sign * result;
}

void slice_string(const char* sourcestring, char delimiter, char* firststring, char* secondstring, size_t firstsize, size_t secondsize) {
    size_t i = 0;

    while (sourcestring[i] != '\0' && sourcestring[i] != delimiter && i < firstsize - 1) {
        firststring[i] = sourcestring[i];
        i++;
    }
    
    firststring[i] = '\0';

    if (sourcestring[i] == delimiter) {
        i++; 
    }

    size_t j = 0;
    while (sourcestring[i] != '\0' && j < secondsize - 1) {
        secondstring[j] = sourcestring[i];
        i++;
        j++;
    }
    
    secondstring[j] = '\0';
}


char* os_version(){
    return "Nightpane version DEBUG (1)";
}
