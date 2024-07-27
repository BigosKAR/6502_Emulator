#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "flags.h"
#include "instructions.h"
#include "./instructions/load/load_instructions.h"
#include "./instructions/transfer/trans_instructions.h"
#include "./instructions/stack/stack_instructions.h"
#include "./instructions/shift/shift_instructions.h"
#include "./instructions/logic/logic_instructions.h"
#include "./instructions/arithmetic/arith_instructions.h"

// execution of instructions *most important function*
void execute()
{
    unsigned char high_byte_data;
    unsigned char low_byte_data;
    while(vm.cycles > 0)
    {
        if(vm.cycles <= 0) {
            printf("Breaking loop, CYCLES: %d\n", vm.cycles);
            break;
        }
        fetch_word(&low_byte_data, &high_byte_data); // takes 2 cycles away
        switch(high_byte_data)
        {
            case LDA_IMM: {
                InstructionParams params = {2, low_byte_data, LDA_IMM, IMMEDIATE};
                ld_imm(params, &vm.accumulator);
                break;
            }
            case LDA_ABS: {
                InstructionParams params = {4, low_byte_data, LDA_ABS, ABSOLUTE};
                ld_instruction(params, &vm.accumulator, NULL);
                break;
            }
            case LDA_ABS_X: {
                InstructionParams params = {4, low_byte_data, LDA_ABS_X, ABSOLUTE_INDEXED_PC};
                ld_instruction(params, &vm.accumulator, &vm.x);
                break;
            }
            case LDA_ABS_Y: {
                InstructionParams params = {4, low_byte_data, LDA_ABS_Y, ABSOLUTE_INDEXED_PC};
                ld_instruction(params, &vm.accumulator, &vm.y);
                break;
            }
            case LDA_ZP: {
                InstructionParams params = {3, low_byte_data, LDA_ZP, ZERO_PAGE};
                ld_instruction(params, &vm.accumulator, NULL);
                break;
            }
            case LDA_ZP_X: {
                InstructionParams params = {4, low_byte_data, LDA_ZP_X, ZERO_PAGE_INDEXED};
                ld_instruction(params, &vm.accumulator, &vm.x);
                break;
            }
            case LDA_ZP_X_IND: {   
                InstructionParams params = {6, low_byte_data, LDA_ZP_X_IND, ZERO_PAGE_X_INDIRECT};
                ld_instruction(params, &vm.accumulator, &vm.x);
                break;
            }
            case LDA_ZP_Y_IND: {
                InstructionParams params = {5, low_byte_data, LDA_ZP_Y_IND, ZERO_PAGE_Y_INDIRECT_PC};
                ld_instruction(params, &vm.accumulator, &vm.y);
                break;
            }
            case LDX_IMM: {
                InstructionParams params = {2, low_byte_data, LDX_IMM, IMMEDIATE};
                ld_imm(params, &vm.x);
                break;
            }
            case LDX_ABS: {
                InstructionParams params = {4, low_byte_data, LDX_ABS, ABSOLUTE};
                ld_instruction(params, &vm.x, NULL);
                break;
            }
            case LDX_ABS_Y: {
                InstructionParams params = {4, low_byte_data, LDX_ABS_Y, ABSOLUTE_INDEXED_PC};
                ld_instruction(params, &vm.x, &vm.y);
                break;
            }
            case LDX_ZP: {
                InstructionParams params = {3, low_byte_data, LDX_ZP, ZERO_PAGE};
                ld_instruction(params, &vm.x, NULL);
                break;
            }
            case LDX_ZP_Y: {
                InstructionParams params = {4, low_byte_data, LDX_ZP_Y, ZERO_PAGE_INDEXED};
                ld_instruction(params, &vm.x, &vm.y);
                break;
            }
            case LDY_IMM: {
                InstructionParams params = {2, low_byte_data, LDY_IMM, IMMEDIATE};
                ld_imm(params, &vm.y);
                break;
            }
            case LDY_ABS: {
                InstructionParams params = {4, low_byte_data, LDY_ABS, ABSOLUTE};
                ld_instruction(params, &vm.y, NULL);
                break;
            }
            case LDY_ZP: {
                InstructionParams params = {3, low_byte_data, LDY_ZP, ZERO_PAGE};
                ld_instruction(params, &vm.y, NULL);
                break;
            }
            case LDY_ABS_X: {
                InstructionParams params = {4, low_byte_data, LDY_ABS_X, ABSOLUTE_INDEXED_PC};
                ld_instruction(params, &vm.y, &vm.x);
                break;
            }
            case LDY_ZP_X: {
                InstructionParams params = {4, low_byte_data, LDY_ZP_X, ZERO_PAGE_INDEXED};
                ld_instruction(params, &vm.y, &vm.x);
                break;
            }
            case STA_ABS: {
                InstructionParams params = {4, low_byte_data, STA_ABS, ABSOLUTE};
                st_instruction(params, vm.accumulator, NULL);
                break;
            }
            case STA_ZP: {
                InstructionParams params = {3, low_byte_data, STA_ZP, ZERO_PAGE};
                st_instruction(params, vm.accumulator, NULL);
                break;
            }
            case STA_ZP_X:{
                InstructionParams params = {4, low_byte_data, STA_ZP_X, ZERO_PAGE_INDEXED};
                st_instruction(params, vm.accumulator, &vm.x); 
                break;
            }
            case STA_ABS_X: {
                InstructionParams params = {5, low_byte_data, STA_ABS_X, ABSOLUTE_INDEXED};
                st_instruction(params, vm.accumulator, &vm.x);
                break;
            }
            case STA_ABS_Y: {
                InstructionParams params = {5, low_byte_data, STA_ABS_Y, ABSOLUTE_INDEXED};
                st_instruction(params, vm.accumulator, &vm.y);
                break;
            }
            case STA_ZP_X_IND: {
                InstructionParams params = {6, low_byte_data, STA_ZP_X_IND, ZERO_PAGE_X_INDIRECT};
                st_instruction(params, vm.accumulator, &vm.x);
                break;
            }
            case STA_ZP_Y_IND: {
                InstructionParams params = {6, low_byte_data, STA_ZP_Y_IND, ZERO_PAGE_Y_INDIRECT};
                st_instruction(params, vm.accumulator, &vm.y);
                break;
            }
            case STX_ABS: {
                InstructionParams params = {4, low_byte_data, STX_ABS, ABSOLUTE};
                st_instruction(params, vm.x, NULL);
                break;
            }
            case STX_ZP:{
                InstructionParams params = {3, low_byte_data, STX_ZP, ZERO_PAGE};
                st_instruction(params, vm.x, NULL);
                break;
            }
            case STX_ZP_Y: {
                InstructionParams params = {4, low_byte_data, STX_ZP_Y, ZERO_PAGE_INDEXED};
                st_instruction(params, vm.x, &vm.y);
                break;
            }
            case STY_ABS: {
                InstructionParams params = {4, low_byte_data, STY_ABS, ABSOLUTE};
                st_instruction(params, vm.y, NULL);
                break;
            }
            case STY_ZP: {
                InstructionParams params = {3, low_byte_data, STY_ZP, ZERO_PAGE};
                st_instruction(params, vm.y, NULL);
                break;
            }
            case STY_ZP_X: {
                InstructionParams params = {4, low_byte_data, STY_ZP_X, ZERO_PAGE_INDEXED};
                st_instruction(params, vm.y, &vm.x);
                break;
            }
            case TAX: {
                trans_logic(&vm.x, vm.accumulator, TAX, false);
                break;
            }
            case TAY: {
                trans_logic(&vm.y, vm.accumulator, TAY, false);
                break;
            }
            case TSX: {
                unsigned short temp_add = 0x01 << 8 | vm.sp;
                trans_logic(&vm.x, memory.data[temp_add], TSX, false);
                break;
            }
            case TXA: {
                trans_logic(&vm.accumulator, vm.x, TXA, false);
                break;
            }
            case TXS: {
                unsigned short temp_add = 0x01 << 8 | vm.sp;
                trans_logic(&memory.data[temp_add], vm.x, TXS, true);
                break;
            }
            case TYA: {
                trans_logic(&vm.accumulator, vm.y, TYA, false);
                break;
            }
            case PHA: {
                push_stack_logic(&vm.accumulator, PHA);
                break;
            }
            case PHP: {
                push_stack_logic(&vm.processor_status, PHP);
                break;
            }
            case PLA: {
                pull_stack_logic(&vm.accumulator, PLA, true);
                break;
            }
            case PLP: {
                pull_stack_logic(&vm.processor_status, PLP, false);
                break;
            }
            case ASL_A: {
                shift_acc_logic(ASL_A);
                break;
            }
            case ASL_ABS: {
                shift_abs_logic(low_byte_data, ASL_ABS);
                break;
            }
            case ASL_ABS_X: {
                shift_abs_x_logic(low_byte_data, ASL_ABS_X);
                break;
            }
            case ASL_ZP: {
                shift_zp_logic(low_byte_data, ASL_ZP);
                break;
            }
            case ASL_ZP_X: {
                shift_zp_x_logic(low_byte_data, ASL_ZP_X);
                break;
            }
            case LSR_A: {
                shift_acc_logic(LSR_A);
                break;
            }
            case LSR_ABS: {
                shift_abs_logic(low_byte_data, LSR_ABS);
                break;
            }
            case LSR_ABS_X: {
                shift_abs_x_logic(low_byte_data, LSR_ABS_X);
                break;
            }
            case LSR_ZP: {
                shift_zp_logic(low_byte_data, LSR_ZP);
                break;
            }
            case LSR_ZP_X: {
                shift_zp_x_logic(low_byte_data, LSR_ZP_X);
                break;
            }
            case ROL_A: {
                rotate_acc_logic(ROL_A);
                break;
            }
            case ROL_ABS: {
                rotate_abs_logic(low_byte_data, ROL_ABS);
                break;
            }
            case ROL_ABS_X: {
                rotate_abs_x_logic(low_byte_data, ROL_ABS_X);
                break;
            }
            case ROL_ZP:{
                rotate_zp_logic(low_byte_data, ROL_ZP);
                break;
            }
            case ROL_ZP_X: {
                rotate_zp_x_logic(low_byte_data, ROL_ZP_X);
                break;
            }
            case ROR_A: {
                rotate_acc_logic(ROR_A);
                break;
            }
            case ROR_ABS:
            {
                rotate_abs_logic(low_byte_data, ROR_ABS);
                break;
            }
            case ROR_ABS_X: {
                rotate_abs_x_logic(low_byte_data, ROR_ABS_X);
                break;
            }
            case ROR_ZP: {
                rotate_zp_logic(low_byte_data, ROR_ZP);
                break;
            }
            case ROR_ZP_X: {
                rotate_zp_x_logic(low_byte_data, ROR_ZP_X);
                break;
            }
            case AND_IMM: {
                logical_imm(low_byte_data, AND_IMM);
                break;
            }
            case AND_ABS: {
                logical_abs(low_byte_data, AND_ABS);
                break;
            }
            case AND_ABS_X: {
                logical_abs_reg_logic(low_byte_data, vm.x, AND_ABS_X);
                break;
            }
            case AND_ABS_Y: {
                logical_abs_reg_logic(low_byte_data, vm.y, AND_ABS_Y);
                break;
            }
            case AND_ZP: {
                logical_zp(low_byte_data, AND_ZP);
                break;
            }
            case AND_ZP_X: {
                logical_zp_x(low_byte_data, AND_ZP_X);
                break;
            }
            case AND_ZP_X_IND: {
                logical_zp_x_ind(low_byte_data, AND_ZP_X_IND);
                break;
            }
            case AND_ZP_Y_IND: {
                logical_zp_y_ind(low_byte_data, AND_ZP_Y_IND);
                break;
            }
            case BIT_ABS:{
                bit_abs(low_byte_data, BIT_ABS);
                break;
            }
            case BIT_ZP:{
                bit_zp(low_byte_data, BIT_ZP);
                break;
            }
            case EOR_IMM: {
                logical_imm(low_byte_data, EOR_IMM);
                break;
            }
            case EOR_ABS: {
                logical_abs(low_byte_data, EOR_ABS);
                break;
            }
            case EOR_ABS_X: {
                logical_abs_reg_logic(low_byte_data, vm.x, EOR_ABS_X);
                break;
            }
            case EOR_ABS_Y: {
                logical_abs_reg_logic(low_byte_data, vm.y, EOR_ABS_Y);
                break;
            }
            case EOR_ZP: {
                logical_zp(low_byte_data, EOR_ZP);
                break;
            }
            case EOR_ZP_X: {
                logical_zp_x(low_byte_data, EOR_ZP_X);
                break;
            }
            case EOR_ZP_X_IND: {
                logical_zp_x_ind(low_byte_data, EOR_ZP_X_IND);
                break;
            }
            case EOR_ZP_Y_IND: {
                logical_zp_y_ind(low_byte_data, EOR_ZP_Y_IND);
                break;
            }
            case ORA_IMM: {
                logical_imm(low_byte_data, ORA_IMM);
                break;
            }
            case ORA_ABS: {
                logical_abs(low_byte_data, ORA_ABS);
                break;
            }
            case ORA_ABS_X: {
                logical_abs_reg_logic(low_byte_data, vm.x, ORA_ABS_X);
                break;
            }
            case ORA_ABS_Y: {
                logical_abs_reg_logic(low_byte_data, vm.y, ORA_ABS_Y);
                break;
            }
            case ORA_ZP: {
                logical_zp(low_byte_data, ORA_ZP);
                break;
            }
            case ORA_ZP_X: {
                logical_zp_x(low_byte_data, ORA_ZP_X);
                break;
            }
            case ORA_ZP_X_IND: {
                logical_zp_x_ind(low_byte_data, ORA_ZP_X_IND);
                break;
            }
            case ORA_ZP_Y_IND: {
                logical_zp_y_ind(low_byte_data, ORA_ZP_Y_IND);
                break;
            }
            case ADC_IMM: {
                InstructionParams params = {2, low_byte_data, ADC_IMM, IMMEDIATE};
                adc_imm(params);
                break;
            }
            case ADC_ABS: {
                InstructionParams params = {4, low_byte_data, ADC_ABS, ABSOLUTE};
                adc_instruction(params, NULL);
                break;
            }
            case ADC_ABS_X: {
                InstructionParams params = {4, low_byte_data, ADC_ABS_X, ABSOLUTE_INDEXED_PC};
                adc_instruction(params, &vm.x);
                break;
            }
            case ADC_ABS_Y: {
                InstructionParams params = {4, low_byte_data, ADC_ABS_Y, ABSOLUTE_INDEXED_PC};
                adc_instruction(params, &vm.y);
                break;
            }
            case ADC_ZP: {
                InstructionParams params = {3, low_byte_data, ADC_ZP, ZERO_PAGE};
                adc_instruction(params, NULL);
                break;
            }
            case ADC_ZP_X: {
                InstructionParams params = {4, low_byte_data, ADC_ZP_X, ZERO_PAGE_INDEXED};
                adc_instruction(params, &vm.x);
                break;
            }
            case ADC_ZP_X_IND: {
                InstructionParams params = {6, low_byte_data, ADC_ZP_X_IND, ZERO_PAGE_X_INDIRECT};
                adc_instruction(params, &vm.x);
                break;
            }
            case ADC_ZP_Y_IND: {
                InstructionParams params = {5, low_byte_data, ADC_ZP_Y_IND, ZERO_PAGE_Y_INDIRECT_PC};
                adc_instruction(params, &vm.y);
                break;
            }
            case CMP_IMM: {
                InstructionParams params = {2, low_byte_data, CMP_IMM, IMMEDIATE};
                cm_imm(params, vm.accumulator);
                break;
            }
            case CMP_ABS: {
                InstructionParams params = {4, low_byte_data, CMP_ABS, ABSOLUTE};
                cm_instruction(params, vm.accumulator, NULL);
                break;
            }
            case CMP_ABS_X: {
                InstructionParams params = {4, low_byte_data, CMP_ABS_X, ABSOLUTE_INDEXED_PC};
                cm_instruction(params, vm.accumulator, &vm.x);
                break;
            }
            case CMP_ABS_Y: {
                InstructionParams params = {4, low_byte_data, CMP_ABS_Y, ABSOLUTE_INDEXED_PC};
                cm_instruction(params, vm.accumulator, &vm.y);
                break;
            }
            case CMP_ZP: {
                InstructionParams params = {3, low_byte_data, CMP_ZP, ZERO_PAGE};
                cm_instruction(params, vm.accumulator, NULL);
                break;
            }
            case CMP_ZP_X: {
                InstructionParams params = {4, low_byte_data, CMP_ZP_X, ZERO_PAGE_INDEXED};
                cm_instruction(params, vm.accumulator, &vm.x);
                break;
            }
            case CMP_ZP_X_IND: {
                InstructionParams params = {6, low_byte_data, CMP_ZP_X_IND, ZERO_PAGE_X_INDIRECT};
                cm_instruction(params, vm.accumulator, &vm.x);
                break;
            }
            case CMP_ZP_Y_IND: {
                InstructionParams params = {5, low_byte_data, CMP_ZP_Y_IND, ZERO_PAGE_Y_INDIRECT_PC};
                cm_instruction(params, vm.accumulator, &vm.y);
                break;
            }
            case CPX_IMM: {
                InstructionParams params = {2, low_byte_data, CPX_IMM, IMMEDIATE};
                cm_imm(params, vm.x);
                break;
            }
            case CPX_ABS: {
                InstructionParams params = {4, low_byte_data, CPX_ABS, ABSOLUTE};
                cm_instruction(params, vm.x, NULL);
                break;
            }
            case CPX_ZP: {
                InstructionParams params = {3, low_byte_data, CPX_ZP, ZERO_PAGE};
                cm_instruction(params, vm.x, NULL);
                break;
            }
            case CPY_IMM: {
                InstructionParams params = {2, low_byte_data, CPY_IMM, IMMEDIATE};
                cm_imm(params, vm.y);
                break;
            }
            case CPY_ABS: {
                InstructionParams params = {4, low_byte_data, CPY_ABS, ABSOLUTE};
                cm_instruction(params, vm.y, NULL);
                break;
            }
            case CPY_ZP: {
                InstructionParams params = {3, low_byte_data, CPY_ZP, ZERO_PAGE};
                cm_instruction(params, vm.y, NULL);
                break;
            }
            default: {
                printf("ERROR: OPCODE NOT FOUND\n");
                vm.cycles = 0;
                break;
            }
        }
    }
}

