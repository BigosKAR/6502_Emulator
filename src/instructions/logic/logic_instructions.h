#ifndef LOGIC_INSTRUCTIONS_H
#define LOGIC_INSTRUCTIONS_H

void and_imm(unsigned int* cycles, unsigned char low_byte, unsigned char instruction);
void and_abs(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction);
void and_abs_reg_logic(unsigned int* cycles, unsigned low_order_address, unsigned char vm_register, unsigned char instruction);
void and_zp(unsigned int* cycles, unsigned char low_byte, unsigned char instruction);
void and_zp_x(unsigned int* cycles, unsigned char low_byte, unsigned char instruction);
void and_zp_x_ind(unsigned int* cycles, unsigned char low_byte, unsigned char instruction);
void and_zp_y_ind(unsigned int* cycles, unsigned char low_byte, unsigned char instruction);

void and_bitwise_logic(unsigned char value);

#endif