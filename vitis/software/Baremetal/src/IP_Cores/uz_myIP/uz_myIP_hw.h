#ifndef UZ_MYIP_HW_H
#define UZ_MYIP_HW_H

#include <stdint.h>
void uz_myIP_hw_write_A(uint32_t base_address,int32_t A);
void uz_myIP_hw_write_B(uint32_t base_address,int32_t B);
int32_t uz_myIP_hw_read_C(uint32_t base_address);

void uz_myIP_hw_write_A_uint(uint32_t base_address,uint32_t A);
void uz_myIP_hw_write_B_uint(uint32_t base_address,uint32_t B);
uint32_t uz_myIP_hw_read_C_uint(uint32_t base_address);

#endif // UZ_MYIP_HW_H
