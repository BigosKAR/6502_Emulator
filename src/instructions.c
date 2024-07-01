#include "instructions.h"
#include <stdbool.h>

// do to: implement the fetch function
unsigned char fetch(unsigned int* cycles, unsigned char* low_byte, unsigned char* high_byte)
{
    unsigned short data = *vm.ip;
    printf("Data: %x\n", data);
    // reversed because of little endian
    *high_byte = (data & 0x00FF);
    *low_byte = (data & 0xFF00) >> 8;
    vm.ip++;
    *cycles -= 1;
}

void reset_bytes(unsigned char* low_byte, unsigned char* high_byte)
{
    *low_byte = 0;
    *high_byte = 0;
}

void execute(unsigned int *cycles)
{
    unsigned char *high_byte_data;
    unsigned char *low_byte_data;
    
    while(*cycles > 0)
    {;
        fetch(cycles, low_byte_data, high_byte_data); // takes 1 cycle away

        switch(*high_byte_data)
        {
            case LDA: {
                vm.accumulator = *low_byte_data;
                reset_bytes(low_byte_data, high_byte_data);
                printf("LDA: %x\n", vm.accumulator);
                *cycles -= 1; // takes 1 cycles away
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