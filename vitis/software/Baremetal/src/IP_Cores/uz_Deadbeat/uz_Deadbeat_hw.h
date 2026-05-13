
#ifndef UZ_DEADBEAT_HW_H
#define UZ_DEADBEAT_HW_H

#include <stdint.h>

void uz_Deadbeat_hw_write_id_ref(uint32_t base_address, int32_t id_ref);
void uz_Deadbeat_hw_write_iq_ref(uint32_t base_address, int32_t iq_ref);
void uz_Deadbeat_hw_write_id(uint32_t base_address, int32_t id);
void uz_Deadbeat_hw_write_iq(uint32_t base_address, int32_t iq);
void uz_Deadbeat_hw_write_theta(uint32_t base_address, int32_t theta);
void uz_Deadbeat_hw_write_theta_0(uint32_t base_address, int32_t theta_0);
void uz_Deadbeat_hw_write_w_e(uint32_t base_address, int32_t w_e);
void uz_Deadbeat_hw_write_ua_0(uint32_t base_address, int32_t ua_0);
void uz_Deadbeat_hw_write_ub_0(uint32_t base_address, int32_t ub_0);
void uz_Deadbeat_hw_write_uc_0(uint32_t base_address, int32_t uc_0);

int32_t uz_Deadbeat_hw_read_ua_0(uint32_t base_address);
int32_t uz_Deadbeat_hw_read_ub_o(uint32_t base_address);
int32_t uz_Deadbeat_hw_read_uc_0(uint32_t base_address);

#endif // UZ_DEADBEAT_HW_H
