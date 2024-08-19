#ifndef ADDRESSING_MODES_H
#define ADDRESSING_MODES_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "flags.h"
#include "instructions.h"

typedef enum{
    IMMEDIATE,
    IMPLIED,
    ACCUMULATOR,
    RELATIVE,
    ABSOLUTE,
    ABSOLUTE_INDEXED,
    ABSOLUTE_INDEXED_PC,
    ABSOLUTE_INDIRECT,
    ZERO_PAGE,
    ZERO_PAGE_INDEXED,
    ZERO_PAGE_X_INDIRECT,
    ZERO_PAGE_Y_INDIRECT,
    ZERO_PAGE_Y_INDIRECT_PC
}AddressingModes;

typedef struct InstructionParams{
    unsigned int required_cycles;
    unsigned char instruction;
    AddressingModes addressing_mode;
}InstructionParams;

unsigned short get_relative_address(); // -1 Cycle (additional -1 if page crossed)
unsigned short get_abs_address(); // -2 Cycle
unsigned short get_abs_indexed_address_pc(unsigned char vm_register); // -2 Cycle (additional -1 if page crossed)
unsigned short get_abs_indexed_address(unsigned char vm_register); // -2 Cycle
unsigned short get_abs_ind_address(); // -4 Cycles
unsigned short get_zp_address(); // -1 Cycle
unsigned short get_zp_indexed_address(unsigned char vm_register); // -2 Cycle
unsigned short get_zp_x_ind_address(); // -4 Cycles
unsigned short get_zp_y_ind_address_pc(); // -3 Cycles (additional -1 if page crossed)
unsigned short get_zp_y_ind_address(); // -3 Cycles
unsigned short fetch_address(InstructionParams params, unsigned char* vm_register);

#endif