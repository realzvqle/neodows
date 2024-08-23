#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED




#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "../../HAL/hal.h"
#include "../../nposkrnl/nposkrnl.h"
#include "../../kshell/kshell.h"



uint8_t read_key_from_port();
char read_key();
void keyboard_install();


















#endif