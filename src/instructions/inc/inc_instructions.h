#ifndef INC_INSTRUCTIONS_H
#define INC_INSTRUCTIONS_H

#include "../../addressing_modes.h"

typedef enum {
    MEMORY,
    REGISTER_X,
    REGISTER_Y
}SourceType;

typedef enum{
    INCREMENT,
    DECREMENT
}IncOperationType;

typedef struct IncParams{
    SourceType source_type;
    IncOperationType operation_type;
}IncParams;

void inc_instruction(InstructionParams params, IncParams inc_params, unsigned char* vm_register);

#endif