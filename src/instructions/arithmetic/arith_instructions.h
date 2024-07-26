#ifndef ARITH_INSTRUCTIONS_H
#define ARITH_INSTRUCTIONS_H

#include "../../addressing_modes.h"

void adc_imm(unsigned char low_byte, unsigned char instruction);
void adc_abs(unsigned low_order_address, unsigned char instruction);
void adc_abs_reg_logic(unsigned low_order_address, unsigned char vm_register, unsigned char instruction);
void adc_zp(unsigned low_order_address, unsigned char instruction);
void adc_zp_x(unsigned low_order_address, unsigned char instruction);
void adc_zp_x_ind(unsigned char low_order_address, unsigned char instruction);
void adc_zp_y_ind(unsigned char low_order_address, unsigned char instruction);

void cm_imm_logic(unsigned char low_byte, unsigned char vm_register, unsigned char instruction);
void cm_instruction(unsigned int cycles_required, AddressingModes mode, unsigned char low_order_address, unsigned char vm_register, unsigned char index_register, unsigned char instruction);

void compare_logic(unsigned char vm_register, unsigned char memory_value);
void adc_logic(unsigned char char_value);

#endif