#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "flags.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// CONSTANTS

#define MEM_MAX_SIZE 64 * 1024
#define HIGH_STACK_ADDRESS 0x001

// INSTRUCTIONS
#define ADC 0x69
#define BCC 0x90
#define BCS 0xB0
#define BEQ 0xF0
#define BMI 0x30
#define BNE 0xD0
#define BPL 0x10
#define BRK 0x00
#define BVC 0x50
#define BVS 0x70
#define CLC 0x18
#define CLD 0xD8
#define CLI 0x58
#define CLV 0xB8
#define CMP 0xC9
#define CPX 0xE0
#define CPY 0xC0
#define DEC 0xC6
#define DEX 0xCA
#define DEY 0x88
#define EOR 0x49
#define INC 0xE6
#define INX 0xE8
#define INY 0xC8
#define JMP 0x4C
#define JSR 0x20

// LDA instructions
#define LDA_IMM 0xA9 // 2 Cycles
#define LDA_ABS 0xAD // 4 Cycles
#define LDA_ABS_X 0xBD // 4 Cycles + 1 if page crossed
#define LDA_ABS_Y 0xB9 // 4 Cycles + 1 if page crossed
#define LDA_ZP 0xA5 // 3 Cycles
#define LDA_ZP_X 0xB5 // 4 Cycles
#define LDA_ZP_X_IND 0xA1 // 6 Cycles
#define LDA_ZP_Y_IND 0xB1 // 5 Cycles + 1 if page crossed

// LDX instructions
#define LDX_IMM 0xA2 // 2 Cycles
#define LDX_ABS 0xAE // 4 Cycles
#define LDX_ABS_Y 0xBE // 4 Cycles + 1 if page crossed
#define LDX_ZP 0xA6 // 3 Cycles
#define LDX_ZP_Y 0xB6 // 4 Cycles

// LDY instructions
#define LDY_IMM 0xA0 // 2 Cycles
#define LDY_ABS 0xAC // 4 Cycles
#define LDY_ABS_X 0xBC // 4 Cycles + 1 if page crossed
#define LDY_ZP 0xA4 // 3 Cycles
#define LDY_ZP_X 0xB4 // 4 Cycles

/// STA instructions
#define STA_ABS 0x8D // 4 Cycles
#define STA_ZP 0x85 // 3 Cycles
#define STA_ZP_X 0x95 // 4 Cycles
#define STA_ABS_X 0x9D // 5 Cycles
#define STA_ABS_Y 0x99 // 5 Cycles
#define STA_ZP_X_IND 0x81 // 6 Cycles
#define STA_ZP_Y_IND 0x91 // 6 Cycles

// STX instructions
#define STX_ABS 0x8E // 4 Cycles
#define STX_ZP 0x86 // 3 Cycles
#define STX_ZP_Y 0x96 // 4 Cycles

// STY instructions
#define STY_ABS 0x8C // 4 Cycles
#define STY_ZP 0x84 // 3 Cycles
#define STY_ZP_X 0x94 // 4 Cycles

// Transfer instructions
#define TAX 0xAA // 2 Cycles
#define TAY 0xA8 // 2 Cycles
#define TSX 0xBA // 2 Cycles
#define TXA 0x8A // 2 Cycles
#define TXS 0x9A // 2 Cycles 
#define TYA 0x98 // 2 Cycles

// Stack instructions
#define PHA 0x48 // 3 Cycles
#define PHP 0x08 // 3 Cycles
#define PLA 0x68 // 4 Cycles
#define PLP 0x28 // 4 Cycles

// ASL instructions
#define ASL_A 0x0A // 2 Cycles
#define ASL_ABS 0x0E // 6 Cycles
#define ASL_ABS_X 0x1E // 7 Cycles
#define ASL_ZP 0x06 // 5 Cycles
#define ASL_ZP_X 0x16 // 6 Cycles

