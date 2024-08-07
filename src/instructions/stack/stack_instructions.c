#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"
#include "stack_instructions.h"

// Main stack instructions
void push_stack_instruction(InstructionParams params, unsigned char* vm_register)
{
    onebyte_ins_fix();
    cycle_check(params.required_cycles+1); // +1 cycle adjustment for onebyte instructions
    unsigned short stack_add = 0x01 << 8 | vm.sp;
    vm.sp--;
    wrap_stack_pointer(); // Wraps the stack pointer if it goes out of bounds
    vm.cycles -= 1; // Cycle for decremeting the stack pointer
    memory.data[stack_add] = *vm_register;
    vm.cycles -= 1; // Cycle for writing to the stack
    debug(params.instruction, memory.data[stack_add]);
}
void pull_stack_instruction(InstructionParams params, unsigned char* vm_register)
{
    onebyte_ins_fix();
    cycle_check(params.required_cycles+1);
    unsigned short stack_add = 0x01 << 8 | vm.sp;
    vm.sp++;
    vm.cycles -= 1; 
    *vm_register = memory.data[stack_add];
    vm.cycles -=2 ; // Read value from stack and write the value to the register (takes 2 cycles)
    wrap_stack_pointer();
    if(params.instruction == PLA)updateNZFlags(*vm_register);
    debug(params.instruction, *vm_register);
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