#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"

// Main logic functions
void and_imm(unsigned int* cycles, unsigned char low_byte, unsigned char instruction)
{
    cycle_check(2-2, cycles);
    and_bitwise_logic(low_byte);
    debug(instruction, vm.accumulator);
}
void and_abs(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned char high_order_address = fetch_byte(cycles);
    unsigned short address = (high_order_address << 8) | low_order_address;
    and_bitwise_logic(memory.data[address]);
    *cycles -= 1;
    debug(instruction, vm.accumulator);
}

// Helper logic functions
void and_bitwise_logic(unsigned char value)
{
    vm.accumulator &= value;
    updateNZFlags(vm.accumulator);
}