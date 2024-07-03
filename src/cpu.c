#include <stdio.h>
#include "instructions.h"
#include "flags.h"
#include <string.h>

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
    vm.sp = &memory.data[0x01FF];

    vm.processor_status = 0x20;
    vm.accumulator = vm.x = vm.y = 0;  
}

struct VirtualMachine vm;
struct Memory memory;

int main()
{
    int cycles = 10;
    int *ptr = &cycles;
    reset();
    memory.data[0xFFFC] = 0xAD; // LDA absolute opcode
    memory.data[0xFFFD] = 0x34; // Low byte of the address
    memory.data[0xFFFE] = 0x12; // High byte of the address
    memory.data[0xFFFF] = LDA_IMM;
    memory.data[0x0000] = 0x53;
    memory.data[0x0001] = LDA_ABS;
    memory.data[0x0002] = 0x51;
    memory.data[0x0003] = 0x34;
    memory.data[0x3451] = 0x71;
    memory.data[0x1234] = 0x69; // Value to be loaded into the accumulator
    //memory.data[0xFFFF] = 0xA9;
    //memory.data[0xFFFD] = 0x81;
    execute(ptr);
    return 0;
}