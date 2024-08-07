#ifndef SHIFT_INSTRUCTIONS_H
#define SHIFT_INSTRUCTIONS_H

typedef enum {
    SHIFT_ASL,
    SHIFT_LSR,
    SHIFT_ROL,
    SHIFT_ROR
} ShiftType;

void shift_accumulator(InstructionParams params, ShiftType shift_type);
void shift_instruction(InstructionParams params, unsigned char* vm_register, ShiftType shift_type);
void rotate_accumulator(InstructionParams params, ShiftType shift_type);
void rotate_instruction(InstructionParams params, unsigned char* vm_register, ShiftType shift_type);

void rotate_logic(unsigned char* value, ShiftType shift_type);
void shift_logic(unsigned short address, unsigned char temp_var, ShiftType shift_type);

#endif