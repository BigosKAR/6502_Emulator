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

// execution of instructions *most important function*
void execute(unsigned int *cycles)
{
    unsigned char high_byte_data;
    unsigned char low_byte_data;
    while(*cycles > 0)
    {
        if(*cycles <= 0)break;
        fetch_word(cycles, &low_byte_data, &high_byte_data); // takes 2 cycles away
        switch(high_byte_data)
        {
            case LDA_IMM: {
                ld_imm_logic(cycles, &low_byte_data, &vm.accumulator, LDA_IMM);
                break;
            }
            case LDA_ABS: {
                ld_abs_logic(cycles, &low_byte_data, &vm.accumulator, LDA_ABS);
                break;
            }
            case LDA_ABS_X: {
                ld_abs_reg_logic(cycles, &low_byte_data, &vm.accumulator, vm.x, LDA_ABS_X);
                break;
            }
            case LDA_ABS_Y: {
                ld_abs_reg_logic(cycles, &low_byte_data, &vm.accumulator, vm.y, LDA_ABS_Y);
                break;
            }
            case LDA_ZP: {
                // Useful for faster execution time because there is no need to fetch another byte
                ld_zp_logic(cycles, &low_byte_data, &vm.accumulator, LDA_ZP);
                break;
            }
            case LDA_ZP_X: {
                ld_zp_reg_logic(cycles, &low_byte_data, &vm.accumulator, vm.x, LDA_ZP_X);
                break;
            }
            case LDA_ZP_X_IND: {
                lda_zp_x_ind(cycles, &low_byte_data);
                break;
            }
            case LDA_ZP_Y_IND: {
                lda_zp_y_ind(cycles, &low_byte_data);
                break;
            }
            case LDX_IMM: {
                ld_imm_logic(cycles, &low_byte_data, &vm.x, LDX_IMM);
                break;
            }
            case LDX_ABS: {
                ld_abs_logic(cycles, &low_byte_data, &vm.x, LDX_ABS);
                break;
            }
            case LDX_ABS_Y: {
                ld_abs_reg_logic(cycles, &low_byte_data, &vm.x, vm.y, LDX_ABS_Y);
                break;
            }
            case LDX_ZP: {
                ld_zp_logic(cycles, &low_byte_data, &vm.x, LDX_ZP);
                break;
            }
            case LDX_ZP_Y: {
                ld_zp_reg_logic(cycles, &low_byte_data, &vm.x, vm.y, LDX_ZP_Y);
                break;
            }
            case LDY_IMM: {
                ld_imm_logic(cycles, &low_byte_data, &vm.y, LDY_IMM);
                break;
            }
            case LDY_ABS: {
                ld_abs_logic(cycles, &low_byte_data, &vm.y, LDY_ABS);
                break;
            }
            case LDY_ZP: {
                ld_zp_logic(cycles, &low_byte_data, &vm.y, LDY_ZP);
                break;
            }
            case LDY_ABS_X: {
                ld_abs_reg_logic(cycles, &low_byte_data, &vm.y, vm.x, LDY_ABS_X);
                break;
            }
            case LDY_ZP_X: {
                ld_zp_reg_logic(cycles, &low_byte_data, &vm.y, vm.x, LDY_ZP_X);
                break;
            }
            case STA_ABS: {
                st_abs_logic(cycles, low_byte_data, vm.accumulator, STA_ABS);
                break;
            }
            case STA_ZP: {
                st_zp_logic(cycles, low_byte_data, vm.accumulator, STA_ZP);
                break;
            }
            case STA_ZP_X:
            {
                st_zp_reg_logic(cycles, low_byte_data, vm.accumulator, vm.x, STA_ZP_X);
                break;
            }
            case STA_ABS_X: {
                sta_abs_reg_logic(cycles, low_byte_data, vm.x, STA_ABS_X);
                break;
            }
            case STA_ABS_Y: {
                sta_abs_reg_logic(cycles, low_byte_data, vm.y, STA_ABS_Y);
                break;
            }
            case STA_ZP_X_IND: {
                sta_zp_x_ind(cycles, low_byte_data);
                break;
            }
            case STA_ZP_Y_IND: {
                sta_zp_y_ind(cycles, low_byte_data);
                break;
            }
            case STX_ABS: {
                st_abs_logic(cycles, low_byte_data, vm.x, STX_ABS);
                break;
            }
            case STX_ZP:{
                st_zp_logic(cycles, low_byte_data, vm.x, STX_ZP);
                break;
            }
            case STX_ZP_Y: {
                st_zp_reg_logic(cycles, low_byte_data, vm.x, vm.y, STX_ZP_Y);
                break;
            }
            case STY_ABS: {
                st_abs_logic(cycles, low_byte_data, vm.y, STY_ABS);
                break;
            }
            case STY_ZP: {
                st_zp_logic(cycles, low_byte_data, vm.y, STX_ZP);
                break;
            }
            case STY_ZP_X: {
                st_zp_reg_logic(cycles, low_byte_data, vm.y, vm.x,STY_ZP_X);
                break;
            }
            case TAX: {
                trans_logic(cycles, &vm.x, vm.accumulator, TAX, false);
                break;
            }
            case TAY: {
                trans_logic(cycles, &vm.y, vm.accumulator, TAY, false);
                break;
            }
            case TSX: {
                unsigned short temp_add = 0x01 << 8 | vm.sp;
                trans_logic(cycles, &vm.x, memory.data[temp_add], TSX, false);
                break;
            }
            case TXA: {
                trans_logic(cycles, &vm.accumulator, vm.x, TXA, false);
                break;
            }
            case TXS: {
                unsigned short temp_add = 0x01 << 8 | vm.sp;
                trans_logic(cycles, &memory.data[temp_add], vm.x, TXS, true);
                break;
            }
            case TYA: {
                trans_logic(cycles, &vm.accumulator, vm.y, TYA, false);
                break;
            }
            case PHA: {
                push_stack_logic(cycles, &vm.accumulator, PHA);
                break;
            }
            case PHP: {
                push_stack_logic(cycles, &vm.processor_status, PHP);
                break;
            }
            case PLA: {
                pull_stack_logic(cycles, &vm.accumulator, PLA, true);
                break;
            }
            case PLP: {
                pull_stack_logic(cycles, &vm.processor_status, PLP, false);
                break;
            }
            case ASL_A: {
                shift_acc_logic(cycles, ASL_A);
                break;
            }
            case ASL_ABS: {
                shift_abs_logic(cycles, low_byte_data, ASL_ABS);
                break;
            }
            case ASL_ABS_X: {
                shift_abs_x_logic(cycles, low_byte_data, ASL_ABS_X);
                break;
            }
            case ASL_ZP: {
                shift_zp_logic(cycles, low_byte_data, ASL_ZP);
                break;
            }
            case ASL_ZP_X: {
                shift_zp_x_logic(cycles, low_byte_data, ASL_ZP_X);
                break;
            }
            case LSR_A: {
                shift_acc_logic(cycles, LSR_A);
                break;
            }
            case LSR_ABS: {
                shift_abs_logic(cycles, low_byte_data, LSR_ABS);
                break;
            }
            case LSR_ABS_X: {
                shift_abs_x_logic(cycles, low_byte_data, LSR_ABS_X);
                break;
            }
            case LSR_ZP: {
                shift_zp_logic(cycles, low_byte_data, LSR_ZP);
                break;
            }
            case LSR_ZP_X: {
                shift_zp_x_logic(cycles, low_byte_data, LSR_ZP_X);
                break;
            }
            case ROL_A: {
                rotate_acc_logic(cycles, ROL_A);
                break;
            }
            case ROL_ABS: {
                rotate_abs_logic(cycles, low_byte_data, ROL_ABS);
                break;
            }
            case ROL_ABS_X: {
                rotate_abs_x_logic(cycles, low_byte_data, ROL_ABS_X);
                break;
            }
            case ROL_ZP:{
                rotate_zp_logic(cycles, low_byte_data, ROL_ZP);
                break;
            }
            case ROL_ZP_X: {
                rotate_zp_x_logic(cycles, low_byte_data, ROL_ZP_X);
                break;
            }
            case ROR_A: {
                rotate_acc_logic(cycles, ROR_A);
                break;
            }
            case ROR_ABS:
            {
                rotate_abs_logic(cycles, low_byte_data, ROR_ABS);
                break;
            }
            case ROR_ABS_X: {
                rotate_abs_x_logic(cycles, low_byte_data, ROR_ABS_X);
                break;
            }
            case ROR_ZP: {
                rotate_zp_logic(cycles, low_byte_data, ROR_ZP);
                break;
            }
            case ROR_ZP_X: {
                rotate_zp_x_logic(cycles, low_byte_data, ROR_ZP_X);
                break;
            }
            case AND_IMM: {
                logical_imm(cycles, low_byte_data, AND_IMM);
                break;
            }
            case AND_ABS: {
                logical_abs(cycles, low_byte_data, AND_ABS);
                break;
            }
            case AND_ABS_X: {
                logical_abs_reg_logic(cycles, low_byte_data, vm.x, AND_ABS_X);
                break;
            }
            case AND_ABS_Y: {
                logical_abs_reg_logic(cycles, low_byte_data, vm.y, AND_ABS_Y);
                break;
            }
            case AND_ZP: {
                logical_zp(cycles, low_byte_data, AND_ZP);
                break;
            }
            case AND_ZP_X: {
                logical_zp_x(cycles, low_byte_data, AND_ZP_X);
                break;
            }
            case AND_ZP_X_IND: {
                logical_zp_x_ind(cycles, low_byte_data, AND_ZP_X_IND);
                break;
            }
            case AND_ZP_Y_IND: {
                logical_zp_y_ind(cycles, low_byte_data, AND_ZP_Y_IND);
                break;
            }
            case BIT_ABS:{
                bit_abs(cycles, low_byte_data, BIT_ABS);
                break;
            }
            case BIT_ZP:{
                bit_zp(cycles, low_byte_data, BIT_ZP);
                break;
            }
            case EOR_IMM: {
                logical_imm(cycles, low_byte_data, EOR_IMM);
                break;
            }
            case EOR_ABS: {
                logical_abs(cycles, low_byte_data, EOR_ABS);
                break;
            }
            case EOR_ABS_X: {
                logical_abs_reg_logic(cycles, low_byte_data, vm.x, EOR_ABS_X);
                break;
            }
            case EOR_ABS_Y: {
                logical_abs_reg_logic(cycles, low_byte_data, vm.y, EOR_ABS_Y);
                break;
            }
            case EOR_ZP: {
                logical_zp(cycles, low_byte_data, EOR_ZP);
                break;
            }
            case EOR_ZP_X: {
                logical_zp_x(cycles, low_byte_data, EOR_ZP_X);
                break;
            }
            case EOR_ZP_X_IND: {
                logical_zp_x_ind(cycles, low_byte_data, EOR_ZP_X_IND);
                break;
            }
            case EOR_ZP_Y_IND: {
                logical_zp_y_ind(cycles, low_byte_data, EOR_ZP_Y_IND);
                break;
            }
            case ORA_IMM: {
                logical_imm(cycles, low_byte_data, ORA_IMM);
                break;
            }
            case ORA_ABS: {
                logical_abs(cycles, low_byte_data, ORA_ABS);
                break;
            }
            case ORA_ABS_X: {
                logical_abs_reg_logic(cycles, low_byte_data, vm.x, ORA_ABS_X);
                break;
            }
            case ORA_ABS_Y: {
                logical_abs_reg_logic(cycles, low_byte_data, vm.y, ORA_ABS_Y);
                break;
            }
            case ORA_ZP: {
                logical_zp(cycles, low_byte_data, ORA_ZP);
                break;
            }
            case ORA_ZP_X: {
                logical_zp_x(cycles, low_byte_data, ORA_ZP_X);
                break;
            }
            case ORA_ZP_X_IND: {
                logical_zp_x_ind(cycles, low_byte_data, ORA_ZP_X_IND);
                break;
            }
            case ORA_ZP_Y_IND: {
                logical_zp_y_ind(cycles, low_byte_data, ORA_ZP_Y_IND);
                break;
            }
            default: {
                printf("ERROR: OPCODE NOT FOUND\n");
                *cycles = 0;
                break;
            }
        }
    }
}

