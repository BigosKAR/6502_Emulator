#ifndef LOGIC_INSTRUCTIONS_H
#define LOGIC_INSTRUCTIONS_H

void and_imm(unsigned int* cycles, unsigned char low_byte, unsigned char instruction);
void and_abs(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction);

#endif