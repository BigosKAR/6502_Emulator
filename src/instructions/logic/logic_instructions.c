#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"
#include "logic_instructions.h"
#include "../../addressing_modes.h"

// Main logic functions

// Functions for AND, EOR, and OR (logical)
void logical_imm(InstructionParams params)
{
    cycle_check(params.required_cycles);
    unsigned char immediate_value = fetch_byte();
    if(params.instruction == AND_IMM)and_bitwise_logic(immediate_value);
    else if(params.instruction == EOR_IMM)eor_bitwise_logic(immediate_value);
    else if(params.instruction == ORA_IMM)ora_bitwise_logic(immediate_value);
    else printf("Could not find the given instruction!\n");
    if(VERBOSE)debug(params.instruction, vm.accumulator);
}

void logical_instruction(InstructionParams params, unsigned char* vm_register, LogicType logic_type)
{
    unsigned short address = fetch_address(params, vm_register);
    if(logic_type == LOGIC_AND)and_bitwise_logic(memory.data[address]);
    else if(logic_type == LOGIC_XOR)eor_bitwise_logic(memory.data[address]);
    else if(logic_type == LOGIC_OR)ora_bitwise_logic(memory.data[address]);
    else printf("Could not find the given logic type!\n");
    vm.cycles -= 1;
    if(VERBOSE)debug(params.instruction, vm.accumulator);
}

void bit_instruction(InstructionParams params)
{
    unsigned short address = fetch_address(params, NULL);
    unsigned char and_value = bit_logic(params, address);
    vm.cycles -= 1;
    if(VERBOSE)debug(params.instruction, and_value);
}

// Main logic functions
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
unsigned char bit_logic(InstructionParams params, unsigned short address){
    unsigned char and_value = vm.accumulator & memory.data[address];
    BIT_update_NVZ(memory.data[address], and_value);
    return and_value;
}