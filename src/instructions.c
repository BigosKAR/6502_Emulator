#include "instructions.h"
#include <stdbool.h>
#include "flags.h"
#include <string.h>
#include <stdlib.h>

bool out_of_bounds(unsigned short address)
{
    return address > MEM_MAX_SIZE;
}

void fetch_word(unsigned int* cycles, unsigned char* low_byte, unsigned char* high_byte)
{
    if(vm.ip == MEM_MAX_SIZE)
    {
        vm.ip = 0;
        *high_byte = memory.data[vm.ip];
        vm.ip++;
        *low_byte = memory.data[vm.ip];
        vm.ip++;
    }
    
    else if(vm.ip+2 == MEM_MAX_SIZE)
    {
        *high_byte = memory.data[vm.ip];
        *low_byte = memory.data[vm.ip+1];
        vm.ip = 0;
    }
    else if(vm.ip+1 == MEM_MAX_SIZE)
    {
        *high_byte = memory.data[vm.ip];
        vm.ip = 0;
        *low_byte = memory.data[vm.ip];
        vm.ip++;
    }
    else
    {
        *high_byte = memory.data[vm.ip];
        vm.ip++;
        *low_byte = memory.data[vm.ip];
        vm.ip++;
    }
    *cycles -= 2;
}

unsigned char fetch_byte(unsigned int* cycles)
{
    unsigned char Byte = memory.data[vm.ip];
    vm.ip += 1;
    if(out_of_bounds(vm.ip))
    {
        vm.ip = 0;
    }
    //printf("POINTER POINTS TO: %x\n", *vm.ip);
    *cycles -= 1;
    return Byte;
}

// execution of instructions *most important function*
void execute(unsigned int *cycles)
{
    unsigned char high_byte_data;
    unsigned char low_byte_data;
    while(*cycles > 0)
    {
        if(*cycles <= 0)break;
        fetch_word(cycles, &low_byte_data, &high_byte_data); // takes 2 cycles away
        switch(high_byte_data)
        {
            case LDA_IMM: {
                ld_imm_logic(cycles, &low_byte_data, &vm.accumulator, LDA_IMM);
                break;
            }
            case LDA_ABS: {
                cycle_check(4-2, cycles);
                unsigned char low_order_address = low_byte_data;
                unsigned char high_order_address = fetch_byte(cycles);
                unsigned short address = (high_order_address <<8) | low_order_address;
                vm.accumulator = memory.data[address];
                *cycles -= 1; // reading the byte from memory
                LD_flags(vm.accumulator);
                debug(LDA_ABS, vm.accumulator);
                break;
            }
            case LDA_ABS_X: {
                lda_abs_logic(cycles, &low_byte_data, vm.x, LDA_ABS_X);
                break;
            }
            case LDA_ABS_Y: {
                lda_abs_logic(cycles, &low_byte_data, vm.y, LDA_ABS_Y);
                break;
            }
            case LDA_ZP: {
                // Useful for faster execution time because there is no need to fetch another byte
                cycle_check(3-2, cycles);
                unsigned short address = (0x00<<8) | low_byte_data;
                vm.accumulator = memory.data[address];
                *cycles -= 1;
                LD_flags(vm.accumulator);
                debug(LDA_ZP, vm.accumulator);
                break;
            }
            case LDA_ZP_X: {
                cycle_check(4-2, cycles);
                unsigned short address = (0x00<<8) | low_byte_data;
                zp_wrapping(cycles, &address, vm.x);  //changing the address, checking for potential zeropage wrapping
                vm.accumulator = memory.data[address];
                *cycles -= 1;
                LD_flags(vm.accumulator);
                debug(LDA_ZP_X, vm.accumulator);
                break;
            }
            case LDA_ZP_X_IND: {
                cycle_check(6-2, cycles);
                unsigned short address = (0x00<<8) | low_byte_data;
                unsigned short new_address;
                unsigned char high_b_add, low_b_add;
                zp_wrapping(cycles, &address, vm.x);  //changing the address, checking for potential zeropage wrapping
                fetch_word_zp(cycles, address, &low_b_add, &high_b_add);
                new_address = (low_b_add << 8) | high_b_add;
                vm.accumulator = memory.data[new_address];
                *cycles -= 1;
                LD_flags(vm.accumulator);
                debug(LDA_ZP_X_IND, vm.accumulator);
                break;
            }
            case LDA_ZP_Y_IND: {
                cycle_check(5-2, cycles); // does not check for extra cycle
                unsigned short address = (0x00<<8) | low_byte_data;
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
                vm.accumulator = memory.data[indirect_address];
                *cycles -= 1;
                LD_flags(vm.accumulator);
                debug(LDA_ZP_Y_IND, vm.accumulator);
                break;
            }
            case LDX_IMM: {
                ld_imm_logic(cycles, &low_byte_data, &vm.x, LDX_IMM);
                break;
            }
            case LDX_ABS: {
                cycle_check(4-2, cycles);
                unsigned short address = (fetch_byte(cycles) << 8) | low_byte_data;
                vm.x = memory.data[address];
                *cycles -= 1;
                LD_flags(vm.x);
                debug(LDX_ABS, vm.x);
                break;
            }
            case LDX_ABS_Y: {
                cycle_check(4-2, cycles);
                unsigned short address, temp_address;
                address = (fetch_byte(cycles) << 8) | low_byte_data;
                temp_address = address;
                address += vm.y;
                if((temp_address & 0xFF00) != (address & 0xFF00))
                {
                    *cycles -= 1;
                    cycle_check(1, cycles);
                }
                vm.x = memory.data[address];
                *cycles -= 1;
                LD_flags(vm.x);
                debug(LDX_ABS_Y, vm.x);
                break;
            }
            case LDX_ZP: {
                cycle_check(3-2, cycles);
                unsigned short zp_address = (0x00<<8) | low_byte_data;
                vm.x = memory.data[zp_address];
                *cycles -= 1;
                LD_flags(vm.x);
                debug(LDX_ZP, vm.x);
                break;
            }
            case LDX_ZP_Y: {
                cycle_check(4-2, cycles);
                unsigned short zp_address = (0x00<<8) | low_byte_data;
                zp_wrapping(cycles, &zp_address, vm.y); //changing the address, checking for potential zeropage wrapping
                vm.x = memory.data[zp_address];
                *cycles -= 1;
                LD_flags(vm.x);
                debug(LDX_ZP_Y, vm.x);
                break;
            }
            case LDY_IMM: {
                ld_imm_logic(cycles, &low_byte_data, &vm.y, LDY_IMM);
                break;
            }
            default: {
                printf("ERROR: OPCODE NOT FOUND\n");
                *cycles = 0;
                break;
            }
        }
    }
}

