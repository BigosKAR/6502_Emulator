#include <stdio.h>
#define STACK_MAX 256


struct {
    unsigned char *ip; // Pointer pointing to the instructions
    unsigned long long register_A; // Register for storing values
    unsigned long long stack[STACK_MAX];
    unsigned long long *sp; // stack top pointer
}vm;

typedef enum{
    OP_PUSHI, // push immediate value to stack
    OP_ADD, // add two top values from stack
    OP_SUB, // subtract two top values from stack
    OP_DIV, // divide two top values from stack
    OP_MUL, // multiply two top values from stack
    OP_POP_RES, // pop the result from stack

    //REGISTER OPERATIONS
    //OP_INC, // increase register value by 1
    //OP_DEC, // decrease register value by 1
    //OP_ADDI, // add immediate value to register
    //OP_SUBI, // subtract immediate value from register
    
    OP_DONE // terminate program
}opcode;

typedef enum result{
    SUCCESS, // will have value 0
    ERROR_OPCODE_NOT_FOUND, // will have value 1
    ERROR_DIVISION_BY_ZERO, // will have value 2
}result;

void reset(void)
{
    puts("Resetting the VM");
    vm = (typeof(vm)) {NULL};
    vm.sp= vm.stack;

}

void stack_push(unsigned long long value)
{
    *vm.sp = value;
    vm.sp++;
}

unsigned long long stack_pop(void)
{
    vm.sp--;
    return *vm.sp;
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
            case OP_PUSHI: {
                // push immediate value to stack
                unsigned char arg = *vm.ip++;
                stack_push(arg);
                break;
            }
            case OP_ADD: {
                // pop two values from stack, add, then push the result
                unsigned long long a = stack_pop();
                unsigned long long b = stack_pop();
                unsigned long long c = a + b;
                stack_push(c);
                break;
            }
            case OP_SUB: {
                // pop two values from stack, subtract, then push the result
                unsigned long long a = stack_pop();
                unsigned long long b = stack_pop();
                unsigned long long c = a - b;
                stack_push(c);
                break;
            }
            case OP_DIV: {
                //pop two values from stack, divide, and then push the result
                unsigned long long a = stack_pop();
                if (a == 0)
                {
                    return ERROR_DIVISION_BY_ZERO;
                }
                unsigned long long b = stack_pop();
                unsigned long long c = b/a;
                stack_push(c);
                break;
            }
            case OP_MUL: {
                // pop two values from stack, multiply, then push the result
                unsigned long long a = stack_pop();
                unsigned long long b = stack_pop();
                unsigned long long c = a * b;
                stack_push(c);
                break;
            }
            case OP_POP_RES: {
                // pop result from stack, move it to register A
                unsigned long long result = stack_pop();
                vm.register_A = result;
                break;
            }
            /*case OP_INC:{
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
            */
            case OP_DONE: {
                return SUCCESS;
            }
            default:
                return ERROR_OPCODE_NOT_FOUND;
        }
    }
    return SUCCESS;
}