#ifndef UZ_AXI_MYTESTIP_HW_H
#define UZ_AXI_MYTESTIP_HW_H
#include <stdint.h>

void uz_axi_myTestIP_hw_write_A(uint32_t base_address,int32_t A);
void uz_axi_myTestIP_hw_write_B(uint32_t base_address,int32_t B);
int32_t uz_axi_myTestIP_hw_read_result(uint32_t base_address);

#endif // UZ_AXI_MYTESTIP_HW_H