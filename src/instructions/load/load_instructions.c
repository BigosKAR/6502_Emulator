#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../flags.h"
#include "../../instructions.h"
#include "load_instructions.h"
#include "../../addressing_modes.h"

void ld_abs_reg_logic(unsigned int* cycles, unsigned char* low_order_address, unsigned char* vm_register, unsigned char vm_reg_indexed, unsigned char instruction)
{
    cycle_check(4-2, cycles); 
    unsigned short address = get_abs_indexed_address_pc(cycles, *low_order_address, vm_reg_indexed);
    *vm_register = memory.data[address];
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
void ld_abs_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char* vm_register, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned short address = get_abs_address(cycles, low_order_address);
    *vm_register = memory.data[address];
    *cycles -= 1; // reading the byte from memory
    updateNZFlags(*vm_register);
    debug(instruction, *vm_register);
}
void ld_zp_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char* vm_register, unsigned char instruction)
{
    cycle_check(3-2, cycles);
    unsigned short zp_address = get_zp_address(low_order_address);
    *vm_register = memory.data[zp_address];
    *cycles -= 1;
    updateNZFlags(*vm_register);
    debug(instruction, *vm_register);
}
void ld_zp_reg_logic(unsigned int* cycles, unsigned char low_byte, unsigned char* vm_register, unsigned char vm_reg_indexed, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned short zp_address = get_zp_indexed_address(cycles, low_byte, vm_reg_indexed);
    *vm_register = memory.data[zp_address];
    *cycles -= 1;
    updateNZFlags(*vm_register);
    debug(instruction, *vm_register);
}
void lda_zp_x_ind(unsigned int* cycles, unsigned char low_order_address)
{
    cycle_check(6-2, cycles);
    unsigned short indirect_address = get_zp_x_ind_address(cycles, low_order_address);
    vm.accumulator = memory.data[indirect_address];
    *cycles -= 1;
    updateNZFlags(vm.accumulator);
    debug(LDA_ZP_X_IND, vm.accumulator); 
}
void lda_zp_y_ind(unsigned int* cycles, unsigned char low_order_address)
{
    cycle_check(5-2, cycles); // does not check for extra cycle
    unsigned short indirect_address = get_zp_y_ind_address_pc(cycles, low_order_address);
    vm.accumulator = memory.data[indirect_address];
    *cycles -= 1;
    updateNZFlags(vm.accumulator);
    debug(LDA_ZP_Y_IND, vm.accumulator);
}

void st_abs_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_register, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned short address = get_abs_address(cycles, low_order_address);
    memory.data[address] = vm_register;
    *cycles -= 1; 
    // no flags affected
    debug(instruction, memory.data[address]);
}
void st_zp_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_register, unsigned char instruction)
{
    cycle_check(3-2, cycles);
    unsigned short zp_address = get_zp_address(low_order_address);
    memory.data[zp_address] = vm_register;
    *cycles -= 1;
    // no flags affected
    debug(instruction, memory.data[zp_address]);
}
void st_zp_reg_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_register, unsigned char vm_reg_indexed, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned short zp_address = get_zp_indexed_address(cycles, low_order_address, vm_reg_indexed);
    memory.data[zp_address] = vm_register;
    *cycles -= 1;
    // no flags affected
    debug(instruction, memory.data[zp_address]);
}
void sta_abs_reg_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_reg_indexed, unsigned char instruction)
{
    cycle_check(5-2, cycles);
    unsigned short address = get_abs_indexed_address(cycles, low_order_address, vm_reg_indexed);
    *cycles -= 1;
    memory.data[address] = vm.accumulator;
    *cycles -= 1;
    debug(instruction, memory.data[address]);
}
void sta_zp_x_ind(unsigned int* cycles, unsigned char low_order_address)
{
    cycle_check(6-2, cycles);
    unsigned short indirect_address = get_zp_x_ind_address(cycles, low_order_address);
    memory.data[indirect_address] = vm.accumulator;
    *cycles -= 1;
    debug(STA_ZP_X_IND, memory.data[indirect_address]);
}
void sta_zp_y_ind(unsigned int* cycles, unsigned char low_order_address)
{
    cycle_check(6-2, cycles);
    unsigned short indirect_address = get_zp_y_ind_address(cycles, low_byte);
    *cycles -= 1;
    memory.data[indirect_address] = vm.accumulator;
    *cycles -= 1;
    debug(STA_ZP_Y_IND, memory.data[indirect_address]);
}