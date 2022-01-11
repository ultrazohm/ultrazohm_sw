#ifndef UZ_RESOLVERIP_HW_H
#define UZ_RESOLVERIP_HW_H

#include <stdint.h>

void uz_resolverIP_hw_write_A(uint32_t base_address,int32_t A);

void uz_resolverIP_hw_write_B(uint32_t base_address,int32_t B);

int32_t uz_resolverIP_hw_read_C(uint32_t base_address);

#endif // UZ_RESOLVERIP_HW_H
