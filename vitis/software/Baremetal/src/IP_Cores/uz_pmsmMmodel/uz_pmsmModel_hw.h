#ifndef UZ_PMSMMODEL_HW_H
#define UZ_PMSMMODEL_HW_H

#include <stdint.h>
#include <stdbool.h>

float uz_pmsmModel_hw_read_torque(uint32_t base_address);
float uz_pmsmModel_hw_read_i_q(uint32_t base_address);
float uz_pmsmModel_hw_read_i_d(uint32_t base_address);
void uz_pmsmModel_hw_write_reset(uint32_t base_address, bool reset);
void uz_pmsmModel_hw_write_omega_mech(uint32_t base_address, float omega_mech);
#endif // UZ_PMSMMODEL_HW_H