// fetching functions
void fetch_word(unsigned char* low_byte, unsigned char* high_byte)
{
    if(vm.ip == MEM_MAX_SIZE)
    {
        vm.ip = 0;
        *high_byte = memory.data[vm.ip];
        vm.ip++;
        *low_byte = memory.data[vm.ip];
        vm.ip++;
    }
    
    else if(vm.ip+2 == MEM_MAX_SIZE)
    {
        *high_byte = memory.data[vm.ip];
        *low_byte = memory.data[vm.ip+1];
        vm.ip = 0;
    }
    else if(vm.ip+1 == MEM_MAX_SIZE)
    {
        *high_byte = memory.data[vm.ip];
        vm.ip = 0;
        *low_byte = memory.data[vm.ip];
        vm.ip++;
    }
    else
    {
        *high_byte = memory.data[vm.ip];
        vm.ip++;
        *low_byte = memory.data[vm.ip];
        vm.ip++;
    }
    vm.cycles -= 2;
}
unsigned char fetch_byte()
{
    unsigned char Byte = memory.data[vm.ip];
    vm.ip += 1;
    if(out_of_bounds(vm.ip))
    {
        vm.ip = 0;
    }
    //printf("POINTER POINTS TO: %x\n", *vm.ip);
    vm.cycles -= 1;
    return Byte;
}

