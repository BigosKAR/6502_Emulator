#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"

void transfer_instruction(InstructionParams params, unsigned char* vmr_destination, unsigned char vmr_source)
{
    cycle_check(params.required_cycles);
    *vmr_destination = vmr_source;
    vm.cycles -= 1;
    if(!(params.instruction == TXS))updateNZFlags(*vmr_destination);
    if(VERBOSE)debug(params.instruction, *vmr_destination);
}