#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"
#include "logic_instructions.h"

// Main logic functions
void and_imm(unsigned int* cycles, unsigned char low_byte, unsigned char instruction)
{
    cycle_check(2-2, cycles);
    and_bitwise_logic(low_byte);
    debug(instruction, vm.accumulator);
}
void and_abs(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned char high_order_address = fetch_byte(cycles);
    unsigned short address = (high_order_address << 8) | low_order_address;
    and_bitwise_logic(memory.data[address]);
    *cycles -= 1;
    debug(instruction, vm.accumulator);
}

void and_abs_reg_logic(unsigned int* cycles, unsigned low_order_address, unsigned char vm_register, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned char high_order_address = fetch_byte(cycles);
    unsigned short address = (high_order_address << 8) | low_order_address;
    unsigned short temp_address = address + vm_register;
    if((address & 0xFF00) != (temp_address & 0xFF00))
    {
        if((temp_address >> 8) == 0);
        else
        {
        *cycles -= 1; // If page boundary crossed then take 1 cycle
        cycle_check(1, cycles);
        }
    }
    wrap_address(&temp_address); // may be unnecessary because C wraps around for unsigned short
    *cycles -= 1;
    and_bitwise_logic(memory.data[temp_address]);
    debug(instruction, vm.accumulator);
}
void and_zp(unsigned int* cycles, unsigned char low_byte, unsigned char instruction)
{
    cycle_check(3-2, cycles);
    unsigned short address = (0x00 << 8) | low_byte;
    and_bitwise_logic(memory.data[address]);
    *cycles -= 1;
    debug(instruction, vm.accumulator);
}
void and_zp_x(unsigned int* cycles, unsigned char low_byte, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned short zp_address = (0x00 << 8) | low_byte;
    zp_wrapping(cycles, &zp_address, vm.x);
    and_bitwise_logic(memory.data[zp_address]);
    *cycles -= 1;
    debug(instruction, vm.accumulator);
}
void and_zp_x_ind(unsigned int* cycles, unsigned char low_byte, unsigned char instruction)
{
    cycle_check(6-2, cycles);
    unsigned short zp_address = (0x00 << 8) | low_byte;
    zp_wrapping(cycles, &zp_address, vm.x);
    unsigned char low_b_data, high_b_data;
    fetch_word_zp(cycles, zp_address, &low_b_data, &high_b_data);
    unsigned short indirect_address = (low_b_data << 8) | high_b_data;
    and_bitwise_logic(memory.data[indirect_address]);
    *cycles -= 1;
    debug(instruction, vm.accumulator);
}
void and_zp_y_ind(unsigned int* cycles, unsigned char low_byte, unsigned char instruction)
{
    cycle_check(5-2, cycles);
    unsigned short address = (0x00 << 8) | low_byte;
    unsigned short temp_address = address;
    address += vm.y;
    if((temp_address & 0xFF00) != (address & 0xFF00))
    {
        *cycles -= 1; // If page boundary crossed then take 1 cycle
        cycle_check(1, cycles);
    }
    unsigned char low_b_data, high_b_data;
    fetch_word_zp(cycles, address, &low_b_data, &high_b_data);
    unsigned short indirect_address = (low_b_data << 8) | high_b_data;
    and_bitwise_logic(memory.data[indirect_address]);
    *cycles -= 1;
    debug(instruction, vm.accumulator);
}

// Helper logic functions
void and_bitwise_logic(unsigned char value)
{
    vm.accumulator &= value;
    updateNZFlags(vm.accumulator);
}