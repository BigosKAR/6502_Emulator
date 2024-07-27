#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"

void trans_logic(unsigned char* vmr_destination, unsigned char vmr_source, unsigned char instruction, bool isTXS)
{
    onebyte_ins_fix();
    cycle_check(2+1);
    *vmr_destination = vmr_source;
    vm.cycles -= 1;
    if(!isTXS)updateNZFlags(*vmr_destination);
    debug(instruction, *vmr_destination);
}