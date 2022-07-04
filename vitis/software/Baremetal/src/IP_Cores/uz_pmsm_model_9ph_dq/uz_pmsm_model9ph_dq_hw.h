#ifndef UZ_PMSM_MODEL9PH_DQ_HW_H
#define UZ_PMSM_MODEL9PH_DQ_HW_H
#include <stdbool.h>
#include <stdint.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"

// Model settings
void uz_pmsm_model9ph_hw_write_reset(uint32_t base_address, bool reset);
void uz_pmsm_model9ph_hw_write_simulate_mechanical(uint32_t base_address, bool simulate_mechanical);
void uz_pmsm_model9ph_hw_write_switch_pspl(uint32_t base_address, bool switch_pspl);

// General inputs
void uz_pmsm_model9ph_hw_write_load_torque(uint32_t base_address, float load_torque);
void uz_pmsm_model9ph_hw_write_omega_mech(uint32_t base_address, float omega_mech);

// General outputs
float uz_pmsm_model9ph_hw_read_torque(uint32_t base_address);
float uz_pmsm_model9ph_hw_read_omega_mech(uint32_t base_address);
float uz_pmsm_model9ph_hw_read_theta_el(uint32_t base_address);

// Voltage input

// Current and voltage output


// Physical parameter
void uz_pmsm_model9ph_hw_write_inertia(uint32_t base_address, float intertia);
void uz_pmsm_model9ph_hw_write_friction_coefficient(uint32_t base_address, float mu);
void uz_pmsm_model9ph_hw_write_coulomb_friction_constant(uint32_t base_address, float m_c);
void uz_pmsm_model9ph_hw_write_L_d(uint32_t base_address, float inductance);
void uz_pmsm_model9ph_hw_write_L_q(uint32_t base_address, float inductance);
void uz_pmsm_model9ph_hw_write_r_1(uint32_t base_address, float r_1);
void uz_pmsm_model9ph_hw_write_polepairs(uint32_t base_address, float polepairs);
void uz_pmsm_model9ph_hw_write_psi_pm(uint32_t base_address, float psi_pm);
void uz_pmsm_model9ph_hw_write_L_x1(uint32_t base_address, float inductance);
void uz_pmsm_model9ph_hw_write_L_y1(uint32_t base_address, float inductance);
void uz_pmsm_model9ph_hw_write_L_x2(uint32_t base_address, float inductance);
void uz_pmsm_model9ph_hw_write_L_y2(uint32_t base_address, float inductance);
void uz_pmsm_model9ph_hw_write_L_x3(uint32_t base_address, float inductance);
void uz_pmsm_model9ph_hw_write_L_y3(uint32_t base_address, float inductance);
void uz_pmsm_model9ph_hw_write_L_zero(uint32_t base_address, float inductance);

// read and write voltage and currents
//void uz_pmsm_model9ph_hw_write_voltage_dq(uint32_t base_address, uz_9ph_dq_t phase_voltage);
//uz_9ph_dq_t uz_pmsm_model9ph_hw_read_voltage_dq(uint32_t base_address);
//uz_9ph_dq_t uz_pmsm_model9ph_hw_read_currents_dq(uint32_t base_address);

#endif // uz_pmsm_model9ph_dq_H