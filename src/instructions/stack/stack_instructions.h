#ifndef STACK_INSTRUCTIONS_H
#define STACK_INSTRUCTIONS_H

void push_stack_instruction(InstructionParams params, unsigned char* vm_register);
void pull_stack_instruction(InstructionParams params, unsigned char* vm_register);

void wrap_stack_pointer();

#endif