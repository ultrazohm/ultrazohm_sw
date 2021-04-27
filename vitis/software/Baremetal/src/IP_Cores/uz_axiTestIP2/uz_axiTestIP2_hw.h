#ifndef UZ_AXITESTIP2_HW_H
#define UZ_AXITESTIP2_HW_H

#include <stdint.h>
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_AXI.h"
#include "uz_axiTestIP2_hwAddresses.h"

void uz_axiTestIP2_hw_write_A_int32(uint32_t base_address, int32_t A);
void uz_axiTestIP2_hw_write_B_int32(uint32_t base_address, int32_t B);
int32_t uz_axiTestIP2_hw_read_C_int32(uint32_t base_address);

#endif // UZ_AXITESTIP2_HW_H
