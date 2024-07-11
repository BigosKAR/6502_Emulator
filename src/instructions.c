#include "instructions.h"
#include <stdbool.h>
#include "flags.h"
#include <string.h>
#include <stdlib.h>

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
                asl_accumulator(cycles, ASL_A);
                break;
            }
            case ASL_ABS: {
                asl_absolute(cycles, low_byte_data, ASL_ABS);
                break;
            }
            case ASL_ABS_X: {
                asl_abs_x(cycles, low_byte_data, ASL_ABS_X);
                break;
            }
            case ASL_ZP: {
                asl_zp(cycles, low_byte_data, ASL_ZP);
                break;
            }
            case ASL_ZP_X: {
                asl_zp_x(cycles, low_byte_data, ASL_ZP_X);
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

// instruction functions for repeating code
void ld_abs_reg_logic(unsigned int* cycles, unsigned char* low_order_address, unsigned char* vm_register, unsigned char vm_reg_indexed, unsigned char instruction)
{
    cycle_check(4-2, cycles); 
    unsigned char high_order_address = fetch_byte(cycles); // -1 cycle
    unsigned short address = (high_order_address <<8) | *low_order_address;
    unsigned short temp_address;
    temp_address = address + vm_reg_indexed;
    if((address & 0xFF00) != (temp_address & 0xFF00))
    {
        *cycles -= 1; // If page boundary crossed then take 1 cycle
        cycle_check(1, cycles);
    }
    wrap_address(&temp_address);
    *vm_register = memory.data[temp_address];
    *cycles -= 1; // reading the byte from memory
    updateNZFlags(*vm_register);
    debug(instruction, *vm_register);
}
void ld_imm_logic(unsigned int* cycles, unsigned char* low_byte, unsigned char *vm_register, unsigned char instruction)
{
    cycle_check(2-2, cycles);
    *vm_register = *low_byte;
    updateNZFlags(*vm_register);
    debug(instruction, *vm_register);
}
void ld_abs_logic(unsigned int* cycles, unsigned char* low_order_address, unsigned char* vm_register, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned char high_order_address = fetch_byte(cycles);
    unsigned short address = (high_order_address <<8) | *low_order_address;
    *vm_register = memory.data[address];
    *cycles -= 1; // reading the byte from memory
    updateNZFlags(*vm_register);
    debug(instruction, *vm_register);
}
void ld_zp_logic(unsigned int* cycles, unsigned char* low_byte, unsigned char* vm_register, unsigned char instruction)
{
    cycle_check(3-2, cycles);
    unsigned short address = (0x00<<8) | *low_byte;
    *vm_register = memory.data[address];
    *cycles -= 1;
    updateNZFlags(*vm_register);
    debug(instruction, *vm_register);
}
void ld_zp_reg_logic(unsigned int* cycles, unsigned char* low_byte, unsigned char* vm_register, unsigned char vm_reg_indexed, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned short zp_address = (0x00<<8) | *low_byte;
    zp_wrapping(cycles, &zp_address, vm_reg_indexed); //changing the address, checking for potential zeropage wrapping
    *vm_register = memory.data[zp_address];
    *cycles -= 1;
    updateNZFlags(*vm_register);
    debug(instruction, *vm_register);
}
void lda_zp_x_ind(unsigned int* cycles, unsigned char* low_byte)
{
    cycle_check(6-2, cycles);
    unsigned short address = (0x00<<8) | *low_byte;
    unsigned short new_address;
    unsigned char high_b_add, low_b_add;
    zp_wrapping(cycles, &address, vm.x);  //changing the address, checking for potential zeropage wrapping
    fetch_word_zp(cycles, address, &low_b_add, &high_b_add);
    new_address = (low_b_add << 8) | high_b_add;
    vm.accumulator = memory.data[new_address];
    *cycles -= 1;
    updateNZFlags(vm.accumulator);
    debug(LDA_ZP_X_IND, vm.accumulator); 
}
void lda_zp_y_ind(unsigned int* cycles, unsigned char* low_byte)
{
    cycle_check(5-2, cycles); // does not check for extra cycle
    unsigned short address = (0x00<<8) | *low_byte;
    unsigned short indirect_address, temp_address;
    unsigned char high_b_add, low_b_add;
    fetch_word_zp(cycles, address, &low_b_add, &high_b_add); // -2 cycles
    indirect_address = low_b_add << 8 | high_b_add;
    temp_address = indirect_address;
    indirect_address+=vm.y;
    if((temp_address & 0xFF00) != (indirect_address & 0xFF00))
    {
        *cycles -= 1; // If page boundary crossed then take 1 cycle
        cycle_check(1, cycles);
    
    }
    wrap_address(&indirect_address);
    vm.accumulator = memory.data[indirect_address];
    *cycles -= 1;
    updateNZFlags(vm.accumulator);
    debug(LDA_ZP_Y_IND, vm.accumulator);
}

void st_abs_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_register, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned char high_order_address = fetch_byte(cycles);
    unsigned short address = (high_order_address <<8) | low_order_address;
    memory.data[address] = vm_register;
    *cycles -= 1; 
    // no flags affected
    debug(instruction, memory.data[address]);
}
void st_zp_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_register, unsigned char instruction)
{
    cycle_check(3-2, cycles);
    unsigned short address = (0x00<<8) | low_order_address;
    memory.data[address] = vm_register;
    *cycles -= 1;
    // no flags affected
    debug(instruction, memory.data[address]);
}
void st_zp_reg_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_register, unsigned char vm_reg_indexed, unsigned char instruction)
{
    cycle_check(4-2, cycles);
    unsigned short zp_address = (0x00<<8) | low_order_address;
    zp_wrapping(cycles, &zp_address, vm_reg_indexed);  // takes 1 cycle
    memory.data[zp_address] = vm_register;
    *cycles -= 1;
    // no flags affected
    debug(instruction, memory.data[zp_address]);
}
void sta_abs_reg_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_reg_indexed, unsigned char instruction)
{
    cycle_check(5-2, cycles);
    unsigned short address = (fetch_byte(cycles) << 8) | low_order_address;
    address += vm_reg_indexed; // adding contents of the register to the address
    wrap_address(&address); 
    *cycles -= 1;
    memory.data[address] = vm.accumulator;
    *cycles -= 1;
    debug(instruction, memory.data[address]);
}
void sta_zp_x_ind(unsigned int* cycles, unsigned char low_byte)
{
    cycle_check(6-2, cycles);
    unsigned short zp_address = (0x00<<8) | low_byte;
    zp_wrapping(cycles, &zp_address, vm.x);
    unsigned short new_address;
    unsigned char high_b_add, low_b_add;
    fetch_word_zp(cycles, zp_address, &low_b_add, &high_b_add);
    new_address = (low_b_add << 8) | high_b_add;
    memory.data[new_address] = vm.accumulator;
    *cycles -= 1;
    debug(STA_ZP_X_IND, memory.data[new_address]);
}
void sta_zp_y_ind(unsigned int* cycles, unsigned char low_byte)
{
    cycle_check(6-2, cycles);
    unsigned short zp_address = (0x00 << 8) | low_byte;
    unsigned char high_b_add, low_b_add;
    fetch_word_zp(cycles, zp_address, &low_b_add, &high_b_add);
    unsigned short new_address = low_b_add << 8 | high_b_add;
    new_address += vm.y;
    *cycles -= 1;
    wrap_address(&new_address);
    memory.data[new_address] = vm.accumulator;
    *cycles -= 1;
    debug(STA_ZP_Y_IND, memory.data[new_address]);
}

