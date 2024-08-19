#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../instructions.h"
#include "../../flags.h"
#include "ctrl_instructions.h"
#include "../../addressing_modes.h"

void brk_instruction(InstructionParams params)
{
    cycle_check(params.required_cycles);
    vm.ip++;
    unsigned char byte = fetch_byte();
    unsigned short stack_add = 0x01 << 8 | vm.sp;
    vm.sp--;
    memory.data[stack_add] = byte;
    stack_add = 0x01 | vm.sp;
    vm.sp--;
    memory.data[stack_add] = vm.processor_status;
    set_flag(FLAG_BREAK);
    unsigned short intterupt_address = (memory.data[0xFFFE] << 4) | memory.data[0xFFFF];
    vm.ip = intterupt_address;
    vm.cycles -= 5;
    if(VERBOSE)debug(params.instruction, vm.processor_status);
}

void jmp_instruction(InstructionParams params)
{
    printf("CYCLES: %d\n", vm.cycles);
    unsigned short new_ip_val = fetch_address(params, NULL);
    vm.ip = new_ip_val;
    if(VERBOSE)debug(params.instruction, memory.data[vm.ip]);
}

void jsr_instruction(InstructionParams params)
{
    unsigned short subroutine_address = fetch_address(params, NULL);
    unsigned short return_address = vm.ip;
    vm.ip = subroutine_address;

    unsigned char high_order_rAddress = (return_address & 0xFF00) >> 8; // Spliting the return address
    unsigned char low_order_rAddress = return_address & 0x00FF;

    unsigned short stack_add = 0x01 << 8 | vm.sp;
    vm.sp--;
    memory.data[stack_add] = high_order_rAddress;
    stack_add = 0x01 << 8 | vm.sp;
    vm.sp--;
    memory.data[stack_add] = low_order_rAddress;
    vm.cycles -= 3;
    if(VERBOSE)debug(params.instruction, memory.data[vm.ip]);
}

void rti_instruction(InstructionParams params)
{
    cycle_check(params.required_cycles);
    unsigned short stack_add = 0x01 << 8 | vm.sp;
    vm.processor_status = memory.data[stack_add];
    vm.sp++;
    stack_add = 0x01 << 8 | vm.sp;
    unsigned char low_order_rAddress = memory.data[stack_add];
    vm.sp++;
    stack_add = 0x01 << 8 | vm.sp;
    unsigned char high_order_rAddress = memory.data[stack_add];
    vm.sp++;
    vm.ip = (high_order_rAddress << 8) | low_order_rAddress;
    vm.cycles -= 5;
    if(VERBOSE)debug(params.instruction, vm.processor_status);
}

void rts_instruction(InstructionParams params)
{
    cycle_check(params.required_cycles);
    unsigned short stack_add = 0x01 << 8 | vm.sp;
    unsigned char low_order_IP = memory.data[stack_add];
    vm.sp++;
    stack_add = 0x01 << 8 | vm.sp;
    unsigned char high_order_IP = memory.data[stack_add];
    vm.sp++;
    vm.ip = (high_order_IP << 8) | low_order_IP;
    vm.cycles -= 5;
    if(VERBOSE)debug(params.instruction, vm.processor_status);
}