#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"
#include "arith_instructions.h"
#include "../../addressing_modes.h"

void adc_imm(unsigned int* cycles, unsigned char low_byte, unsigned char instruction)
{
    cycle_check(2-2, cycles);
    adc_logic(low_byte);
    debug(instruction, vm.accumulator);
}
void adc_abs(unsigned int* cycles, unsigned low_order_address, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned short address = get_abs_address(cycles, low_order_address);
    adc_logic(memory.data[address]);
    *cycles -= 1;
    debug(instruction, vm.accumulator);
}
void adc_abs_reg_logic(unsigned int* cycles, unsigned low_order_address, unsigned char vm_register, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned short address = get_abs_indexed_address_pc(cycles, low_order_address, vm_register);
    adc_logic(memory.data[address]);
    *cycles -= 1;
    debug(instruction, vm.accumulator);
}
void adc_zp(unsigned int* cycles, unsigned low_order_address, unsigned char instruction)
{
    cycle_check(3-2, cycles);
    unsigned short zp_address = get_zp_address(low_order_address);
    adc_logic(memory.data[zp_address]);
    *cycles -= 1;
    debug(instruction, vm.accumulator);
}
void adc_zp_x(unsigned int* cycles, unsigned low_order_address, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned short zp_address = get_zp_indexed_address(cycles, low_order_address, vm.x);
    adc_logic(memory.data[zp_address]);
    *cycles -= 1;
    debug(instruction, vm.accumulator);
}
void adc_zp_x_ind(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(6-2, cycles);
    unsigned short indirect_address = get_zp_x_ind_address(cycles, low_order_address);
    adc_logic(memory.data[indirect_address]);
    *cycles -= 1;
    debug(instruction, vm.accumulator);
}
void adc_zp_y_ind(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(5-2, cycles);
    unsigned short indirect_address = get_zp_y_ind_address_pc(cycles, low_order_address);
    printf("Indirect address: %x\n", indirect_address);
    printf("Content at indirect address: %d\n", memory.data[indirect_address]);
    adc_logic(memory.data[indirect_address]);
    *cycles -= 1;
    debug(instruction, vm.accumulator);
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