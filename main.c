#include <stdio.h>

struct {
    unsigned char *ip; // Pointer pointing to the instructions
    unsigned long long register_A; // Register for storing values
}vm;

typedef enum{
    OP_INC, // increase register value by 1
    OP_DEC, // decrease register value by 1
    OP_ADDI, // add immediate value to register
    OP_SUBI, // subtract immediate value from register
    OP_DONE // terminate program
}opcode;

typedef enum result{
    SUCCESS,
    ERROR,
}result;

void reset(void)
{
    puts("Resetting the VM");
    vm = (typeof(vm)) {NULL};
}

result vm_interpret(unsigned char *bytecode){
    reset();
    puts("Interpreting the bytecode");
    vm.ip = bytecode;
    for(;;)
    {
        unsigned char instruction = *vm.ip++;
        switch(instruction)
        {
            case OP_INC:{
                vm.register_A++;
                break;
            }
            case OP_DEC: {
                vm.register_A--;
                break;
            }
            case OP_ADDI: {
            // get the argument
            unsigned char arg = *vm.ip++;
            vm.register_A += arg;
            break;
            }
            case OP_SUBI: {
            // get the argument
            unsigned char arg = *vm.ip++;
            vm.register_A -= arg;
            break;
            }
            case OP_DONE: {
                return SUCCESS;
            }
            default:
                return ERROR;
        }
    }
    return SUCCESS;
}