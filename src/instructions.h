#include <stdio.h>

// FLAGS

#define FLAG_CARRY 0x00
#define FLAG_ZERO 0x01
#define FLAG_INTERRUPT 0x04
#define FLAG_DECIMAL 0X08
#define FLAG_BREAK 0x10
#define UNUSED_FLAG 0x20
#define FLAG_OVERFLOW 0x40
#define FLAG_NEGATIVE 0x80

// CONSTANTS

#define MEM_MAX_SIZE 64 * 1024
#define HIGH_STACK_ADDRESS 0x001

// INSTRUCTIONS
#define ADC 0x69
#define AND 0x29
#define ASL 0x0A
#define BCC 0x90
#define BCS 0xB0
#define BEQ 0xF0
#define BIT 0x24
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
#define LDA 0xA9
#define LDX 0xA2
#define LDY 0xA0
#define LSR 0x4A
#define NOP 0xEA
#define ORA 0x09
#define PHA 0x48
#define PHP 0x08
#define PLA 0x68
#define PLP 0x28
#define ROL 0x2A
#define ROR 0x6A
#define RTI 0x40
#define RTS 0x60
#define SBC 0xE9
#define SEC 0x38
#define SED 0xF8
#define SEI 0x78
#define STA 0x85
#define STX 0x86
#define STY 0x84
#define TAX 0xAA
#define TAY 0xA8
#define TSX 0xBA
#define TXA 0x8A
#define TXS 0x9A
#define TYA 0x98


struct {
    unsigned short *ip; // Pointer pointing to the instructions (high byte)
    
    // Registers
    unsigned char accumulator; // Accumulator register
    unsigned char x; // X register
    unsigned char y; // Y register
    unsigned char processor_status; // Processor status register
    
    // Stack
    unsigned char *sp; // Stack pointer
    
}vm;

struct{
    unsigned char data[MEM_MAX_SIZE];
}memory;

unsigned char fetch(unsigned int *cycles, unsigned char *low_byte, unsigned char *high_byte);
void execute(unsigned int *cycles);
