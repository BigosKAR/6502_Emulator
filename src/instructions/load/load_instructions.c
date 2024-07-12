#include "../../instructions.h"
#include <stdbool.h>
#include "../../flags.h"
#include <string.h>
#include <stdlib.h>

void ld_abs_reg_logic(unsigned int* cycles, unsigned char* low_order_address, unsigned char* vm_register, unsigned char vm_reg_indexed, unsigned char instruction)
{
    cycle_check(4-2, cycles); 
    unsigned char high_order_address = fetch_byte(cycles); // -1 cycle
    unsigned short address = (high_order_address <<8) | *low_order_address;
    unsigned short temp_address;
    temp_address = address + vm_reg_indexed;
    if((address & 0xFF00) != (temp_address & 0xFF00))
    {
        *cycles -= 1; // If page boundary crossed then take 1 cycle
        cycle_check(1, cycles);
    }
    wrap_address(&temp_address);
    *vm_register = memory.data[temp_address];
    *cycles -= 1; // reading the byte from memory
    updateNZFlags(*vm_register);
    debug(instruction, *vm_register);
}
void ld_imm_logic(unsigned int* cycles, unsigned char* low_byte, unsigned char *vm_register, unsigned char instruction)
{
    cycle_check(2-2, cycles);
    *vm_register = *low_byte;
    updateNZFlags(*vm_register);
    debug(instruction, *vm_register);
}
void ld_abs_logic(unsigned int* cycles, unsigned char* low_order_address, unsigned char* vm_register, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned char high_order_address = fetch_byte(cycles);
    unsigned short address = (high_order_address <<8) | *low_order_address;
    *vm_register = memory.data[address];
    *cycles -= 1; // reading the byte from memory
    updateNZFlags(*vm_register);
    debug(instruction, *vm_register);
}
void ld_zp_logic(unsigned int* cycles, unsigned char* low_byte, unsigned char* vm_register, unsigned char instruction)
{
    cycle_check(3-2, cycles);
    unsigned short address = (0x00<<8) | *low_byte;
    *vm_register = memory.data[address];
    *cycles -= 1;
    updateNZFlags(*vm_register);
    debug(instruction, *vm_register);
}
void ld_zp_reg_logic(unsigned int* cycles, unsigned char* low_byte, unsigned char* vm_register, unsigned char vm_reg_indexed, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned short zp_address = (0x00<<8) | *low_byte;
    zp_wrapping(cycles, &zp_address, vm_reg_indexed); //changing the address, checking for potential zeropage wrapping
    *vm_register = memory.data[zp_address];
    *cycles -= 1;
    updateNZFlags(*vm_register);
    debug(instruction, *vm_register);
}
void lda_zp_x_ind(unsigned int* cycles, unsigned char* low_byte)
{
    cycle_check(6-2, cycles);
    unsigned short address = (0x00<<8) | *low_byte;
    unsigned short new_address;
    unsigned char high_b_add, low_b_add;
    zp_wrapping(cycles, &address, vm.x);  //changing the address, checking for potential zeropage wrapping
    fetch_word_zp(cycles, address, &low_b_add, &high_b_add);
    new_address = (low_b_add << 8) | high_b_add;
    vm.accumulator = memory.data[new_address];
    *cycles -= 1;
    updateNZFlags(vm.accumulator);
    debug(LDA_ZP_X_IND, vm.accumulator); 
}
void lda_zp_y_ind(unsigned int* cycles, unsigned char* low_byte)
{
    cycle_check(5-2, cycles); // does not check for extra cycle
    unsigned short address = (0x00<<8) | *low_byte;
    unsigned short indirect_address, temp_address;
    unsigned char high_b_add, low_b_add;
    fetch_word_zp(cycles, address, &low_b_add, &high_b_add); // -2 cycles
    indirect_address = low_b_add << 8 | high_b_add;
    temp_address = indirect_address;
    indirect_address+=vm.y;
    if((temp_address & 0xFF00) != (indirect_address & 0xFF00))
    {
        *cycles -= 1; // If page boundary crossed then take 1 cycle
        cycle_check(1, cycles);
    
    }
    wrap_address(&indirect_address);
    vm.accumulator = memory.data[indirect_address];
    *cycles -= 1;
    updateNZFlags(vm.accumulator);
    debug(LDA_ZP_Y_IND, vm.accumulator);
}
void st_abs_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_register, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned char high_order_address = fetch_byte(cycles);
    unsigned short address = (high_order_address <<8) | low_order_address;
    memory.data[address] = vm_register;
    *cycles -= 1; 
    // no flags affected
    debug(instruction, memory.data[address]);
}
void st_zp_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_register, unsigned char instruction)
{
    cycle_check(3-2, cycles);
    unsigned short address = (0x00<<8) | low_order_address;
    memory.data[address] = vm_register;
    *cycles -= 1;
    // no flags affected
    debug(instruction, memory.data[address]);
}
void st_zp_reg_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_register, unsigned char vm_reg_indexed, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned short zp_address = (0x00<<8) | low_order_address;
    zp_wrapping(cycles, &zp_address, vm_reg_indexed);  // takes 1 cycle
    memory.data[zp_address] = vm_register;
    *cycles -= 1;
    // no flags affected
    debug(instruction, memory.data[zp_address]);
}
void sta_abs_reg_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_reg_indexed, unsigned char instruction)
{
    cycle_check(5-2, cycles);
    unsigned short address = (fetch_byte(cycles) << 8) | low_order_address;
    address += vm_reg_indexed; // adding contents of the register to the address
    wrap_address(&address); 
    *cycles -= 1;
    memory.data[address] = vm.accumulator;
    *cycles -= 1;
    debug(instruction, memory.data[address]);
}
void sta_zp_x_ind(unsigned int* cycles, unsigned char low_byte)
{
    cycle_check(6-2, cycles);
    unsigned short zp_address = (0x00<<8) | low_byte;
    zp_wrapping(cycles, &zp_address, vm.x);
    unsigned short new_address;
    unsigned char high_b_add, low_b_add;
    fetch_word_zp(cycles, zp_address, &low_b_add, &high_b_add);
    new_address = (low_b_add << 8) | high_b_add;
    memory.data[new_address] = vm.accumulator;
    *cycles -= 1;
    debug(STA_ZP_X_IND, memory.data[new_address]);
}
void sta_zp_y_ind(unsigned int* cycles, unsigned char low_byte)
{
    cycle_check(6-2, cycles);
    unsigned short zp_address = (0x00 << 8) | low_byte;
    unsigned char high_b_add, low_b_add;
    fetch_word_zp(cycles, zp_address, &low_b_add, &high_b_add);
    unsigned short new_address = low_b_add << 8 | high_b_add;
    new_address += vm.y;
    *cycles -= 1;
    wrap_address(&new_address);
    memory.data[new_address] = vm.accumulator;
    *cycles -= 1;
    debug(STA_ZP_Y_IND, memory.data[new_address]);
}