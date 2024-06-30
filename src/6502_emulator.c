#include <stdio.h>
#include "instructions.h"

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

    vm.ip = (unsigned short*)&memory.data[0xFFFC];
    vm.sp = &memory.data[0x01FF];

    vm.processor_status = 0x24;
    vm.accumulator = vm.x = vm.y = 0;   
}

int main()
{
    int cycles = 2;
    int *ptr = &cycles;
    reset();
    memory.data[0xFFFC] = 0xA9;
    printf("memory.data[0xFFFC]: %d\n", memory.data[0xFFFC]);
    memory.data[0xFFFD] = 0x05;
    execute(ptr);
    return 0;
}