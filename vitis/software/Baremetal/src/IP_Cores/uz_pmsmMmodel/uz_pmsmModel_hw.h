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
void uz_pmsmModel_hw_trigger_fitting_parameters_strobe(uint32_t base_address);

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


// Fitting Parameters
void uz_pmsmModel_hw_write_ad1(uint32_t base_address, float ad1);
void uz_pmsmModel_hw_write_ad2(uint32_t base_address, float ad2);
void uz_pmsmModel_hw_write_ad3(uint32_t base_address, float ad3);
void uz_pmsmModel_hw_write_ad4(uint32_t base_address, float ad4);
void uz_pmsmModel_hw_write_ad5(uint32_t base_address, float ad5);
void uz_pmsmModel_hw_write_ad6(uint32_t base_address, float ad6);
void uz_pmsmModel_hw_write_aq(uint32_t base_address, float aq1, float aq2, float aq3, float aq4, float aq5, float aq6);
void uz_pmsmModel_hw_write_fitting_parameters(uint32_t base_address, float reciprocal_F1G1, float reciprocal_F2G2, float ad4_mul_ad5, float ad1_mul_ad2, float aq4_mul_aq5, float aq1_mul_aq2, float aq4_div_aq5, float aq1_div_aq2, float ad4_div_ad5, float ad1_div_ad2, float aq3_min_aq6);


// Determine if omega mech is a input or the mechanical system is simulated with a simple friction model
void uz_pmsmModel_hw_write_simulate_mechanical(uint32_t base_address, bool simulate_mechanical);
void uz_pmsmModel_hw_write_simulate_nonlinear(uint32_t base_address, bool simulate_nonlinear);

// Reset
void uz_pmsmModel_hw_write_reset(uint32_t base_address, bool reset);
#endif // UZ_PMSMMODEL_HW_H