void trans_logic(unsigned int* cycles, unsigned char* vmr_destination, unsigned char vmr_source, unsigned char instruction, bool isTXS)
{
    onebyte_ins_fix(cycles);
    cycle_check(2-1, cycles);
    *vmr_destination = vmr_source;
    *cycles -= 1;
    if(!isTXS)updateNZFlags(*vmr_destination);
    debug(instruction, *vmr_destination);
}

void push_stack_logic(unsigned int* cycles, unsigned char* vm_register, unsigned char instruction)
{
    onebyte_ins_fix(cycles);
    cycle_check(3-1, cycles);
    unsigned short stack_add = 0x01 << 8 | vm.sp;
    vm.sp--;
    wrap_stack_pointer(); // Wraps the stack pointer if it goes out of bounds
    *cycles -= 1; // Cycle for decremeting the stack pointer
    memory.data[stack_add] = *vm_register;
    *cycles -= 1; // Cycle for writing to the stack
    debug(instruction, memory.data[stack_add]);
}
void pull_stack_logic(unsigned int* cycles, unsigned char* vm_register, unsigned char instruction, bool isPLA)
{
    onebyte_ins_fix(cycles);
    cycle_check(4-1, cycles);
    vm.sp++;
    *cycles -= 1; 
    unsigned short stack_add = 0x01 << 8 | vm.sp;
    *vm_register = memory.data[stack_add];
    *cycles -= 2; // Read value from stack and write the value to the register (takes 2 cycles)
    wrap_stack_pointer();
    if(isPLA)updateNZFlags(*vm_register);
    debug(instruction, *vm_register);
}

