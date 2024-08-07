#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"

void transfer_instruction(InstructionParams params, unsigned char* vmr_destination, unsigned char vmr_source)
{
    onebyte_ins_fix();
    cycle_check(params.required_cycles+1);
    *vmr_destination = vmr_source;
    vm.cycles -= 1;
    if(!(params.instruction == TXS))updateNZFlags(*vmr_destination);
    debug(params.instruction, *vmr_destination);
}