#ifndef LOGIC_INSTRUCTIONS_H
#define LOGIC_INSTRUCTIONS_H

void logical_imm(unsigned char low_byte, unsigned char instruction);
void logical_abs(unsigned char low_order_address, unsigned char instruction);
void logical_abs_reg_logic(unsigned low_order_address, unsigned char vm_register, unsigned char instruction);
void logical_zp(unsigned char low_byte, unsigned char instruction);
void logical_zp_x(unsigned char low_byte, unsigned char instruction);
void logical_zp_x_ind(unsigned char low_byte, unsigned char instruction);
void logical_zp_y_ind(unsigned char low_byte, unsigned char instruction);

void bit_abs(unsigned char low_order_address, unsigned char instruction);
void bit_zp(unsigned char low_order_address, unsigned char instruction);

void and_bitwise_logic(unsigned char value);
void eor_bitwise_logic(unsigned char value);
void ora_bitwise_logic(unsigned char value);
#endif