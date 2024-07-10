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
    vm.sp = 0xFF; // Stack is in addresses: 0x0100 to 0x01FF

    vm.processor_status = 0x20;
    vm.accumulator = vm.x = vm.y = 0;  
}

struct VirtualMachine vm;
struct Memory memory;

int main()
{
    int cycles = 12;
    int *ptr = &cycles;
    reset();
    vm.accumulator = 247;
    vm.x = 255;
    vm.y = 255;
    memory.data[0xFFFC] = PHP;
    memory.data[0xFFFD] = LDA_IMM;
    memory.data[0xFFFE] = 0x00;
    memory.data[0xFFFF] = PLP;
    execute(ptr);
    return 0;
}