#ifndef SHIFT_INSTRUCTIONS_H
#define SHIFT_INSTRUCTIONS_H

void shift_acc_logic(unsigned char instruction);
void shift_abs_logic(unsigned char low_order_address, unsigned char instruction);
void shift_abs_x_logic(unsigned char low_order_address, unsigned char instruction);
void shift_zp_logic(unsigned char low_order_address, unsigned char instruction);
void shift_zp_x_logic(unsigned char low_order_address, unsigned char instruction);

void rotate_acc_logic(unsigned char instruction);
void rotate_abs_logic(unsigned char low_order_address, unsigned char instruction);
void rotate_abs_x_logic(unsigned char low_order_address, unsigned char instruction);
void rotate_zp_logic(unsigned char low_order_address, unsigned char instruction);
void rotate_zp_x_logic(unsigned char low_order_address, unsigned char instruction);

void rotate_logic(unsigned char* value, bool isLeft);

#endif