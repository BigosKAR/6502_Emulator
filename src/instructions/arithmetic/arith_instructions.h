#ifndef ARITH_INSTRUCTIONS_H
#define ARITH_INSTRUCTIONS_H

void adc_imm(unsigned int* cycles, unsigned char low_byte, unsigned char instruction);
void adc_abs(unsigned int* cycles, unsigned low_order_address, unsigned char instruction);
void adc_abs_reg_logic(unsigned int* cycles, unsigned low_order_address, unsigned char vm_register, unsigned char instruction);
void adc_zp(unsigned int* cycles, unsigned low_order_address, unsigned char instruction);
void adc_zp_x(unsigned int* cycles, unsigned low_order_address, unsigned char instruction);
void adc_zp_x_ind(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction);
void adc_zp_y_ind(unsigned int* cycles, unsigned char low_order_address, unsigned char instruction);

void adc_logic(unsigned char char_value);

#endif