// instruction functions for repeating code
void lda_abs_logic(unsigned int* cycles, unsigned char* low_byte, unsigned char vm_register, unsigned char instruction)
{
    cycle_check(4-2, cycles); 
    unsigned char low_order_address = *low_byte;
    unsigned char high_order_address = fetch_byte(cycles);
    unsigned short address = (high_order_address <<8) | low_order_address;
    unsigned short temp_address;
    temp_address = address + vm_register;
    vm.accumulator = memory.data[address+vm_register];
    if((address & 0xFF00) != (temp_address & 0xFF00))
    {
        *cycles -= 1; // If page boundary crossed then take 1 cycle
        cycle_check(1, cycles);
    }
    *cycles -= 1; // reading the byte from memory
    LD_flags(vm.accumulator);
    debug(instruction, vm.accumulator);
}

void ld_imm_logic(unsigned int* cycles, unsigned char* low_byte, unsigned char *vm_register, unsigned char instruction)
{
    cycle_check(2-2, cycles);
    *vm_register = *low_byte;
    LD_flags(*vm_register);
    debug(instruction, *vm_register);
}

// zero page functions
void zp_wrapping(int* cycles, unsigned short* address, unsigned char vm_register)
{
    if((*address+vm_register)>0xFF) *address = *address + vm_register - 0x100; // -0x100 to include the 0th position in memory
    else *address = *address + vm_register;
    *cycles -= 1;
}
void fetch_word_zp(unsigned int* cycles, unsigned short address, unsigned char* low_byte, unsigned char* high_byte)
{
    // fetching the word from an address given by 2 bytes in the zeropage
    if(address == 0x00FF)
    {
        *high_byte = memory.data[0x00FF];
        *low_byte = memory.data[0x0000];
    }
    else
    {
        *high_byte = memory.data[address];
        *low_byte = memory.data[address+1];
    }
    *cycles -= 2;
}

// debugging functions
void debug(unsigned char instruction, unsigned char vm_register)
{
    printf("INSTRUCTION %x: %d\n", instruction, vm_register);
    display_flags();
}

// other functions
void cycle_check(unsigned int cycle_amount, unsigned int* cycles)
{
    if(!(*cycles >= cycle_amount)) // -2 cycles because the first operation is the same for every instruction (opcode and 1 operand)
    {
        printf("Insufficient cycle amount!\n");
        exit(EXIT_FAILURE);
    }
}