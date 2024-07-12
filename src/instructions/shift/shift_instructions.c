#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"

// Main shift functions
void shift_acc_logic(unsigned int* cycles, unsigned char instruction)
{
    onebyte_ins_fix(cycles);
    cycle_check(2-1, cycles);
    unsigned char temp_var = vm.accumulator;
    if(instruction == ASL_A)
    {
        vm.accumulator = vm.accumulator << 1;
        updateNZC_Flags(vm.accumulator, temp_var);
    }
    else 
    {
        vm.accumulator = vm.accumulator >> 1;
        LSR_update_NZC_Flags(vm.accumulator, temp_var);
    }
    *cycles -= 1;
    debug(instruction, vm.accumulator);
}
void shift_abs_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(6-2, cycles);
    unsigned char high_order_address = fetch_byte(cycles);
    unsigned short address = (high_order_address << 8) | low_order_address;
    unsigned char temp_var = memory.data[address];
    if(instruction == ASL_ABS)
    {
        memory.data[address] = memory.data[address] << 1;
        updateNZC_Flags(memory.data[address], temp_var);
    }
    else
    {
        memory.data[address] = memory.data[address] >> 1;
        LSR_update_NZC_Flags(memory.data[address], temp_var);
    }
    *cycles -= 3; // reading memory from initial address, shifting the value, and writing it back to the same location
    debug(instruction, memory.data[address]);
}
void shift_abs_x_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(7-2, cycles);
    unsigned char high_order_address = fetch_byte(cycles); // -1 cycle
    unsigned short new_address = high_order_address << 8 | low_order_address;
    new_address += vm.x;
    wrap_address(&new_address);
    unsigned char temp_var = memory.data[new_address];
    if(instruction == ASL_ABS_X)
    {
        memory.data[new_address] = memory.data[new_address] << 1;
        updateNZC_Flags(memory.data[new_address], temp_var);
    }
    else
    {
        memory.data[new_address] = memory.data[new_address] >> 1;
        LSR_update_NZC_Flags(memory.data[new_address], temp_var);
    }
    *cycles -= 4; // adding x reg content to an address, reading memory from that address, performing the shift, and writing the result back to the same location
    debug(instruction, memory.data[new_address]);
}
void shift_zp_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(5-2, cycles);
    unsigned short zp_address = (0x00 << 8) | low_order_address;
    unsigned char temp_var = memory.data[zp_address];
    if(instruction == ASL_ZP)
    {
        memory.data[zp_address] = memory.data[zp_address] << 1;
        updateNZC_Flags(memory.data[zp_address], temp_var);
    }
    else
    {
        memory.data[zp_address] = memory.data[zp_address] >> 1;
        LSR_update_NZC_Flags(memory.data[zp_address], temp_var);
    }
    *cycles -= 3; // reading memory from initial address, performing the shift, and writing the result back to the same location
    debug(instruction, memory.data[zp_address]);
}
void shift_zp_x_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(6-2, cycles);
    unsigned short zp_address = (0x00 << 8) | low_order_address;
    zp_wrapping(cycles, &zp_address, vm.x);
    unsigned char temp_var = memory.data[zp_address];
    if(instruction == ASL_ABS_X)
    {
        memory.data[zp_address] = memory.data[zp_address] << 1;
        updateNZC_Flags(memory.data[zp_address], temp_var);
    }
    else
    {
        memory.data[zp_address] = memory.data[zp_address] >> 1;
        LSR_update_NZC_Flags(memory.data[zp_address], temp_var);
    }
    *cycles -= 3; // reading memory from initial address, performing the shift, and writing the result back to the same location
    debug(instruction, memory.data[zp_address]);
}

void rotate_acc_logic(unsigned int* cycles, unsigned char instruction)
{
    onebyte_ins_fix(cycles);
    cycle_check(2-1, cycles);
    unsigned char temp_var = vm.accumulator;
    if(instruction == ROL_A)
    {
       rotate_logic(&vm.accumulator, true);
    }
    else
    {
        rotate_logic(&vm.accumulator, false);
    }
    *cycles -= 1; // performing the shift
    debug(instruction, vm.accumulator);
}
void rotate_abs_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(6-2, cycles);
    unsigned char high_order_address = fetch_byte(cycles);
    unsigned short address = (high_order_address << 8) | low_order_address;
    if(instruction == ROL_ABS)
    {
        rotate_logic(&memory.data[address], true);
    }
    else
    {
        rotate_logic(&memory.data[address], false);
    }
    *cycles -= 3; // reading memory from initial address, performing the shift, and writing the result back to the same location
    debug(instruction, memory.data[address]);
}
void rotate_abs_x_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(7-2, cycles);
    unsigned char high_order_address = fetch_byte(cycles);
    unsigned short address = high_order_address << 8 | low_order_address;
    address += vm.x;
    wrap_address(&address);
    if(instruction == ROL_ABS_X)
    {
        rotate_logic(&memory.data[address], true);
    }
    else
    {
        rotate_logic(&memory.data[address], false);
    }
    *cycles -= 4; // adding x reg content to an address, reading memory from that address, performing the shift, and writing the result back to the same location
    debug(instruction, memory.data[address]);
}
void rotate_zp_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(5-2, cycles);
    unsigned short zp_address = (0x00 << 8) | low_order_address;
    if(instruction == ROL_ZP)
    {
        rotate_logic(&memory.data[zp_address], true);
    }
    else
    {
        rotate_logic(&memory.data[zp_address], false);
    }
    *cycles -= 3; // reading memory from initial address, performing the shift, and writing the result back to the same location
    debug(instruction, memory.data[zp_address]);
}
void rotate_zp_x_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(6-2, cycles);
    unsigned short zp_address = (0x00 << 8) | low_order_address;
    zp_wrapping(cycles, &zp_address, vm.x);
    if(instruction == ROL_ZP_X)
    {
        rotate_logic(&memory.data[zp_address], true);
    }
    else
    {
        rotate_logic(&memory.data[zp_address], false);
    }
    *cycles -= 3; // read, shift, write back
    debug(instruction, memory.data[zp_address]);
}

// Helper shift functions
void rotate_logic(unsigned char* value, bool isLeft)
{
    if(isLeft)
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
    else
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