// fetching functions
void fetch_word(unsigned int* cycles, unsigned char* low_byte, unsigned char* high_byte)
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
    *cycles -= 2;
}
unsigned char fetch_byte(unsigned int* cycles)
{
    unsigned char Byte = memory.data[vm.ip];
    vm.ip += 1;
    if(out_of_bounds(vm.ip))
    {
        vm.ip = 0;
    }
    //printf("POINTER POINTS TO: %x\n", *vm.ip);
    *cycles -= 1;
    return Byte;
}

// zero page functions
void zp_wrapping(unsigned int* cycles, unsigned short* address, unsigned char vm_register)
{
    if((*address+vm_register)>0xFF) *address = *address + vm_register - 0x100; // -0x100 to include the 0th position in memory
    else *address = *address + vm_register;
    *cycles -= 1;
}
void fetch_word_zp(unsigned int* cycles, unsigned short address, unsigned char* low_byte, unsigned char* high_byte)
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
    *cycles -= 2;
}

// debugging functions
void debug(unsigned char instruction, unsigned char component)
{
    printf("INSTRUCTION %x: %d (%x in hexadecimal)\n", instruction, component, component);
    display_flags();
}

// other functions
void cycle_check(unsigned int cycle_amount, unsigned int* cycles)
{
    if(!(*cycles >= cycle_amount)) // -2 cycles because the first operation is the same for every instruction (opcode and 1 operand)
    {
        printf("Insufficient cycle amount!\n");
        exit(EXIT_FAILURE);
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
void onebyte_ins_fix(unsigned int* cycles) // Function for fixing the cycle count and the instruction pointer for one byte instructions
{
    vm.ip--; // move the pointer one byte back because of the fetch word function at the start of the while loop
    *cycles+=1; // also need to restore 1 cycle back
}

// address fetching functions
