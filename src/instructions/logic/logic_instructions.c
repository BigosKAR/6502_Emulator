#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"
#include "logic_instructions.h"
#include "../../addressing_modes.h"

// Main logic functions

// Functions for AND, EOR, and OR (logical)
void logical_imm(unsigned char low_byte, unsigned char instruction)
{
    cycle_check(2-2);
    if(instruction == AND_IMM)and_bitwise_logic(low_byte);
    else if(instruction == EOR_IMM)eor_bitwise_logic(low_byte);
    else ora_bitwise_logic(low_byte); // OR is the remaining case
    debug(instruction, vm.accumulator);
}
void logical_abs(unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(4-2);
    unsigned short address = get_abs_address(low_order_address);
    if(instruction == AND_ABS)and_bitwise_logic(memory.data[address]);
    else if(instruction == EOR_ABS)eor_bitwise_logic(memory.data[address]);
    else ora_bitwise_logic(memory.data[address]); // OR is the remaining case
    vm.cycles -= 1;
    debug(instruction, vm.accumulator);
}
void logical_abs_reg_logic(unsigned low_order_address, unsigned char vm_register, unsigned char instruction)
{
    cycle_check(4-2);
    unsigned short address = get_abs_indexed_address_pc(low_order_address, vm_register);
    if(instruction == AND_ABS_X || instruction == AND_ABS_Y)and_bitwise_logic(memory.data[address]);
    else if(instruction == EOR_ABS_X || instruction == EOR_ABS_Y)eor_bitwise_logic(memory.data[address]);
    else ora_bitwise_logic(memory.data[address]);
    vm.cycles -= 1;
    debug(instruction, vm.accumulator);
}
void logical_zp(unsigned char low_byte, unsigned char instruction)
{
    cycle_check(3-2);
    unsigned short address = get_zp_address(low_byte);
    if(instruction == AND_ZP)and_bitwise_logic(memory.data[address]);
    else if(instruction == EOR_ZP)eor_bitwise_logic(memory.data[address]);
    else ora_bitwise_logic(memory.data[address]);
    vm.cycles -= 1;
    debug(instruction, vm.accumulator);
}
void logical_zp_x(unsigned char low_byte, unsigned char instruction)
{
    cycle_check(4-2);
    unsigned short zp_address = get_zp_indexed_address(low_byte, vm.x);
    if(instruction == AND_ZP_X)and_bitwise_logic(memory.data[zp_address]);
    else if(instruction == EOR_ZP_X)eor_bitwise_logic(memory.data[zp_address]);
    else ora_bitwise_logic(memory.data[zp_address]);
    vm.cycles -= 1;
    debug(instruction, vm.accumulator);
}
void logical_zp_x_ind(unsigned char low_byte, unsigned char instruction)
{
    cycle_check(6-2);
    unsigned short indirect_address = get_zp_x_ind_address(low_byte);
    if(instruction == AND_ZP_X_IND)and_bitwise_logic(memory.data[indirect_address]);
    else if(instruction == EOR_ZP_X_IND)eor_bitwise_logic(memory.data[indirect_address]);
    else ora_bitwise_logic(memory.data[indirect_address]);
    vm.cycles -= 1;
    debug(instruction, vm.accumulator);
}
void logical_zp_y_ind(unsigned char low_byte, unsigned char instruction)
{
    cycle_check(5-2);
    unsigned short indirect_address = get_zp_y_ind_address_pc(low_byte);
    if(instruction == AND_ZP_Y_IND)and_bitwise_logic(memory.data[indirect_address]);
    else if(instruction == EOR_ZP_Y_IND)eor_bitwise_logic(memory.data[indirect_address]);
    else ora_bitwise_logic(memory.data[indirect_address]);
    vm.cycles -= 1;
    debug(instruction, vm.accumulator);
}

void bit_abs(unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(4-2);
    unsigned short address = get_abs_address(low_order_address);
    unsigned char and_value = vm.accumulator & memory.data[address];
    vm.cycles -= 1;
    BIT_update_NVZ(memory.data[address], and_value);
    debug(instruction, and_value);
}
void bit_zp(unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(3-2);
    unsigned short zp_address = get_zp_address(low_order_address);
    unsigned char and_value = vm.accumulator & memory.data[zp_address];
    vm.cycles -= 1;
    BIT_update_NVZ(memory.data[zp_address], and_value);
    debug(instruction, and_value);
}

// Helper logic functions
void and_bitwise_logic(unsigned char value)
{
    vm.accumulator &= value;
    updateNZFlags(vm.accumulator);
}
void eor_bitwise_logic(unsigned char value)
{
    vm.accumulator ^= value;
    updateNZFlags(vm.accumulator);
}
void ora_bitwise_logic(unsigned char value)
{
    vm.accumulator |= value;
    updateNZFlags(vm.accumulator);
}