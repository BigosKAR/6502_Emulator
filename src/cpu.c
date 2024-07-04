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
    //vm.sp = 0x01FF; Need to change it to fit the 8 bit pointer

    vm.processor_status = 0x20;
    vm.accumulator = vm.x = vm.y = 0;  
}

struct VirtualMachine vm;
struct Memory memory;

int main()
{
    int cycles = 3;
    int *ptr = &cycles;
    reset();
    memory.data[vm.ip] = 0xA5;
    memory.data[vm.ip+1] = 0x45; 
    memory.data[0x0045] = 0x59;
    execute(ptr);
    return 0;
}