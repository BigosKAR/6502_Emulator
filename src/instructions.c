#include "instructions.h"
#include <stdbool.h>
#include "flags.h"
#include <string.h>

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

void lda_abs_logic(unsigned int* cycles, unsigned char* low_byte, bool isX)
{
    unsigned char low_order_address = *low_byte;
    unsigned char high_order_address = fetch_byte(cycles);
    unsigned short address = (high_order_address <<8) | low_order_address;
    unsigned short temp_address;
    if(isX)
    {
        temp_address = address + vm.x;
        vm.accumulator = memory.data[address+vm.x];
    }
    else
    {
        temp_address = address + vm.y;
        vm.accumulator = memory.data[address+vm.y];
    }
    if((address & 0xFF00) != (temp_address & 0xFF00))
    {
        *cycles -= 1; // If page boundary crossed then take 1 cycle
    }
    *cycles -= 1; // reading the byte from memory
    LDA_flags();
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
                vm.accumulator = low_byte_data;
                LDA_flags();
                lda_debug(LDA_IMM);
                break;
            }
            case LDA_ABS: {
                unsigned char low_order_address = low_byte_data;
                unsigned char high_order_address = fetch_byte(cycles);
                unsigned short address = (high_order_address <<8) | low_order_address;
                vm.accumulator = memory.data[address];
                *cycles -= 1; // reading the byte from memory
                LDA_flags();
                lda_debug(LDA_ABS);
                break;
            }
            case LDA_ABS_X: {
                lda_abs_logic(cycles, &low_byte_data, true);
                lda_debug(LDA_ABS_X);
                break;
            }
            case LDA_ABS_Y: {
                lda_abs_logic(cycles, &low_byte_data, false);
                lda_debug(LDA_ABS_Y);
                break;
            }
            case LDA_ZP: {
                // Useful for faster execution time because there is no need to fetch another byte
                unsigned short address = (0x00<<8) | low_byte_data;
                vm.accumulator = memory.data[address];
                *cycles -= 1;
                LDA_flags();
                lda_debug(LDA_ZP);
                break;
            }
            case LDA_ZP_X: {
                unsigned short address = (0x00<<8) | low_byte_data;
                zp_wrapping(cycles, &address);
                vm.accumulator = memory.data[address];
                *cycles -= 1;
                LDA_flags();
                lda_debug(LDA_ZP_X);
                break;
            }
            case LDA_ZP_X_IND: {
                unsigned short address = (0x00<<8) | low_byte_data;
                unsigned short new_address;
                unsigned char high_b_add, low_b_add;
                zp_wrapping(cycles, &address);
                fetch_word_zp(cycles, address, &low_b_add, &high_b_add);
                new_address = (low_b_add << 8) | high_b_add;
                vm.accumulator = memory.data[new_address];
                *cycles -= 1;
                LDA_flags();
                lda_debug(LDA_ZP_X_IND);
                break;
            }
            case LDA_ZP_Y_IND: {
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
                
                }
                vm.accumulator = memory.data[indirect_address];
                *cycles -= 1;
                LDA_flags();
                lda_debug(LDA_ZP_Y_IND);
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

// zero page functions

void zp_wrapping(int* cycles, unsigned short* address)
{
    if((*address+vm.x)>0xFF) *address = *address + vm.x - 0xFF;
    else *address = *address + vm.x;
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
void lda_debug(unsigned char instruction)
{
    printf("INSTRUCTION %x: %d\n", instruction, vm.accumulator);
    display_flags();
}