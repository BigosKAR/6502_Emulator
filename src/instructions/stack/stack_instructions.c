#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"
#include "stack_instructions.h"

// Main stack instructions
void push_stack_logic(unsigned int* cycles, unsigned char* vm_register, unsigned char instruction)
{
    onebyte_ins_fix(cycles);
    cycle_check(3-1, cycles);
    unsigned short stack_add = 0x01 << 8 | vm.sp;
    vm.sp--;
    wrap_stack_pointer(); // Wraps the stack pointer if it goes out of bounds
    *cycles -= 1; // Cycle for decremeting the stack pointer
    memory.data[stack_add] = *vm_register;
    *cycles -= 1; // Cycle for writing to the stack
    debug(instruction, memory.data[stack_add]);
}
void pull_stack_logic(unsigned int* cycles, unsigned char* vm_register, unsigned char instruction, bool isPLA)
{
    onebyte_ins_fix(cycles);
    cycle_check(4-1, cycles);
    vm.sp++;
    *cycles -= 1; 
    unsigned short stack_add = 0x01 << 8 | vm.sp;
    *vm_register = memory.data[stack_add];
    *cycles -= 2; // Read value from stack and write the value to the register (takes 2 cycles)
    wrap_stack_pointer();
    if(isPLA)updateNZFlags(*vm_register);
    debug(instruction, *vm_register);
}

// Helper stack functions
void wrap_stack_pointer()
{
    if(vm.sp < 0x00)
    {
        vm.sp = 0xFF;
        printf("Wrapped around the stack pointer\n");
    }
    else if(vm.sp > 0xFF)
    {
        vm.sp = 0x00;
    }
}