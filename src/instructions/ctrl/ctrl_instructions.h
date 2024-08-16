#ifndef CTRL_INSTRUCTIONS_H
#define CTRL_INSTRUCTIONS_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../addressing_modes.h"

void brk_instruction(InstructionParams params);
void jmp_instruction(InstructionParams params);
void jsr_instruction(InstructionParams params);
void rti_instruction(InstructionParams params);
void rts_instruction(InstructionParams params);

#endif