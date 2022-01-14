#ifndef UZ_RESOLVERIP_HW_H
#define UZ_RESOLVERIP_HW_H

#include <stdint.h>

#define  RESCON_Data_uz_axi_EN_bit        1 << 0
#define  RESCON_Data_uz_axi_GO_bit        1 << 1
#define  RESCON_Data_uz_axi_BUSY_bit      1 << 2
#define  RESCON_Data_uz_axi_ERROR_bit     1 << 3
#define  RESCON_Data_uz_axi_DMODE_bit     1 << 4
#define  RESCON_Data_uz_axi_CMODE_bit     1 << 5
#define  RESCON_Data_uz_axi_RW_bit        1 << 6
#define  RESCON_Data_uz_axi_nRESET_bit    1 << 7

void uz_resolverIP_hw_write_A(uint32_t base_address,int32_t A);

void uz_resolverIP_hw_write_B(uint32_t base_address,int32_t B);

int32_t uz_resolverIP_hw_read_C(uint32_t base_address);

void uz_resolverIP_hw_write_RESCON(uint32_t base_address, int32_t val);
void uz_resolverIP_hw_write_RESDAT(uint32_t base_address, int32_t val);
void uz_resolverIP_hw_write_RESADR(uint32_t base_address, int32_t val);

int32_t uz_resolverIP_hw_read_RESCON(uint32_t base_address);
int32_t uz_resolverIP_hw_read_RESDAT(uint32_t base_address);
int32_t uz_resolverIP_hw_read_RESADR(uint32_t base_address);
int32_t uz_resolverIP_hw_read_RESRDA(uint32_t base_address);

#endif // UZ_RESOLVERIP_HW_H
