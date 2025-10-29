#ifndef UZ_DUTYCYCLEMEAS_H
#define UZ_DUTYCYCLEMEAS_H
#include <stdint.h>

uint32_t uz_DutyCycleMeas_hw_get_PWMperiodTicks(uint32_t base_address);
uint32_t uz_DutyCycleMeas_hw_get_PWMhightimeTicks(uint32_t base_address);
uint32_t uz_DutyCycleMeas_hw_get_PWMlowtimeTicks(uint32_t base_address);
float uz_DutyCycleMeas_hw_get_DutyCycle(uint32_t base_address);

#endif // UZ_DUTYCYCLEMEAS_H
