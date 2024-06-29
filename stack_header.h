#ifndef VM_H
#define VM_H

#include <stdio.h>

#define STACK_MAX 256

// Virtual Machine structure
struct {
    unsigned char *ip; // Instruction pointer
    unsigned long long register_A; // General purpose register
    unsigned long long stack[STACK_MAX]; // Stack
    unsigned long long *sp; // Stack pointer
} vm;

// Opcode enumeration
typedef enum {
    OP_PUSHI, // Push immediate value to stack
    OP_ADD, // Add two top values from stack
    OP_SUB, // Subtract two top values from stack
    OP_DIV, // Divide two top values from stack
    OP_MUL, // Multiply two top values from stack
    OP_POP_RES, // Pop the result from stack to register
    OP_DONE // Terminate program
} opcode;

// Result enumeration
typedef enum result {
    SUCCESS,
    ERROR_OPCODE_NOT_FOUND,
    ERROR_DIVISION_BY_ZERO,
} result;

// Function prototypes
void reset(void);
void stack_push(unsigned long long value);
unsigned long long stack_pop(void);
result vm_interpret(unsigned char *bytecode);

#endif // VM_H