#ifndef UZ_INVERTER_STATUS_H
#define UZ_INVERTER_STATUS_H
#include <stdint.h>

uint32_t uz_inverter_status_hw_get_RDY(uint32_t base_address);
uint32_t uz_inverter_status_hw_get_FLT(uint32_t base_address);
void uz_inverter_status_hw_set_GateDriverEnable(uint32_t base_address, uint8_t GateDriverEnable, uint8_t useFLTlogic);

#endif // UZ_INVERTER_STATUS_H
