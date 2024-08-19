#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "instructions.h"
#include "flags.h"


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
    vm.sp = 0xFD; // Stack is in addresses: 0x0100 to 0x01FF

    vm.processor_status = 0x20;
    vm.accumulator = vm.x = vm.y = 0;
    vm.cycles = 0;
}

struct VirtualMachine vm;
struct Memory memory;

int main()
{
    reset();
    // Users have to set the amount of cycles depening on the instruction
    vm.cycles = 23;

    // Manually loading instructions and operands into memory (Sample program)

    memory.data[0xFFFC] = INX;
    memory.data[0xFFFD] = JSR;
    memory.data[0xFFFE] = 0x12;
    memory.data[0xFFFF] = 0x34;
    memory.data[0x3412] = TXA;
    memory.data[0x3413] = RTS;
    memory.data[0x0000] = BRK;

    // Execute the instructions
    execute();

    return 0;
}