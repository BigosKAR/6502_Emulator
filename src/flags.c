#include "instructions.h"
#include "flags.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Flag names

const char flag_names[8][15] = {
    "FLAG_CARRY",
    "FLAG_ZERO",
    "FLAG_INTERRUPT",
    "FLAG_DECIMAL",
    "FLAG_BREAK",
    "UNUSED_FLAG",
    "FLAG_OVERFLOW",
    "FLAG_NEGATIVE"
};

// General flag functions

void display_flags()
{
    for (int i = 7; i >= 0; i--) {
        printf((vm.processor_status & (1 << i)) ? "Flag: %s SET\n" : "Flag: %s UNSET\n", flag_names[i]);
    }
    printf("\n");
}

void reset_flags()
{
    vm.processor_status = 0x20;
}

void set_flag(unsigned char flag)
{
    vm.processor_status |= flag; // Bitwise OR to change only the part of the processor status that is assigned to the flag
}

void clear_flag(unsigned char flag)
{
    vm.processor_status &= ~flag; // Bitwise AND to change only the part of the processor status that is assigned to the flag
}

// Instruction-specific flag functions

void updateNZFlags(unsigned char value)
{
    if(value >= 128)set_flag(FLAG_NEGATIVE);
    else clear_flag(FLAG_NEGATIVE); 
    if(value == 0)set_flag(FLAG_ZERO);
    else clear_flag(FLAG_ZERO);
}

void updateNZC_Flags(unsigned char new_value, unsigned char old_value)
{
    if(old_value >= 128)set_flag(FLAG_CARRY);
    else clear_flag(FLAG_CARRY);
    if(new_value >= 128)set_flag(FLAG_NEGATIVE);
    else clear_flag(FLAG_NEGATIVE);
    if(new_value == 0)set_flag(FLAG_ZERO);
    else clear_flag(FLAG_ZERO);
}

void LSR_update_NZC_Flags(unsigned char new_value, unsigned char old_value)
{
    if(old_value & 1)set_flag(FLAG_CARRY);
    else clear_flag(FLAG_CARRY);
    if(new_value == 0)set_flag(FLAG_ZERO);
    else clear_flag(FLAG_ZERO);
    clear_flag(FLAG_NEGATIVE);
}