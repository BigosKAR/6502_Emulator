#include "instructions.h"

unsigned char fetch(unsigned int *cycles)
{
    printf("Pointer: %d\n", *vm.ip);
    unsigned char fetched_data = memory.data[*vm.ip];
    printf("Fetched data: %d\n", fetched_data);
    vm.ip++;
    *cycles--;
    return fetched_data;
}

void execute(unsigned int *cycles)
{
    while(*cycles > 0)
    {
        unsigned char data = fetch(cycles);
        printf("LDA: %d\n", LDA);
        printf("data: %d\n", data);
        switch(data)
        {
            case LDA: {
                unsigned char value = fetch(cycles);
                vm.accumulator = value;
                printf("LDA: %d\n", vm.accumulator);
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