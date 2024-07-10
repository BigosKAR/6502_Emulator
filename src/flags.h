#ifndef FLAGS_H

#define FLAGS_H

#include <stdio.h>
#include "instructions.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// FLAGS

#define FLAG_CARRY 0x01
#define FLAG_ZERO 0x02
#define FLAG_INTERRUPT 0x04
#define FLAG_DECIMAL 0X08
#define FLAG_BREAK 0x10
#define UNUSED_FLAG 0x20
#define FLAG_OVERFLOW 0x40
#define FLAG_NEGATIVE 0x80

extern const char flag_names[8][15];;

// General flag functions

void reset_flags();
void set_flag(unsigned char flag);
void clear_flag(unsigned char flag);

void display_flags();

// Instruction-specific flag functions

void updateNZFlags(unsigned char value);


#endif