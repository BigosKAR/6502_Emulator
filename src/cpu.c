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
    vm.cycles = 6;
    vm.accumulator = 45;
    vm.x = 2;
    vm.y = 0;
    set_flag(FLAG_CARRY);
    memory.data[0xFFFC] = CLC;
    memory.data[0xFFFD] = SED;
    memory.data[0xFFFE] = SEI;
    execute();
    return 0;
}