// LSR instructions
#define LSR_A 0x4A // 2 Cycles
#define LSR_ABS 0x4E // 6 Cycles
#define LSR_ABS_X 0x5E // 7 Cycles
#define LSR_ZP 0x46 // 5 Cycles
#define LSR_ZP_X 0x56 // 6 Cycles

// ROL instructions
#define ROL_A 0x2A // 2 Cycles
#define ROL_ABS 0x2E // 6 Cycles
#define ROL_ABS_X 0x3E // 7 Cycles
#define ROL_ZP 0x26 // 5 Cycles
#define ROL_ZP_X 0x36 // 6 Cycles

// ROR instructions
#define ROR_A 0x6A // 2 Cycles
#define ROR_ABS 0x6E // 6 Cycles
#define ROR_ABS_X 0x7E // 7 Cycles
#define ROR_ZP 0x66 // 5 Cycles
#define ROR_ZP_X 0x76 // 6 Cycles

// AND instructions
#define AND_IMM 0x29 // 2 Cycles
#define AND_ABS 0x2D // 4 Cycles
#define AND_ABS_X 0x3D // 4 Cycles + 1 if page crossed
#define AND_ABS_Y 0x39 // 4 Cycles + 1 if page crossed
#define AND_ZP 0x25 // 3 Cycles
#define AND_ZP_X 0x35 // 4 Cycles
#define AND_ZP_X_IND 0x21 // 6 Cycles
#define AND_ZP_Y_IND 0x31 // 5 Cycles + 1 if page crossed

// BIT instructions
#define BIT_ABS 0x2C // 4 Cycles
#define BIT_ZP 0x24 // 3 Cycles

#define LDY 0xA0
#define NOP 0xEA
#define ORA 0x09
#define RTI 0x40
#define RTS 0x60
#define SBC 0xE9
#define SEC 0x38
#define SED 0xF8
#define SEI 0x78
#define STX 0x86
#define STY 0x84

// MEMORY PAGES
// 0x0000 - 0x00FF: Zero Page
// 0x0100 - 0x01FF: Stack
// 0x0200 - 0x07FF: RAM
// 0x0800 - 0x1FFF: Mirrors of 0x0000 - 0x07FF
// 0x2000 - 0x2007: PPU Registers
// 0x2008 - 0x3FFF: Mirrors of 0x2000 - 0x2007
// 0x4000 - 0x4017: APU and I/O Registers
// 0x4018 - 0x401F: APU and I/O functionality that is normally disabled
// 0x4020 - 0xFFFF: Cartridge space: PRG ROM, PRG RAM, and mapper registers

struct VirtualMachine{
    unsigned short ip; // Pointer pointing to the instructions (high byte)
    
    // Registers
    unsigned char accumulator; // Accumulator register
    unsigned char x; // X register
    unsigned char y; // Y register
    unsigned char processor_status; // Processor status register
    
    // Stack
    unsigned char sp; // Stack pointer
    
};

struct Memory{
    unsigned char data[MEM_MAX_SIZE];
};

extern struct VirtualMachine vm;
extern struct Memory memory;

// fetch functions
void fetch_word(unsigned int *cycles, unsigned char *low_byte, unsigned char *high_byte);
unsigned char fetch_byte(unsigned int *cycles);

// main execution function
void execute(unsigned int *cycles);

// zeropage-related functions
void zp_wrapping(unsigned int* cycles, unsigned short* address, unsigned char vm_register);
void fetch_word_zp(unsigned int* cycles, unsigned short address, unsigned char* low_byte, unsigned char* high_byte);

// helper functions
void debug(unsigned char instruction, unsigned char component);
void cycle_check(unsigned int cycle_amount, unsigned int* cycles);
bool out_of_bounds(unsigned short address);
void wrap_address(unsigned short* address);
void onebyte_ins_fix(unsigned int* cycles); // Function for fixing the cycle count and the instruction pointer for one byte instructions

unsigned short get_abs_address(unsigned int* cycles, unsigned char low_order_address);
unsigned short get_zp_address(unsigned char low_order_address);

#endif