#ifndef UZ_INCREMENTALENCODER_HW_H
#define UZ_INCREMENTALENCODER_HW_H
#include <stdint.h>
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_AXI.h"

void uz_incrementalEncoder_hw_set_timer_fpga_ms(uint32_t base_address, uint32_t timer_ms);
void uz_incrementalEncoder_hw_set_pi2_inc(uint32_t base_address, uint32_t pi2_inc);


#endif // UZ_INCREMENTALENCODER_HW_H
