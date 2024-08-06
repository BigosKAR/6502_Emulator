#ifndef ARITH_INSTRUCTIONS_H
#define ARITH_INSTRUCTIONS_H

#include "../../addressing_modes.h"

void adc_imm(InstructionParams params);
void adc_instruction(InstructionParams params, unsigned char *vm_register);
void sbc_imm(InstructionParams params);
void cm_imm(InstructionParams params, unsigned char vm_register);
void cm_instruction(InstructionParams params, unsigned char vm_register, unsigned char *index_register);
void compare_logic(unsigned char vm_register, unsigned char memory_value);
void adc_logic(unsigned char char_value);

#endif