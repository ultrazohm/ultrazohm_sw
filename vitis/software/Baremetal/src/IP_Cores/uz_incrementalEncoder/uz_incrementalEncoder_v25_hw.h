#ifndef UZ_INCREMENTALENCODER_v25_HW_H
#define UZ_INCREMENTALENCODER_v25_HW_H
#include <stdint.h>
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_AXI.h"

void uz_incrementalEncoder_hw_set_speed_timeout(uint32_t base_address,uint32_t speed_timeout);
void uz_incrementalEncoder_hw_reset_ip_core(uint32_t base_address);

float uz_incrementalEncoder_hw_get_omega_oversampled_N4(uint32_t base_address);
float uz_incrementalEncoder_hw_get_omega_oversampled_N8(uint32_t base_address);

float uz_incrementalEncoder_hw_get_NOTB(uint32_t base_address);
float uz_incrementalEncoder_hw_get_NOTA(uint32_t base_address);
float uz_incrementalEncoder_hw_get_A(uint32_t base_address);
float uz_incrementalEncoder_hw_get_B(uint32_t base_address);

#endif // UZ_INCREMENTALENCODER_HW_H
