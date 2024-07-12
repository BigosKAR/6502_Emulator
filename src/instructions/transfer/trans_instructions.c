#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"

void trans_logic(unsigned int* cycles, unsigned char* vmr_destination, unsigned char vmr_source, unsigned char instruction, bool isTXS)
{
    onebyte_ins_fix(cycles);
    cycle_check(2-1, cycles);
    *vmr_destination = vmr_source;
    *cycles -= 1;
    if(!isTXS)updateNZFlags(*vmr_destination);
    debug(instruction, *vmr_destination);
}