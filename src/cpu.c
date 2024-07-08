#include <stdio.h>
#include "instructions.h"
#include "flags.h"
#include <string.h>
#include <stdlib.h>

typedef enum result{
    SUCCESS, // will have value 0
    ERROR_OPCODE_NOT_FOUND, // will have value 1
    ERROR_DIVISION_BY_ZERO, // will have value 2
}result;

void initialize_memory(){
    for(int i = 0; i < MEM_MAX_SIZE; i++){
        memory.data[i] = 0;
    }
}

void reset(void)
{
    initialize_memory();

    vm.ip = 0xFFFC;
    //vm.sp = 0x01FF; Need to change it to fit the 8 bit pointer

    vm.processor_status = 0x20;
    vm.accumulator = vm.x = vm.y = 0;  
}

struct VirtualMachine vm;
struct Memory memory;

int main()
{
    int cycles = 8;
    int *ptr = &cycles;
    reset();
    vm.y = 1;
    memory.data[vm.ip] = 0xB1;
    memory.data[vm.ip+1] = 0xFF;
    memory.data[vm.ip+2] = 0xA9;
    memory.data[vm.ip+3] = 0xAD;
    memory.data[0x00FF] =  0xFF;
    memory.data[0x0000] = 0xAB;
    memory.data[0xAC00] = 0x47;
    execute(ptr);
    return 0;
}