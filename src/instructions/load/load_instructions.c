#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../flags.h"
#include "../../instructions.h"
#include "load_instructions.h"
#include "../../addressing_modes.h"

void ld_imm(InstructionParams params, unsigned char *vm_register)
{
    unsigned char immediate_value = fetch_byte();
    cycle_check(params.required_cycles);
    ld_logic(vm_register, immediate_value);
    if(VERBOSE)debug(params.instruction, *vm_register);
}

void ld_instruction(InstructionParams params, unsigned char* vm_register, unsigned char* index_register)
{
    unsigned short address = fetch_address(params, index_register);
    ld_logic(vm_register, memory.data[address]);
    vm.cycles -= 1;
    if(VERBOSE)debug(params.instruction, *vm_register);
}

void ld_logic(unsigned char* vm_register, unsigned char value)
{
    *vm_register = value;
    updateNZFlags(*vm_register);
}

void st_instruction(InstructionParams params, unsigned char vm_register, unsigned char* index_register)
{
    unsigned short address = fetch_address(params, index_register);
    st_logic(vm_register, address);
    // 3 Addressing modes for STA take 1 more cycle then rest (not considering the cycles taken during the address fetch process)
    if(params.instruction == STA_ABS_X || params.instruction == STA_ABS_Y || params.instruction == STA_ZP_Y_IND)vm.cycles -= 2; 
    else vm.cycles -= 1;
    if(VERBOSE)debug(params.instruction, memory.data[address]);
}

void st_logic(unsigned char register_value, unsigned short address)
{
    memory.data[address] = register_value;
}