// zero page functions
void zp_wrapping(unsigned short* address, unsigned char vm_register)
{
    if((*address+vm_register)>0xFF) *address = *address + vm_register - 0x100; // -0x100 to include the 0th position in memory
    else *address = *address + vm_register;
    vm.cycles -= 1;
}
void fetch_word_zp(unsigned short address, unsigned char* low_byte, unsigned char* high_byte)
{
    // fetching the word from an address given by 2 bytes in the zeropage
    if(address == 0x00FF)
    {
        *high_byte = memory.data[0x00FF];
        *low_byte = memory.data[0x0000];
    }
    else
    {
        *high_byte = memory.data[address];
        *low_byte = memory.data[address+1];
    }
    vm.cycles -= 2;
}

// debugging functions
void debug(unsigned char instruction, unsigned char component)
{
    printf("INSTRUCTION %x: %d (%x in hexadecimal)\n", instruction, component, component);
    display_flags();
}

// other functions
void cycle_check(int cycle_amount)
{
    if(!(vm.cycles >= (cycle_amount-2))) // -2 cycles because the first operation is the same for every instruction (opcode and 1 operand)
    {
        printf("Insufficient cycle amount!\n");
        abort();
    }
}
void wrap_address(unsigned short* address) // Wraps the address if it goes out of bounds (for absolute addressing), use after incrementing the register
{
    *address = *address % 0x10000;
}
bool out_of_bounds(unsigned short address)
{
    return address > MEM_MAX_SIZE;
}
void onebyte_ins_fix() // Function for fixing the cycle count and the instruction pointer for one byte instructions
{
    vm.ip--; // move the pointer one byte back because of the fetch word function at the start of the while loop
    vm.cycles+=1; // also need to restore 1 cycle back
}

InstructionParams load_ins_params(unsigned int required_cycles, unsigned char low_byte, unsigned char instruction, AddressingModes addressing_mode)
{
    InstructionParams params;
    params.required_cycles = required_cycles;
    params.low_byte = low_byte;
    params.instruction = instruction;
    params.addressing_mode = addressing_mode;
    return params;
}