void asl_accumulator(unsigned int* cycles, unsigned char instruction)
{
    onebyte_ins_fix(cycles);
    cycle_check(2-1, cycles);
    unsigned char temp_var = vm.accumulator;
    vm.accumulator = vm.accumulator << 1;
    *cycles -= 1;
    updateNZC_Flags(vm.accumulator, temp_var);
    debug(instruction, vm.accumulator);
}
void asl_absolute(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(6-2, cycles);
    unsigned char high_order_address = fetch_byte(cycles);
    unsigned short address = (high_order_address << 8) | low_order_address;
    unsigned char temp_var = memory.data[address];
    memory.data[address] = memory.data[address] << 1;
    *cycles -= 3; // reading memory from initial address, shifting the value, and writing it back to the same location
    updateNZC_Flags(memory.data[address], temp_var);
    debug(instruction, memory.data[address]);
}
void asl_abs_x(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(7-2, cycles);
    unsigned char high_order_address = fetch_byte(cycles); // -1 cycle
    unsigned short new_address = high_order_address << 8 | low_order_address;
    new_address += vm.x;
    wrap_address(&new_address);
    unsigned char temp_var = memory.data[new_address];
    memory.data[new_address] = memory.data[new_address] << 1;
    *cycles -= 4; // adding x reg content to an address, reading memory from that address, performing the shift, and writing the result back to the same location
    updateNZC_Flags(memory.data[new_address], temp_var);
    debug(instruction, memory.data[new_address]);
}
void asl_zp(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(5-2, cycles);
    unsigned short zp_address = (0x00 << 8) | low_order_address;
    unsigned char temp_var = memory.data[zp_address];
    memory.data[zp_address] = memory.data[zp_address] << 1;
    *cycles -= 3; // reading memory from initial address, performing the shift, and writing the result back to the same location
    updateNZC_Flags(memory.data[zp_address], temp_var);
    debug(instruction, memory.data[zp_address]);
}
void asl_zp_x(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction)
{
    cycle_check(6-2, cycles);
    unsigned short zp_address = (0x00 << 8) | low_order_address;
    zp_wrapping(cycles, &zp_address, vm.x);
    unsigned char temp_var = memory.data[zp_address];
    memory.data[zp_address] = memory.data[zp_address] << 1;
    *cycles -= 3; // reading memory from initial address, performing the shift, and writing the result back to the same location
    updateNZC_Flags(memory.data[zp_address], temp_var);
    debug(instruction, memory.data[zp_address]);
}

// zero page functions
void zp_wrapping(int* cycles, unsigned short* address, unsigned char vm_register)
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
void wrap_stack_pointer()
{
    if(vm.sp < 0x00)
    {
        vm.sp = 0xFF;
        printf("Wrapped around the stack pointer\n");
    }
    else if(vm.sp > 0xFF)
    {
        vm.sp = 0x00;
    }
}
void onebyte_ins_fix(unsigned int* cycles) // Function for fixing the cycle count and the instruction pointer for one byte instructions
{
    vm.ip--; // move the pointer one byte back because of the fetch word function at the start of the while loop
    *cycles+=1; // also need to restore 1 cycle back
}