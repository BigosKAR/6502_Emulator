#ifndef STACK_INSTRUCTIONS_H
#define STACK_INSTRUCTIONS_H

void push_stack_logic(unsigned char* vm_register, unsigned char instruction);
void pull_stack_logic(unsigned char* vm_register, unsigned char instruction, bool isPLA);

void wrap_stack_pointer();

#endif