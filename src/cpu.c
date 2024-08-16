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
    vm.cycles = 26;
    vm.accumulator = 45;
    vm.x = 2;
    vm.y = 0;
    memory.data[0xFFFC] = INY;
    memory.data[0xFFFD] = JSR;
    memory.data[0xFFFE] = 0x13;
    memory.data[0xFFFF] = 0x37;
    memory.data[0x3713] = INX;
    memory.data[0x3714] = INX;
    memory.data[0x3715] = INX;
    memory.data[0x3716] = TXA;
    memory.data[0x3717] = TAY;
    memory.data[0x3718] = RTI;
    memory.data[0x0000] = INY;
    execute();
    return 0;
}