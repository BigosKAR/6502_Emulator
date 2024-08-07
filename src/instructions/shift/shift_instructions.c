#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"
#include "shift_instructions.h"
#include "../../addressing_modes.h"

// Main shift functions
void shift_accumulator(InstructionParams params, ShiftType shift_type)
{
    onebyte_ins_fix();
    cycle_check(params.required_cycles+1); // + 1 because its a onebyte instruction
    unsigned char temp_var = vm.accumulator;
    if(shift_type == SHIFT_ASL)
    {
        vm.accumulator = vm.accumulator << 1;
        updateNZC_Flags(vm.accumulator, temp_var);
    }
    else 
    {
        vm.accumulator = vm.accumulator >> 1;
        LSR_update_NZC_Flags(vm.accumulator, temp_var);
    }
    vm.cycles -= 1;
    debug(params.instruction, vm.accumulator);
}

void shift_instruction(InstructionParams params, unsigned char* vm_register, ShiftType shift_type)
{
    unsigned short address = fetch_address(params, vm_register);
    printf("Memory[address]: %d\n", memory.data[address]);
    unsigned char temp_var = memory.data[address];
    shift_logic(address, temp_var, shift_type);
    switch (params.instruction)
    {
    case ASL_ABS:
    case LSR_ABS:
    case ASL_ZP:
    case LSR_ZP:
    case ASL_ZP_X:
    case LSR_ZP_X:
        vm.cycles -= 3;
        break;
    case ASL_ABS_X:
    case LSR_ABS_X:
        vm.cycles -= 4;
        break;
    default: {
        printf("Invalid instruction for this function!\n");
        exit(1);
        break;
        }
    }
        debug(params.instruction, memory.data[address]);

}

void rotate_accumulator(InstructionParams params, ShiftType shift_type)
{
    onebyte_ins_fix();
    cycle_check(params.required_cycles+1);
    rotate_logic(&vm.accumulator, shift_type);
    vm.cycles -= 1; // performing the shift
    debug(params.instruction, vm.accumulator);
}

void rotate_instruction(InstructionParams params, unsigned char* vm_register, ShiftType shift_type)
{
    unsigned short address = fetch_address(params, vm_register);
    rotate_logic(&memory.data[address], shift_type);
    switch(params.instruction)
    {
        case ROL_ABS_X:
        case ROR_ABS_X:
            vm.cycles -= 4;
            break;
        case ROL_ABS:
        case ROR_ABS:
        case ROL_ZP:
        case ROR_ZP:
        case ROL_ZP_X:
        case ROR_ZP_X:
            vm.cycles -= 4;
            break;
        default: {
            printf("Invalid rotate instruction!\n");
            exit(1);
            break;
        }
    }
    debug(params.instruction, memory.data[address]);
}

// Helper shift functions
void rotate_logic(unsigned char* value, ShiftType shift_type)
{
    if(shift_type == SHIFT_ROL)
    {
        if(*value & 0b10000000){
            set_flag(FLAG_CARRY); // Set the carry flag to the value of the 7th bit of the A register
        }
        else{
            clear_flag(FLAG_CARRY); // Clear it if the value is 0
        }
        *value = *value << 1;
        *value |= (vm.processor_status & 0b00000001) ? 1 : 0;
    }
    else if(shift_type == SHIFT_ROR)
    {
        if(*value & 1){
            set_flag(FLAG_CARRY); // Set the carry flag to the value of the 7th bit of the A register
        }
        else{
            clear_flag(FLAG_CARRY); // Clear it if the value is 0
        }
        *value = *value >> 1;
        *value |= (vm.processor_status & 0b00000001) ? 0b10000000 : 0b00000000;
    }
    updateNZFlags(*value);
}
void shift_logic(unsigned short address, unsigned char temp_var, ShiftType shift_type)
{
    if(shift_type == SHIFT_ASL)
    {
        memory.data[address] = memory.data[address] << 1;
        updateNZC_Flags(memory.data[address], temp_var);
    }
    else if(shift_type == SHIFT_LSR)
    {
        memory.data[address] = memory.data[address] >> 1;
        LSR_update_NZC_Flags(memory.data[address], temp_var);
    }
    else printf("Invalid shift type for this type of instruction!\n");
}