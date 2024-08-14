#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"
#include "inc_instructions.h"
#include "../../addressing_modes.h"

void inc_instruction(InstructionParams params, IncParams inc_params, unsigned char* vm_register){
    printf("Source Type: %d\n", inc_params.source_type);
    printf("Operation Type: %d\n", inc_params.operation_type);
    cycle_check(params.required_cycles);
    unsigned char result;
    switch(inc_params.source_type){
        case MEMORY: {
            unsigned short address = fetch_address(params, vm_register);
            if(inc_params.operation_type == DECREMENT)memory.data[address]--;
            else memory.data[address]++;
            result = memory.data[address];
            vm.cycles -= 4;
            break;
        }
        case REGISTER_X: {
            if(inc_params.operation_type == DECREMENT)vm.x--;
            else vm.x++;
            result = vm.x;
            vm.cycles -= 1;
            break;
        }
        case REGISTER_Y: {
            if(inc_params.operation_type == DECREMENT)vm.y--;
            else vm.y++;
            result = vm.y;
            vm.cycles -= 1;
            break;
        }
        default: {
            exit(1);
            break;
        }
    }
    updateNZFlags(result);
    debug(params.instruction, result);
}