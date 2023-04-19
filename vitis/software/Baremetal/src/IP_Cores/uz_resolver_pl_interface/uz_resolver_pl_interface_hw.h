#ifndef UZ_RESOLVER_PL_INTERFACE_HW_H
#define UZ_RESOLVER_PL_INTERFACE_HW_H
#include <stdint.h>
#include <stdbool.h>

void uz_resolver_pl_interface_hw_write_resolver_polepairs(uint32_t base_address, int32_t resolver_polepairs);
void uz_resolver_pl_interface_hw_write_cnt_reset(uint32_t base_address, bool reset);
void uz_resolver_pl_interface_hw_write_position_intmax(uint32_t base_address, int32_t intmax);
void uz_resolver_pl_interface_hw_write_machine_polepairs(uint32_t base_address, int32_t machine_polepairs);
void uz_resolver_pl_interface_hw_write_bitToRPS_factor(uint32_t base_address, float bitToRPS_factor);
void uz_resolver_pl_interface_hw_write_theta_m_offset_rad(uint32_t base_address, float theta_m_offset_rad);

#endif // UZ_RESOLVER_PL_INTERFACE_HW_H
