#ifndef BRANCH_INSTRUCTIONS_H
#define BRANCH_INSTRUCTIONS_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../addressing_modes.h"

void flag_branch_instruction(InstructionParams params, bool condition); //condition when branch is taken

#endif