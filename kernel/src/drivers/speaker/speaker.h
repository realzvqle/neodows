#ifndef SPEAKER_H_INCLUDED
#define SPEAKER_H_INCLUDED








#include "../../HAL/hal.h"
#include "../../nposkrnl/nposkrnl.h"
#include "../../kshell/kshell.h"







void play_sound(uint32_t freq);
NPSTATUS speaker_install();








#endif