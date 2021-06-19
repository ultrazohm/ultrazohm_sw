#ifndef UZ_PMSMMODEL_HW_H
#define UZ_PMSMMODEL_HW_H

#include <stdint.h>
#include <stdbool.h>

// Read
float uz_pmsmModel_hw_read_torque(uint32_t base_address);
float uz_pmsmModel_hw_read_i_q(uint32_t base_address);
float uz_pmsmModel_hw_read_i_d(uint32_t base_address);

// Write
void uz_pmsmModel_hw_write_omega_mech(uint32_t base_address, float omega_mech);
void uz_pmsmModel_hw_write_u_q(uint32_t base_address, float u_d);
void uz_pmsmModel_hw_write_u_d(uint32_t base_address, float u_q);
// Reset
void uz_pmsmModel_hw_write_reset(uint32_t base_address, bool reset);
#endif // UZ_PMSMMODEL_HW_H
