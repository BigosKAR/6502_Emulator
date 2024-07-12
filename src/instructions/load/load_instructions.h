#ifndef LOAD_INSTRUCTIONS_H
#define LOAD_INSTRUCTIONS_H

void ld_abs_reg_logic(unsigned int* cycles, unsigned char* low_order_address, unsigned char* vm_register, unsigned char vm_reg_indexed, unsigned char instruction);
void ld_imm_logic(unsigned int* cycles, unsigned char* low_byte, unsigned char *vm_register, unsigned char instruction);
void ld_abs_logic(unsigned int* cycles, unsigned char* low_order_address, unsigned char* vm_register, unsigned char instruction);
void ld_zp_logic(unsigned int* cycles, unsigned char* low_byte, unsigned char* vm_register, unsigned char instruction);
void ld_zp_reg_logic(unsigned int* cycles, unsigned char* low_byte, unsigned char* vm_register, unsigned char vm_reg_indexed, unsigned char instruction);
void lda_zp_x_ind(unsigned int* cycles, unsigned char* low_byte);
void lda_zp_y_ind(unsigned int* cycles, unsigned char* low_byte);

void st_abs_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_register, unsigned char instruction);
void st_zp_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_register, unsigned char instruction);
void st_zp_reg_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_register, unsigned char vm_reg_indexed, unsigned char instruction);
void sta_abs_reg_logic(unsigned int* cycles, unsigned char low_order_address, unsigned char vm_reg_indexed, unsigned char instruction);
void sta_zp_x_ind(unsigned int* cycles, unsigned char low_byte);
void sta_zp_y_ind(unsigned int* cycles, unsigned char low_byte);

#endif