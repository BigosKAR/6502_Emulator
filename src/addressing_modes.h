#ifndef ADDRESSING_MODES_H
#define ADDRESSING_MODES_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "flags.h"
#include "instructions.h"

unsigned short get_abs_address(); // -1 Cycle
unsigned short get_abs_indexed_address_pc(unsigned char vm_register); // -1 Cycle (additional -1 if page crossed)
unsigned short get_abs_indexed_address(unsigned char vm_register); // -1 Cycle
unsigned short get_zp_address(); 
unsigned short get_zp_indexed_address(unsigned char vm_register); // -1 Cycle
unsigned short get_zp_x_ind_address(); // -3 Cycles
unsigned short get_zp_y_ind_address_pc(); // -2 Cycles (additional -1 if page crossed)
unsigned short get_zp_y_ind_address(); // -2 Cycles
unsigned short fetch_address(InstructionParams params, unsigned char* vm_register);

#endif