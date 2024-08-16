#ifndef LOAD_INSTRUCTIONS_H
#define LOAD_INSTRUCTIONS_H

void ld_imm(InstructionParams params, unsigned char *vm_register);
void ld_instruction(InstructionParams params, unsigned char* vm_register, unsigned char* index_register);
void ld_logic(unsigned char* vm_register, unsigned char value);

void st_instruction(InstructionParams params, unsigned char vm_register, unsigned char* index_register);
void st_logic(unsigned char register_value, unsigned short address);

#endif