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
}

struct VirtualMachine vm;
struct Memory memory;

int main()
{
    unsigned int cycles = 6;
    unsigned int *ptr = &cycles;
    reset();
    vm.accumulator = 0b10000111; // 87
    vm.x = 0x68;
    vm.y = 0xFF;
    memory.data[0xFFFC] = ADC_ZP_Y_IND;
    memory.data[0xFFFD] = 0xF0; 
    memory.data[0x00F0] = 0x12;
    memory.data[0x00F1] = 0x54;
    memory.data[0x5511] = 0b01100101; //65
    set_flag(FLAG_DECIMAL);
    //printf("Memory[0x0033]: %d (%x in hexa)\n", memory.data[0x0033], memory.data[0x0033]);
    printf("Accumulator: %d\n", vm.accumulator);
    execute(ptr);
    printf("Accumulator: %d\n", vm.accumulator);
    //printf("Memory[0x0033]: %d (%x in hexa)\n", memory.data[0x0033], memory.data[0x0033]);
    return 0;
}