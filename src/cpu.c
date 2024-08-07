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
    vm.sp = 0xFF; // Stack is in addresses: 0x0100 to 0x01FF

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
    vm.accumulator = 234; // 87
    vm.x = 3;
    vm.y = 2;
    memory.data[0xFFFC] = ROL_A;
    memory.data[0xFFFD] = 234;
    memory.data[0xFFFE] = 0x12;
    memory.data[0x12FE] = 129;
    //printf("Memory[0x0033]: %d (%x in hexa)\n", memory.data[0x0033], memory.data[0x0033]);
    execute();
    printf("Memory[0x12FE]: %d (%x in hexa)\n", memory.data[0x12FE], memory.data[0x12FE]);
    //printf("Memory[0x0033]: %d (%x in hexa)\n", memory.data[0x0033], memory.data[0x0033]);
    return 0;
}