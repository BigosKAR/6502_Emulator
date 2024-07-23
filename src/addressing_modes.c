#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "flags.h"
#include "instructions.h"
#include "addressing_modes.h"

unsigned short get_abs_address(unsigned int* cycles, unsigned char low_order_address)
{
    unsigned char high_order_address = fetch_byte(cycles);
    return high_order_address << 8 | low_order_address;
}
// function for getting an address from adding the contents of a register to the absolute address (taking into account crossing mem pages)
unsigned short get_abs_indexed_address_pc(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_register)
{
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
    return address + vm_register;
}
unsigned short get_abs_indexed_address(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_register)
{
    unsigned char high_order_address = fetch_byte(cycles);
    unsigned short address = (high_order_address << 8) | low_order_address;
    return address + vm_register;
}
unsigned short get_zp_address(unsigned char low_order_address)
{
    return (0x00 << 8) | low_order_address;
}
unsigned short get_zp_indexed_address(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_register)
{
    unsigned short zp_address = get_zp_address(low_order_address);
    zp_wrapping(cycles, &zp_address, vm_register);
    return zp_address;
}
unsigned short get_zp_x_ind_address(unsigned int* cycles, unsigned char low_order_address)
{
    unsigned short zp_address = get_zp_address(low_order_address);
    zp_wrapping(cycles, &zp_address, vm.x);
    unsigned char low_b_data, high_b_data;
    fetch_word_zp(cycles, zp_address, &low_b_data, &high_b_data);
    unsigned short indirect_address = (low_b_data << 8) | high_b_data;
    return indirect_address;
}
unsigned short get_zp_y_ind_address_pc(unsigned int* cycles, unsigned char low_order_address)
{
    unsigned short zp_address = get_zp_address(low_order_address);
    unsigned char low_b_data, high_b_data;
    fetch_word_zp(cycles, zp_address, &low_b_data, &high_b_data);
    unsigned short indirect_address = (low_b_data << 8) | high_b_data;
    unsigned short temp_address = indirect_address;
    indirect_address += vm.y;
    if((temp_address & 0xFF00) != (indirect_address & 0xFF00))
    {
        if((indirect_address >> 8) == 0);
        else
        {
        *cycles -= 1; // If page boundary crossed then take 1 cycle
        cycle_check(1, cycles);
        }
    }
    return indirect_address;
}
unsigned short get_zp_y_ind_address(unsigned int* cycles, unsigned char low_order_address)
{
    unsigned short zp_address = get_zp_address(low_order_address);
    unsigned char low_b_data, high_b_data;
    fetch_word_zp(cycles, zp_address, &low_b_data, &high_b_data);
    unsigned short indirect_address = (low_b_data << 8) | high_b_data;
    indirect_address += vm.y;
    return indirect_address;
}