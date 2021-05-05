#ifndef UZ_MYIP_HW_H
#define UZ_MYIP_HW_H
#include <stdint.h>

void uz_myIP2_hw_write_A(uint32_t base_address,int32_t A);
void uz_myIP2_hw_write_B(uint32_t base_address,int32_t B);
int32_t uz_myIP2_hw_read_C(uint32_t base_address);

#endif // UZ_MYIP_HW_H
