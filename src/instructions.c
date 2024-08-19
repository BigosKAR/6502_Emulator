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
#include "./instructions/inc/inc_instructions.h"
#include "./instructions/ctrl/ctrl_instructions.h"
#include "./instructions/branch/branch_instructions.h"

// execution of instructions *most important function*
void execute()
{
    unsigned char fetched_byte;
    InstructionParams params;
    while(vm.cycles > 0)
    {
        if(vm.cycles <= 0) {
            printf("Breaking loop, CYCLES: %d\n", vm.cycles);
            break;
        }
        fetched_byte = fetch_byte();
        switch(fetched_byte)
        {
            case LDA_IMM: {
                load_ins_params(&params, 2, LDA_IMM, IMMEDIATE);
                ld_imm(params, &vm.accumulator);
                break;
            }
            case LDA_ABS: {
                load_ins_params(&params, 4, LDA_ABS, ABSOLUTE);
                ld_instruction(params, &vm.accumulator, NULL);
                break;
            }
            case LDA_ABS_X: {
                load_ins_params(&params, 4, LDA_ABS_X, ABSOLUTE_INDEXED_PC);
                ld_instruction(params, &vm.accumulator, &vm.x);
                break;
            }
            case LDA_ABS_Y: {
                load_ins_params(&params, 4, LDA_ABS_Y, ABSOLUTE_INDEXED_PC);
                ld_instruction(params, &vm.accumulator, &vm.y);
                break;
            }
            case LDA_ZP: {
                load_ins_params(&params, 3, LDA_ZP, ZERO_PAGE);
                ld_instruction(params, &vm.accumulator, NULL);
                break;
            }
            case LDA_ZP_X: {
                load_ins_params(&params, 4, LDA_ZP_X, ZERO_PAGE_INDEXED);
                ld_instruction(params, &vm.accumulator, &vm.x);
                break;
            }
            case LDA_ZP_X_IND: {   
                load_ins_params(&params, 6, LDA_ZP_X_IND, ZERO_PAGE_X_INDIRECT);
                ld_instruction(params, &vm.accumulator, &vm.x);
                break;
            }
            case LDA_ZP_Y_IND: {
                load_ins_params(&params, 5, LDA_ZP_Y_IND, ZERO_PAGE_Y_INDIRECT_PC);
                ld_instruction(params, &vm.accumulator, &vm.y);
                break;
            }
            case LDX_IMM: {
                load_ins_params(&params, 2, LDX_IMM, IMMEDIATE);
                ld_imm(params, &vm.x);
                break;
            }
            case LDX_ABS: {
                load_ins_params(&params, 4, LDX_ABS, ABSOLUTE);
                ld_instruction(params, &vm.x, NULL);
                break;
            }
            case LDX_ABS_Y: {
                load_ins_params(&params, 4, LDX_ABS_Y, ABSOLUTE_INDEXED_PC);
                ld_instruction(params, &vm.x, &vm.y);
                break;
            }
            case LDX_ZP: {
                load_ins_params(&params, 3, LDX_ZP, ZERO_PAGE);
                ld_instruction(params, &vm.x, NULL);
                break;
            }
            case LDX_ZP_Y: {
                load_ins_params(&params, 4, LDX_ZP_Y, ZERO_PAGE_INDEXED);
                ld_instruction(params, &vm.x, &vm.y);
                break;
            }
            case LDY_IMM: {
                load_ins_params(&params, 2, LDY_IMM, IMMEDIATE);
                ld_imm(params, &vm.y);
                break;
            }
            case LDY_ABS: {
                load_ins_params(&params, 4, LDY_ABS, ABSOLUTE);
                ld_instruction(params, &vm.y, NULL);
                break;
            }
            case LDY_ZP: {
                load_ins_params(&params, 3, LDY_ZP, ZERO_PAGE);
                ld_instruction(params, &vm.y, NULL);
                break;
            }
            case LDY_ABS_X: {
                load_ins_params(&params, 4, LDY_ABS_X, ABSOLUTE_INDEXED_PC);
                ld_instruction(params, &vm.y, &vm.x);
                break;
            }
            case LDY_ZP_X: {
                load_ins_params(&params, 4, LDY_ZP_X, ZERO_PAGE_INDEXED);
                ld_instruction(params, &vm.y, &vm.x);
                break;
            }
            case STA_ABS: {
                load_ins_params(&params, 4, STA_ABS, ABSOLUTE);
                st_instruction(params, vm.accumulator, NULL);
                break;
            }
            case STA_ZP: {
                load_ins_params(&params, 3, STA_ZP, ZERO_PAGE);
                st_instruction(params, vm.accumulator, NULL);
                break;
            }
            case STA_ZP_X:{
                load_ins_params(&params, 4, STA_ZP_X, ZERO_PAGE_INDEXED);
                st_instruction(params, vm.accumulator, &vm.x); 
                break;
            }
            case STA_ABS_X: {
                load_ins_params(&params, 5, STA_ABS_X, ABSOLUTE_INDEXED);
                st_instruction(params, vm.accumulator, &vm.x);
                break;
            }
            case STA_ABS_Y: {
                load_ins_params(&params, 5, STA_ABS_Y, ABSOLUTE_INDEXED);
                st_instruction(params, vm.accumulator, &vm.y);
                break;
            }
            case STA_ZP_X_IND: {
                load_ins_params(&params, 6, STA_ZP_X_IND, ZERO_PAGE_X_INDIRECT);
                st_instruction(params, vm.accumulator, &vm.x);
                break;
            }
            case STA_ZP_Y_IND: {
                load_ins_params(&params, 6, STA_ZP_Y_IND, ZERO_PAGE_Y_INDIRECT);
                st_instruction(params, vm.accumulator, &vm.y);
                break;
            }
            case STX_ABS: {
                load_ins_params(&params, 4, STX_ABS, ABSOLUTE);
                st_instruction(params, vm.x, NULL);
                break;
            }
            case STX_ZP:{
                load_ins_params(&params, 3, STX_ZP, ZERO_PAGE);
                st_instruction(params, vm.x, NULL);
                break;
            }
            case STX_ZP_Y: {
                load_ins_params(&params, 4, STX_ZP_Y, ZERO_PAGE_INDEXED);
                st_instruction(params, vm.x, &vm.y);
                break;
            }
            case STY_ABS: {
                load_ins_params(&params, 4, STY_ABS, ABSOLUTE);
                st_instruction(params, vm.y, NULL);
                break;
            }
            case STY_ZP: {
                load_ins_params(&params, 3, STY_ZP, ZERO_PAGE);
                st_instruction(params, vm.y, NULL);
                break;
            }
            case STY_ZP_X: {
                load_ins_params(&params, 4, STY_ZP_X, ZERO_PAGE_INDEXED);
                st_instruction(params, vm.y, &vm.x);
                break;
            }
            case TAX: {
                load_ins_params(&params, 2, TAX, IMPLIED);
                transfer_instruction(params, &vm.x, vm.accumulator);
                break;
            }
            case TAY: {
                load_ins_params(&params, 2, TAY, IMPLIED);
                transfer_instruction(params, &vm.y, vm.accumulator);
                break;
            }
            case TSX: {
                load_ins_params(&params, 2, TSX, IMPLIED);
                transfer_instruction(params, &vm.x, vm.sp);
                break;
            }
            case TXA: {
                load_ins_params(&params, 2, TXA, IMPLIED);
                transfer_instruction(params, &vm.accumulator, vm.x);
                break;
            }
            case TXS: {
                load_ins_params(&params, 2, TXS, IMPLIED);
                transfer_instruction(params, &vm.sp, vm.x);
                break;
            }
            case TYA: {
                load_ins_params(&params, 2, TYA, IMPLIED);
                transfer_instruction(params, &vm.accumulator, vm.y);
                break;
            }
            case PHA: {
                load_ins_params(&params, 3, PHA, IMPLIED);
                push_stack_instruction(params, &vm.accumulator);
                break;
            }
            case PHP: {
                load_ins_params(&params, 3, PHP, IMPLIED);
                push_stack_instruction(params, &vm.processor_status);
                break;
            }
            case PLA: {
                load_ins_params(&params, 4, PLA, IMPLIED);
                pull_stack_instruction(params, &vm.accumulator);
                break;
            }
            case PLP: {
                load_ins_params(&params, 4, PLP, IMPLIED);
                pull_stack_instruction(params, &vm.processor_status);
                break;
            }
            case ASL_A: {
                load_ins_params(&params, 2, ASL_A, ACCUMULATOR);
                shift_accumulator(params, SHIFT_ASL);
                break;
            }
            case ASL_ABS: {
                load_ins_params(&params, 6, ASL_ABS, ABSOLUTE);
                shift_instruction(params, NULL, SHIFT_ASL);
                break;
            }
            case ASL_ABS_X: {
                load_ins_params(&params, 7, ASL_ABS_X, ABSOLUTE_INDEXED);
                shift_instruction(params, &vm.x, SHIFT_ASL);
                break;
            }
            case ASL_ZP: {
                load_ins_params(&params, 5, ASL_ZP, ZERO_PAGE);
                shift_instruction(params, NULL, SHIFT_ASL);
                break;
            }
            case ASL_ZP_X: {
                load_ins_params(&params, 6, ASL_ZP_X, ZERO_PAGE_INDEXED);
                shift_instruction(params, &vm.x, SHIFT_ASL);
                break;
            }
            case LSR_A: {
                load_ins_params(&params, 2, LSR_A, ACCUMULATOR);
                shift_accumulator(params, SHIFT_LSR);
                break;
            }
            case LSR_ABS: {
                load_ins_params(&params, 6, LSR_ABS, ABSOLUTE);
                shift_instruction(params, NULL, SHIFT_LSR);
                break;
            }
            case LSR_ABS_X: {
                load_ins_params(&params, 7, LSR_ABS_X, ABSOLUTE_INDEXED);
                shift_instruction(params, &vm.x, SHIFT_LSR);
                break;
            }
            case LSR_ZP: {
                load_ins_params(&params, 5, LSR_ZP, ZERO_PAGE);
                shift_instruction(params, NULL, SHIFT_LSR);
                break;
            }
            case LSR_ZP_X: {
                load_ins_params(&params, 6, LSR_ZP_X, ZERO_PAGE_INDEXED);
                shift_instruction(params, &vm.x, SHIFT_LSR);
                break;
            }
            case ROL_A: {
                load_ins_params(&params, 2, ROL_A, ACCUMULATOR);
                rotate_accumulator(params, SHIFT_ROL);
                break;
            }
            case ROL_ABS: {
                load_ins_params(&params, 6, ROL_ABS, ABSOLUTE);
                rotate_instruction(params, NULL, SHIFT_ROL);
                break;
            }
            case ROL_ABS_X: {
                load_ins_params(&params, 7, ROL_ABS_X, ABSOLUTE_INDEXED);
                rotate_instruction(params, &vm.x, SHIFT_ROL);
                break;
            }
            case ROL_ZP:{
                load_ins_params(&params, 5, ROL_ZP, ZERO_PAGE);
                rotate_instruction(params, NULL, SHIFT_ROL);
                break;
            }
            case ROL_ZP_X: {
                load_ins_params(&params, 6, ROL_ZP_X, ZERO_PAGE_INDEXED);
                rotate_instruction(params, &vm.x, SHIFT_ROL);
                break;
            }
            case ROR_A: {
                load_ins_params(&params, 2, ROR_A, ACCUMULATOR);
                rotate_accumulator(params, SHIFT_ROR);
                break;
            }
            case ROR_ABS:{
                load_ins_params(&params, 6, ROR_ABS, ABSOLUTE);
                rotate_instruction(params, NULL, SHIFT_ROR);
                break;
            }
            case ROR_ABS_X: {
                load_ins_params(&params, 7, ROR_ABS_X, ABSOLUTE_INDEXED);
                rotate_instruction(params, &vm.x, SHIFT_ROR);
                break;
            }
            case ROR_ZP: {
                load_ins_params(&params, 5, ROR_ZP, ZERO_PAGE);
                rotate_instruction(params, NULL, SHIFT_ROR);
                break;
            }
            case ROR_ZP_X: {
                load_ins_params(&params, 6, ROR_ZP_X, ZERO_PAGE_INDEXED);
                rotate_instruction(params, &vm.x, SHIFT_ROR);
                break;
            }
            case AND_IMM: {
                load_ins_params(&params, 2, AND_IMM, IMMEDIATE);
                logical_imm(params);
                break;
            }
            case AND_ABS: {
                load_ins_params(&params, 4, AND_ABS, ABSOLUTE);
                logical_instruction(params, NULL, LOGIC_AND);
                break;
            }
            case AND_ABS_X: {
                load_ins_params(&params, 4, AND_ABS_X, ABSOLUTE_INDEXED_PC);
                logical_instruction(params, &vm.x, LOGIC_AND);
                break;
            }
            case AND_ABS_Y: {
                load_ins_params(&params, 4, AND_ABS_Y, ABSOLUTE_INDEXED_PC);
                logical_instruction(params, &vm.y, LOGIC_AND);
                break;
            }
            case AND_ZP: {
                load_ins_params(&params, 3, AND_ZP, ZERO_PAGE);
                logical_instruction(params, NULL, LOGIC_AND);
                break;
            }
            case AND_ZP_X: {
                load_ins_params(&params, 4, AND_ZP_X, ZERO_PAGE_INDEXED);
                logical_instruction(params, &vm.x, LOGIC_AND);
                break;
            }
            case AND_ZP_X_IND: {
                load_ins_params(&params, 6, AND_ZP_X_IND, ZERO_PAGE_X_INDIRECT);
                logical_instruction(params, &vm.x, LOGIC_AND);
                break;
            }
            case AND_ZP_Y_IND: {
                load_ins_params(&params, 5, AND_ZP_Y_IND, ZERO_PAGE_Y_INDIRECT_PC);
                logical_instruction(params, &vm.y, LOGIC_AND);
                break;
            }
            case BIT_ABS:{
                load_ins_params(&params, 4, BIT_ABS, ABSOLUTE);
                bit_instruction(params);
                break;
            }
            case BIT_ZP:{
                load_ins_params(&params, 3, BIT_ZP, ZERO_PAGE);
                bit_instruction(params);
                break;
            }
            case EOR_IMM: {
                load_ins_params(&params, 2, EOR_IMM, IMMEDIATE);
                logical_imm(params);
                break;
            }
            case EOR_ABS: {
                load_ins_params(&params, 4, EOR_ABS, ABSOLUTE);
                logical_instruction(params, NULL, LOGIC_XOR);
                break;
            }
            case EOR_ABS_X: {
                load_ins_params(&params, 4, EOR_ABS_X, ABSOLUTE_INDEXED_PC);
                logical_instruction(params, &vm.x, LOGIC_XOR);
                break;
            }
            case EOR_ABS_Y: {
                load_ins_params(&params, 4, EOR_ABS_Y, ABSOLUTE_INDEXED_PC);
                logical_instruction(params, &vm.y, LOGIC_XOR);
                break;
            }
            case EOR_ZP: {
                load_ins_params(&params, 3, EOR_ZP, ZERO_PAGE);
                logical_instruction(params, NULL, LOGIC_XOR);
                break;
            }
            case EOR_ZP_X: {
                load_ins_params(&params, 4, EOR_ZP_X, ZERO_PAGE_INDEXED);
                logical_instruction(params, &vm.x, LOGIC_XOR);
                break;
            }
            case EOR_ZP_X_IND: {
                load_ins_params(&params, 6, EOR_ZP_X_IND, ZERO_PAGE_X_INDIRECT);
                logical_instruction(params, &vm.x, LOGIC_XOR);
                break;
            }
            case EOR_ZP_Y_IND: {
                load_ins_params(&params, 5, EOR_ZP_Y_IND, ZERO_PAGE_Y_INDIRECT_PC);
                logical_instruction(params, &vm.y, LOGIC_XOR);
                break;
            }
            case ORA_IMM: {
                load_ins_params(&params, 2, ORA_IMM, IMMEDIATE);
                logical_imm(params);
                break;
            }
            case ORA_ABS: {
                load_ins_params(&params, 4, ORA_ABS, ABSOLUTE);
                logical_instruction(params, NULL, LOGIC_OR);                
                break;
            }
            case ORA_ABS_X: {
                load_ins_params(&params, 4, ORA_ABS_X, ABSOLUTE_INDEXED_PC);
                logical_instruction(params, &vm.x, LOGIC_OR);
                break;
            }
            case ORA_ABS_Y: {
                load_ins_params(&params, 4, ORA_ABS_Y, ABSOLUTE_INDEXED_PC);
                logical_instruction(params, &vm.y, LOGIC_OR);
                break;
            }
            case ORA_ZP: {
                load_ins_params(&params, 3, ORA_ZP, ZERO_PAGE);
                logical_instruction(params, NULL, LOGIC_OR);                
                break;
            }
            case ORA_ZP_X: {
                load_ins_params(&params, 4, ORA_ZP_X, ZERO_PAGE_INDEXED);
                logical_instruction(params, &vm.x, LOGIC_OR);
                break;
            }
            case ORA_ZP_X_IND: {
                load_ins_params(&params, 6, ORA_ZP_X_IND, ZERO_PAGE_X_INDIRECT);
                logical_instruction(params, &vm.x, LOGIC_OR);
                break;
            }
            case ORA_ZP_Y_IND: {
                load_ins_params(&params, 5, ORA_ZP_Y_IND, ZERO_PAGE_Y_INDIRECT_PC);
                logical_instruction(params, &vm.y, LOGIC_OR);
                break;
            }
            case ADC_IMM: {
                load_ins_params(&params, 2, ADC_IMM, IMMEDIATE);
                adc_imm(params);
                break;
            }
            case ADC_ABS: {
                load_ins_params(&params, 4, ADC_ABS, ABSOLUTE);
                adc_instruction(params, NULL);
                break;
            }
            case ADC_ABS_X: {
                load_ins_params(&params, 4, ADC_ABS_X, ABSOLUTE_INDEXED_PC);
                adc_instruction(params, &vm.x);
                break;
            }
            case ADC_ABS_Y: {
                load_ins_params(&params, 4, ADC_ABS_Y, ABSOLUTE_INDEXED_PC);
                adc_instruction(params, &vm.y);
                break;
            }
            case ADC_ZP: {
                load_ins_params(&params, 3, ADC_ZP, ZERO_PAGE);
                adc_instruction(params, NULL);
                break;
            }
            case ADC_ZP_X: {
                load_ins_params(&params, 4, ADC_ZP_X, ZERO_PAGE_INDEXED);
                adc_instruction(params, &vm.x);
                break;
            }
            case ADC_ZP_X_IND: {
                load_ins_params(&params, 6, ADC_ZP_X_IND, ZERO_PAGE_X_INDIRECT);
                adc_instruction(params, &vm.x);
                break;
            }
            case ADC_ZP_Y_IND: {
                load_ins_params(&params, 5, ADC_ZP_Y_IND, ZERO_PAGE_Y_INDIRECT_PC);
                adc_instruction(params, &vm.y);
                break;
            }
            case CMP_IMM: {
                load_ins_params(&params, 2, CMP_IMM, IMMEDIATE);
                cm_imm(params, vm.accumulator);
                break;
            }
            case CMP_ABS: {
                load_ins_params(&params, 4, CMP_ABS, ABSOLUTE);
                cm_instruction(params, vm.accumulator, NULL);
                break;
            }
            case CMP_ABS_X: {
                load_ins_params(&params, 4, CMP_ABS_X, ABSOLUTE_INDEXED_PC);
                cm_instruction(params, vm.accumulator, &vm.x);
                break;
            }
            case CMP_ABS_Y: {
                load_ins_params(&params, 4, CMP_ABS_Y, ABSOLUTE_INDEXED_PC);
                cm_instruction(params, vm.accumulator, &vm.y);
                break;
            }
            case CMP_ZP: {
                load_ins_params(&params, 3, CMP_ZP, ZERO_PAGE);
                cm_instruction(params, vm.accumulator, NULL);
                break;
            }
            case CMP_ZP_X: {
                load_ins_params(&params, 4, CMP_ZP_X, ZERO_PAGE_INDEXED);
                cm_instruction(params, vm.accumulator, &vm.x);
                break;
            }
            case CMP_ZP_X_IND: {
                load_ins_params(&params, 6, CMP_ZP_X_IND, ZERO_PAGE_X_INDIRECT);
                cm_instruction(params, vm.accumulator, &vm.x);
                break;
            }
            case CMP_ZP_Y_IND: {
                load_ins_params(&params, 5, CMP_ZP_Y_IND, ZERO_PAGE_Y_INDIRECT_PC);
                cm_instruction(params, vm.accumulator, &vm.y);
                break;
            }
            case CPX_IMM: {
                load_ins_params(&params, 2, CPX_IMM, IMMEDIATE);
                cm_imm(params, vm.x);
                break;
            }
            case CPX_ABS: {
                load_ins_params(&params, 4, CPX_ABS, ABSOLUTE);
                cm_instruction(params, vm.x, NULL);
                break;
            }
            case CPX_ZP: {
                load_ins_params(&params, 3, CPX_ZP, ZERO_PAGE);
                cm_instruction(params, vm.x, NULL);
                break;
            }
            case CPY_IMM: {
                load_ins_params(&params, 2, CPY_IMM, IMMEDIATE);
                cm_imm(params, vm.y);
                break;
            }
            case CPY_ABS: {
                load_ins_params(&params, 4, CPY_ABS, ABSOLUTE);
                cm_instruction(params, vm.y, NULL);
                break;
            }
            case CPY_ZP: {
                load_ins_params(&params, 3, CPY_ZP, ZERO_PAGE);
                cm_instruction(params, vm.y, NULL);
                break;
            }
            case SBC_IMM:{
                load_ins_params(&params, 2, SBC_IMM, IMMEDIATE);
                sbc_imm(params);
                break;
            }
            case SBC_ABS: {
                load_ins_params(&params, 4, SBC_ABS, ABSOLUTE);
                sbc_instruction(params, NULL);
                break;
            }
            case SBC_ABS_X: {
                load_ins_params(&params, 4, SBC_ABS_X, ABSOLUTE_INDEXED_PC);
                sbc_instruction(params, &vm.x);
                break;
            }
            case SBC_ABS_Y: {
                load_ins_params(&params, 4, SBC_ABS_Y, ABSOLUTE_INDEXED_PC);
                sbc_instruction(params, &vm.y);
                break;
            }
            case SBC_ZP: {
                load_ins_params(&params, 3, SBC_ZP, ZERO_PAGE);
                sbc_instruction(params, NULL);
                break;
            }
            case SBC_ZP_X: {
                load_ins_params(&params, 4, SBC_ZP_X, ZERO_PAGE_INDEXED);
                sbc_instruction(params, &vm.x);
                break;
            }
            case SBC_ZP_X_IND: {
                load_ins_params(&params, 6, SBC_ZP_X_IND, ZERO_PAGE_X_INDIRECT);
                sbc_instruction(params, &vm.x);
                break;
            }
            case SBC_ZP_Y_IND: {
                load_ins_params(&params, 5, SBC_ZP_Y_IND, ZERO_PAGE_Y_INDIRECT_PC);
                sbc_instruction(params, &vm.y);
                break;
            }
            case DEC_ABS: {
                load_ins_params(&params, 6, DEC_ABS, ABSOLUTE);
                IncParams inc_params = {MEMORY, DECREMENT};
                inc_instruction(params, inc_params, NULL);
                break;
            }
            case DEC_ABS_X: {
                load_ins_params(&params, 7, DEC_ABS_X, ABSOLUTE_INDEXED);
                IncParams inc_params = {MEMORY, DECREMENT};
                inc_instruction(params, inc_params, &vm.x);
                break;
            }
            case DEC_ZP: {
                load_ins_params(&params, 5, DEC_ZP, ZERO_PAGE);
                IncParams inc_params = {MEMORY, DECREMENT};
                inc_instruction(params, inc_params, NULL);
                break;
            }
            case DEC_ZP_X: {
                load_ins_params(&params, 6, DEC_ZP_X, ZERO_PAGE_INDEXED);
                IncParams inc_params = {MEMORY, DECREMENT};
                inc_instruction(params, inc_params, &vm.x);
                break;
            }
            case DEX: {
                load_ins_params(&params, 2, DEX, IMPLIED);
                IncParams inc_params = {REGISTER_X, DECREMENT};
                inc_instruction(params, inc_params, NULL);
                break;
            }
            case DEY: {
                load_ins_params(&params, 2, DEY, IMPLIED);
                IncParams inc_params = {REGISTER_Y, DECREMENT};
                inc_instruction(params, inc_params, NULL);
                break;
            }
            case INC_ABS: {
                load_ins_params(&params, 6, INC_ABS, ABSOLUTE);
                IncParams inc_params = {MEMORY, INCREMENT};
                inc_instruction(params, inc_params, NULL);
                break;
            }
            case INC_ABS_X: {
                load_ins_params(&params, 7, INC_ABS_X, ABSOLUTE_INDEXED);
                IncParams inc_params = {MEMORY, INCREMENT};
                inc_instruction(params, inc_params, &vm.x);
                break;
            }
            case INC_ZP: {
                load_ins_params(&params, 5, INC_ZP, ZERO_PAGE);
                IncParams inc_params = {MEMORY, INCREMENT};
                inc_instruction(params, inc_params, NULL);
                break;
            }
            case INC_ZP_X: {
                load_ins_params(&params, 6, INC_ZP_X, ZERO_PAGE_INDEXED);
                IncParams inc_params = {MEMORY, INCREMENT};
                inc_instruction(params, inc_params, &vm.x);
                break;
            }
            case INX: {
                load_ins_params(&params, 2, INX, IMPLIED);
                IncParams inc_params = {REGISTER_X, INCREMENT};
                inc_instruction(params, inc_params, NULL);
                break;
            }
            case INY: {
                load_ins_params(&params, 2, INY, IMPLIED);
                IncParams inc_params = {REGISTER_Y, INCREMENT};
                inc_instruction(params, inc_params, NULL);
                break;
            }
            case BRK: {
                load_ins_params(&params, 7, BRK, IMPLIED);
                brk_instruction(params);
                break;
            }
            case JMP_ABS: {
                load_ins_params(&params, 3, JMP_ABS, ABSOLUTE);
                jmp_instruction(params);
                break;
            }
            case JMP_ABS_IND: {
                load_ins_params(&params, 5, JMP_ABS_IND, ABSOLUTE_INDIRECT);
                jmp_instruction(params);
                break;
            }
            case JSR: {
                load_ins_params(&params, 6, JSR, ABSOLUTE);
                jsr_instruction(params);
                break;
            }
            case RTI: {
                load_ins_params(&params, 6, RTI, IMPLIED);
                rti_instruction(params);
                break;
            }
            case RTS: {
                load_ins_params(&params, 6, RTS, IMPLIED);
                rts_instruction(params);
                break;
            }
            case BCC: {
                load_ins_params(&params, 2, BCC, RELATIVE);
                bool condition = !(vm.processor_status & FLAG_CARRY);
                flag_branch_instruction(params, condition);
                break;
            }
            case BCS: {
                load_ins_params(&params, 2, BCS, RELATIVE);
                bool condition = vm.processor_status & FLAG_CARRY;
                flag_branch_instruction(params, condition);
                break;
            }
            case BEQ: {
                load_ins_params(&params, 2, BEQ, RELATIVE);
                bool condition = vm.processor_status & FLAG_ZERO;
                flag_branch_instruction(params, condition);
                break;
            }
            case BMI: {
                load_ins_params(&params, 2, BMI, RELATIVE);
                bool condition = vm.processor_status & FLAG_NEGATIVE;
                flag_branch_instruction(params, condition);
                break;
            }
            case BNE: {
                load_ins_params(&params, 2, BNE, RELATIVE);
                bool condition = !(vm.processor_status & FLAG_ZERO);
                flag_branch_instruction(params, condition);
                break;
            }
            case BPL: {
                load_ins_params(&params, 2, BPL, RELATIVE);
                bool condition = !(vm.processor_status & FLAG_NEGATIVE);
                flag_branch_instruction(params, condition);
                break;
            }
            case BVC: {
                load_ins_params(&params, 2, BVC, RELATIVE);
                bool condition = !(vm.processor_status & FLAG_OVERFLOW);
                flag_branch_instruction(params, condition);
                break;
            }
            case BVS: {
                load_ins_params(&params, 2, BVS, RELATIVE);
                bool condition = vm.processor_status & FLAG_OVERFLOW;
                flag_branch_instruction(params, condition);
                break;
            }
            case CLC: {
                load_ins_params(&params, 2, CLC, IMPLIED);
                modify_flag_instruction(params, FLAG_CARRY, false);
                break;
            }
            case CLD: {
                load_ins_params(&params, 2, CLD, IMPLIED);
                modify_flag_instruction(params, FLAG_DECIMAL, false);
                break;
            }
            case CLI: {
                load_ins_params(&params, 2, CLI, IMPLIED);
                modify_flag_instruction(params, FLAG_INTERRUPT, false);
                break;
            }
            case CLV: {
                load_ins_params(&params, 2, CLV, IMPLIED);
                modify_flag_instruction(params, FLAG_OVERFLOW, false);
                break;
            }
            case SEC: {
                load_ins_params(&params, 2, SEC, IMPLIED);
                modify_flag_instruction(params, FLAG_CARRY, true);
                break;
            }
            case SED: {
                load_ins_params(&params, 2, SED, IMPLIED);
                modify_flag_instruction(params, FLAG_DECIMAL, true);
                break;
            }
            case SEI: {
                load_ins_params(&params, 2, SEI, IMPLIED);
                modify_flag_instruction(params, FLAG_INTERRUPT, true);
                break;
            }
            case NOP: {
                load_ins_params(&params, 2, NOP, IMPLIED);
                nop_instruction(params);
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
void fetch_word(unsigned char* first_byte, unsigned char* second_byte)
{
    if(vm.ip == MEM_MAX_SIZE)
    {
        vm.ip = 0;
        *first_byte = memory.data[vm.ip];
        vm.ip++;
        *second_byte = memory.data[vm.ip];
        vm.ip++;
    }
    
    else if(vm.ip+2 == MEM_MAX_SIZE)
    {
        *first_byte = memory.data[vm.ip];
        *second_byte = memory.data[vm.ip+1];
        vm.ip = 0;
    }
    else if(vm.ip+1 == MEM_MAX_SIZE)
    {
        *first_byte = memory.data[vm.ip];
        vm.ip = 0;
        *second_byte = memory.data[vm.ip];
        vm.ip++;
    }
    else
    {
        *first_byte = memory.data[vm.ip];
        vm.ip++;
        *second_byte = memory.data[vm.ip];
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
void fetch_word_zp(unsigned short address, unsigned char* first_byte, unsigned char* second_byte)
{
    // fetching the word from an address given by 2 bytes in the zeropage
    if(address == 0x00FF)
    {
        *first_byte = memory.data[0x00FF];
        *second_byte = memory.data[0x0000];
    }
    else
    {
        *first_byte = memory.data[address];
        *second_byte = memory.data[address+1];
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
    if(!(vm.cycles >= (cycle_amount-1))) // -1 cycle because the first operation is the same for every instruction (fetching opcode)
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

void load_ins_params(InstructionParams *params, int required_cycles, unsigned char instruction, AddressingModes addressing_mode)
{
    params->required_cycles = required_cycles;
    // Omit loading the low byte because it will be set at the start of the loop
    params->instruction = instruction;
    params->addressing_mode = addressing_mode;
}

void nop_instruction(InstructionParams params)
{
    cycle_check(params.required_cycles);
    vm.cycles -= 1;
}