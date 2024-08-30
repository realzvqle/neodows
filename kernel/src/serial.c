#include "serial.h"



volatile uint8_t *uart = (uint8_t *) 0x09000000;

void serial_putchar(char c) {
    *uart = c;
}

void serial_print(const char *s) {
    while(*s != '\0') {
        serial_putchar(*s);
        s++;
    }
}