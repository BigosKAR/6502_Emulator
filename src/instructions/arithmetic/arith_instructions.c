#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"
#include "arith_instructions.h"
#include "../../addressing_modes.h"

void adc_imm(InstructionParams params)
{
    cycle_check(params.required_cycles);
    adc_logic(params.low_byte);
    debug(params.instruction, vm.accumulator);
}
void adc_instruction(InstructionParams params, unsigned char* vm_register)
{
    unsigned short address = fetch_address(params, vm_register);
    adc_logic(memory.data[address]);
    vm.cycles -= 1;
    debug(params.instruction, vm.accumulator);
}

// Seperate function for the immediate addressing mode because of the lack of an address + no additional cycles required
void cm_imm(InstructionParams params,unsigned char vm_register)
{
    cycle_check(params.required_cycles);
    compare_logic(vm_register, params.low_byte);
    debug(params.instruction, vm_register);
}
void cm_instruction(InstructionParams params, unsigned char vm_register, unsigned char *index_register)
{
    unsigned short address = fetch_address(params, index_register);
    printf("Address: %x\n", address);
    compare_logic(vm_register, memory.data[address]);
    vm.cycles -= 1;
    debug(params.instruction, vm_register);
}

void compare_logic(unsigned char vm_register, unsigned char memory_value)
{
    unsigned char result = vm_register - memory_value;
    if((result >> 7) & 1)set_flag(FLAG_NEGATIVE);
    else clear_flag(FLAG_NEGATIVE);
    if(result == 0)set_flag(FLAG_ZERO);
    else clear_flag(FLAG_ZERO);
    if(vm_register >= memory_value)set_flag(FLAG_CARRY);
    else clear_flag(FLAG_CARRY);
}
void adc_logic(unsigned char char_value)
{
    // Larger data types to use for comparison
    unsigned short accumulator = vm.accumulator;
    unsigned short result;
    unsigned int value = char_value;
    bool carry = vm.processor_status & FLAG_CARRY;
    bool decimal_mode = vm.processor_status & FLAG_DECIMAL;
    if(decimal_mode)
    {
        unsigned char low_nibble = (accumulator & 0x0F) + (value & 0x0F) + (carry ? 1 : 0);
        if(low_nibble > 9)low_nibble += 6; // Adjust to fit BCD (skip over the unused values)
        unsigned char high_nibble = ((accumulator & 0xF0) >> 4) + ((value & 0xF0) >> 4) + ((low_nibble & 0xF0) >> 4);
        if(high_nibble > 9)
        {
            high_nibble += 6;
            set_flag(FLAG_CARRY);
        }
        else
        {
            clear_flag(FLAG_CARRY);
        }
        result = ((high_nibble & 0x0F) << 4) | (low_nibble & 0x0F);
    }
    else
    {
        if(carry)result = accumulator + value + 1;
        else result = accumulator + value;
        if(result > 0xFF)set_flag(FLAG_CARRY);
        else clear_flag(FLAG_CARRY);
    }
    bool accumulator_sign = accumulator & 0x80;
    bool value_sign = value & 0x80;
    bool result_sign = result & 0x80;

    if((accumulator_sign == value_sign) && (accumulator_sign != result_sign))set_flag(FLAG_OVERFLOW);
    else clear_flag(FLAG_OVERFLOW);

    vm.accumulator = result & 0xFF;
    updateNZFlags(vm.accumulator);
}