#include "instructions.h"
#include <stdbool.h>
#include "flags.h"
#include <string.h>

bool isOutOfBounds(unsigned short address)
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
    if(isOutOfBounds(vm.ip))
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
        printf("LDA_ABS_X: %d\n", vm.accumulator);
    }
    else
    {
        temp_address = address + vm.y;
        vm.accumulator = memory.data[address+vm.y];
        printf("LDA_ABS_Y: %d\n", vm.accumulator);

    }
    if((address & 0xFF00) != (temp_address & 0xFF00))
    {
        *cycles -= 1; // If page boundary crossed then take 1 cycle
    }
    *cycles -= 1; // reading the byte from memory
    LDA_flags();
    //display_flags();
}

void execute(unsigned int *cycles)
{
    unsigned char high_byte_data;
    unsigned char low_byte_data;
    while(*cycles > 0)
    {
        fetch_word(cycles, &low_byte_data, &high_byte_data); // takes 1 cycle away
        switch(high_byte_data)
        {
            case LDA_IMM: {
                vm.accumulator = low_byte_data;
                LDA_flags();
                // For Debugging
                //printf("LDA: %d\n", vm.accumulator);
                //display_flags();
                break;
            }
            case LDA_ABS: {
                unsigned char low_order_address = low_byte_data;
                unsigned char high_order_address = fetch_byte(cycles);
                unsigned short address = (high_order_address <<8) | low_order_address;
                vm.accumulator = memory.data[address];
                *cycles -= 1; // reading the byte from memory
                LDA_flags();
                //printf("LDA_ABS: %d\n", vm.accumulator);
                //display_flags();
                break;
            }
            case LDA_ABS_X: {
                lda_abs_logic(cycles, &low_byte_data, true);
                break;
            }
            case LDA_ABS_Y: {
                lda_abs_logic(cycles, &low_byte_data, false);
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