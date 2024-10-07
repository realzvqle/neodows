#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED




#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "../../HAL/hal.h"
#include "../../nposkrnl/nposkrnl.h"



uint8_t read_ps2_key_from_port();
char read_key();
NPSTATUS keyboard_install();
char code_to_char(uint8_t makeCode);















#endif