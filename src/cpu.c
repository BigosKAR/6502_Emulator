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
    int cycles = 6;
    int *ptr = &cycles;
    reset();
    vm.accumulator = 255;
    vm.x = 0x49;
    memory.data[0xFFFC] = ASL_ZP_X;
    memory.data[0xFFFD] = 0xFF;
    memory.data[0x0048] = 255;
    printf("Memory[0x0048]: %d (%x in hexa)\n", memory.data[0x0048], memory.data[0x0048]);
    execute(ptr);
    return 0;
}