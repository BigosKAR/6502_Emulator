#ifndef LOGIC_INSTRUCTIONS_H
#define LOGIC_INSTRUCTIONS_H

typedef enum {
    LOGIC_AND,
    LOGIC_OR,
    LOGIC_XOR
} LogicType;

void logical_imm(InstructionParams params);
void logical_instruction(InstructionParams params, unsigned char* vm_register, LogicType logic_type);
void bit_instruction(InstructionParams params);

// Main logic functions
void and_bitwise_logic(unsigned char value);
void eor_bitwise_logic(unsigned char value);
void ora_bitwise_logic(unsigned char value);
unsigned char bit_logic(InstructionParams params, unsigned short address);

#endif