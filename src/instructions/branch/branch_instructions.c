#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"
#include "branch_instructions.h"
#include "../../addressing_modes.h"

void flag_branch_instruction(InstructionParams params, bool condition){
    cycle_check(params.required_cycles);
    if(condition)
    {
        printf("BRANCH TAKEN\n");
        unsigned short relative_address = get_relative_address();
        vm.ip = relative_address;
        vm.cycles -= 1;
        cycle_check(1); // Check if there is non negative cycle amount
    }
    else
    {
        printf("BRANCH NOT TAKEN\n");
        vm.ip++;
        vm.cycles -= 1; // not running the get_relative_address function
    }
    debug(params.instruction, vm.processor_status);
}