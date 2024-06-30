#include <stdio.h>
#define REGISTER_NUM 16


struct {
    unsigned short *ip; // Pointer pointing to the instructions
    unsigned long long reg[REGISTER_NUM]; // Registers for storing values
    unsigned long long result_register; // Register for storing the result
}vm;

typedef enum{
    // Math operations will work with values stored in r0 and r1, and then the result will be stored in r2
    OP_LOADI, // load immediate value to register
    OP_ADD, 
    OP_SUB, 
    OP_DIV, 
    OP_MUL, 
    OP_MOV_RES, // move result from r0 to r2
    OP_DONE // terminate program
}opcode;

typedef enum result{
    SUCCESS, // will have value 0
    ERROR_OPCODE_NOT_FOUND, // will have value 1
    ERROR_DIVISION_BY_ZERO, // will have value 2
}result;

void reset(void)
{
    //puts("Resetting the VM");
    vm = (typeof(vm)) {NULL};
}

void decode(unsigned short instruction, unsigned char *op, unsigned char *reg0, unsigned char *reg1, unsigned char *reg2, unsigned char *imm)
{
    // breaking down the instruction into opcode, registers and immediate value
    *op = (instruction & 0xF000) >> 12;
    *reg0 = (instruction & 0x0F00) >> 8;
    *reg1 = (instruction & 0x00F0) >> 4;
    *reg2 = (instruction & 0x000F);
    *imm = (instruction & 0x00FF);
}

result vm_interpret(unsigned short *bytecode){
    reset();
    puts("Interpreting the bytecode");
    vm.ip = bytecode;

    unsigned char op, r0, r1, r2, immediate;

    for(;;)
    {
        unsigned short instruction = *vm.ip++;
        decode(instruction, &op, &r0, &r1, &r2, &immediate);
        switch(op)
        {
            case OP_LOADI: {
                // load immediate value to register
                vm.reg[r0] = immediate;
                break;
            }
            case OP_ADD: {
                // add two values from registers, store the result in another register
                vm.reg[r2] = vm.reg[r0] + vm.reg[r1];
                break;
            }
            case OP_SUB: {
                vm.reg[r2] = vm.reg[r0] - vm.reg[r1];
                break;
            }
            case OP_DIV: {
                if(vm.reg[r1] == 0)
                    return ERROR_DIVISION_BY_ZERO;
                vm.reg[r2] = vm.reg[r0] / vm.reg[r1];
                break;
            }
            case OP_MUL: {
                vm.reg[r2] = vm.reg[r0] * vm.reg[r1];
                break;
            }
            case OP_MOV_RES: {
                vm.result_register = vm.reg[r0];
                break;
            }
            case OP_DONE: {
                return SUCCESS;
            }
            default:
                return ERROR_OPCODE_NOT_FOUND;
        }
    }
    return SUCCESS;
}