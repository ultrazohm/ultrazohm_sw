#ifndef UZ_PMSMMODEL_HW_H
#define UZ_PMSMMODEL_HW_H

#include <stdint.h>
#include <stdbool.h>

// Model Outputs
float uz_pmsmModel_hw_read_torque(uint32_t base_address);
float uz_pmsmModel_hw_read_i_q(uint32_t base_address);
float uz_pmsmModel_hw_read_i_d(uint32_t base_address);
float uz_pmsmModel_hw_read_omega_mech(uint32_t base_address);

// Model Inputs
void uz_pmsmModel_hw_write_omega_mech(uint32_t base_address, float omega_mech);
void uz_pmsmModel_hw_write_v_q(uint32_t base_address, float v_d);
void uz_pmsmModel_hw_write_v_d(uint32_t base_address, float v_q);
void uz_pmsmModel_hw_write_load_torque(uint32_t base_address, float load_torque);

// Strobes
void uz_pmsmModel_hw_trigger_input_strobe(uint32_t base_address);
void uz_pmsmModel_hw_trigger_output_strobe(uint32_t base_address);

// Electrical configuration parameters
void uz_pmsmModel_hw_write_polepairs(uint32_t base_address, float polepairs);
void uz_pmsmModel_hw_write_r_1(uint32_t base_address, float r_1);
void uz_pmsmModel_hw_write_psi_pm(uint32_t base_address, float psi_pm);
void uz_pmsmModel_hw_write_L_d(uint32_t base_address,float L_d);
void uz_pmsmModel_hw_write_L_q(uint32_t base_address, float L_q);

// Mechanical configuration parameters
void uz_pmsmModel_hw_write_friction_coefficient(uint32_t base_address, float mu);
void uz_pmsmModel_hw_write_coulomb_friction_constant(uint32_t base_address, float m_c);
void uz_pmsmModel_hw_write_inertia(uint32_t base_address, float intertia);

// Determine if omega mech is a input or the mechanical system is simulated with a simple friction model
void uz_pmsmModel_hw_write_simulate_mechanical(uint32_t base_address, bool simulate_mechanical);

// Reset
void uz_pmsmModel_hw_write_reset(uint32_t base_address, bool reset);
#endif // UZ_PMSMMODEL_HW_H
