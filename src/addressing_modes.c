#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "flags.h"
#include "instructions.h"
#include "addressing_modes.h"


unsigned short get_abs_address()
{
    unsigned char low_order_address, high_order_address;
    fetch_word(&low_order_address, &high_order_address);
    return high_order_address << 8 | low_order_address;
}
// function for getting an address from adding the contents of a register to the absolute address (taking into account crossing mem pages)
unsigned short get_abs_indexed_address_pc(unsigned char vm_register)
{
    unsigned char low_order_address, high_order_address;
    fetch_word(&low_order_address, &high_order_address);
    unsigned short address = (high_order_address << 8) | low_order_address;
    unsigned short temp_address = address + vm_register;
    if((address & 0xFF00) != (temp_address & 0xFF00))
    {
        if((temp_address >> 8) == 0);
        else
        {
        vm.cycles -= 1; // If page boundary crossed then take 1 cycle
        cycle_check(2); // Check if there is 1 cycle saved (1 cycle are subtracted)
        }
    }
    return address + vm_register;
}
unsigned short get_abs_indexed_address(unsigned char vm_register)
{
    unsigned char low_order_address, high_order_address;
    fetch_word(&low_order_address, &high_order_address);
    unsigned short address = (high_order_address << 8) | low_order_address;
    return address + vm_register;
}

unsigned short get_abs_ind_address()
{
    unsigned char low_order_address, high_order_address;
    fetch_word(&low_order_address, &high_order_address);
    unsigned short initial_address = (high_order_address << 8) | low_order_address;
    unsigned char Low_order_indirect_address, high_order_indirect_address;
    Low_order_indirect_address = memory.data[initial_address];
    high_order_indirect_address = memory.data[initial_address + 1];
    unsigned short indirect_address = (high_order_indirect_address << 8) | Low_order_indirect_address;
    vm.cycles -= 2;
    return indirect_address;
}

unsigned short get_zp_address()
{
    unsigned char low_order_address = fetch_byte();
    return (0x00 << 8) | low_order_address;
}
unsigned short get_zp_indexed_address(unsigned char vm_register)
{
    unsigned short zp_address = get_zp_address();
    zp_wrapping(&zp_address, vm_register);
    return zp_address;
}
unsigned short get_zp_x_ind_address()
{
    unsigned short zp_address = get_zp_address();
    zp_wrapping(&zp_address, vm.x);
    unsigned char high_order_address, low_order_address;
    fetch_word_zp(zp_address, &low_order_address, &high_order_address);
    unsigned short indirect_address = (high_order_address << 8) | low_order_address;
    return indirect_address;
}
unsigned short get_zp_y_ind_address_pc()
{
    unsigned short zp_address = get_zp_address();
    unsigned char low_order_address, high_order_address;
    fetch_word_zp(zp_address, &low_order_address, &high_order_address);
    unsigned short indirect_address = (high_order_address << 8) | low_order_address;
    unsigned short temp_address = indirect_address;
    indirect_address += vm.y;
    if((temp_address & 0xFF00) != (indirect_address & 0xFF00))
    {
        if((indirect_address >> 8) == 0);
        else
        {
        vm.cycles -= 1; // If page boundary crossed then take 1 cycle
        cycle_check(2); // It is 3 because the cycle check takes 2 cycles away and we are checking if there is 1 cycle saved
        }
    }
    return indirect_address;
}
unsigned short get_zp_y_ind_address()
{
    unsigned short zp_address = get_zp_address();
    unsigned char high_order_address, low_order_address;
    fetch_word_zp(zp_address, &low_order_address, &high_order_address);
    unsigned short indirect_address = (high_order_address << 8) | low_order_address;
    indirect_address += vm.y;
    return indirect_address;
}

unsigned short fetch_address(InstructionParams params, unsigned char* vm_register)
{
    cycle_check(params.required_cycles);
    switch(params.addressing_mode) {
        case ACCUMULATOR:
        case IMMEDIATE:
        case IMPLIED:
            printf("Invalid addressing mode\n");
            return 0; //  No address (should not be used)
        case ABSOLUTE: {
            return get_abs_address();
        }
        case ABSOLUTE_INDEXED: {
            if(vm_register == NULL){
                printf("Invalid register. Tried to dereference a NULL pointer!\n");
                exit(1);
            }
            return get_abs_indexed_address(*vm_register);
        }
        case ABSOLUTE_INDEXED_PC: {
            if(vm_register == NULL){
                printf("Invalid register. Tried to dereference a NULL pointer!\n");
                exit(1);
            }
            return get_abs_indexed_address_pc(*vm_register);
        }
        case ABSOLUTE_INDIRECT:
            return get_abs_ind_address();
        case ZERO_PAGE:
            return get_zp_address();
        case ZERO_PAGE_INDEXED: {
            if(vm_register == NULL){
                printf("Invalid register. Tried to dereference a NULL pointer!\n");
                exit(1);
            }
            return get_zp_indexed_address(*vm_register);
        }
        case ZERO_PAGE_X_INDIRECT:
            return get_zp_x_ind_address();
        case ZERO_PAGE_Y_INDIRECT:
            return get_zp_y_ind_address();
        case ZERO_PAGE_Y_INDIRECT_PC:
            return get_zp_y_ind_address_pc();
        default: {
            printf("Invalid addressing mode\n");
            return 0;
            exit(1);
        }
    }
}