#ifndef uz_pmsm_model_9ph_HW_H
#define uz_pmsm_model_9ph_HW_H

#include <stdint.h>
#include <stdbool.h>

// Inputs general
void uz_pmsm_model_9ph_hw_write_load_torque(uint32_t base_address, float load_torque);
void uz_pmsm_model_9ph_hw_write_omega_mech(uint32_t base_address, float omega_mech);
void uz_pmsm_model_9ph_hw_write_u_d(uint32_t base_address, float u_d);
void uz_pmsm_model_9ph_hw_write_u_q(uint32_t base_address, float u_q);

// Outputs general
float uz_pmsm_model_9ph_hw_read_torque(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_omega_mech(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_theta_el(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_u_d(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_u_q(uint32_t base_address);

// Outputs currents dq
float uz_pmsm_model_9ph_hw_read_i_d(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_q(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_z1(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_z2(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_x1(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_y1(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_x2(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_y2(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_z3(uint32_t base_address);

// Model parameter
void uz_pmsm_model_9ph_hw_write_reset(uint32_t base_address, bool reset);
void uz_pmsm_model_9ph_hw_write_simulate_mechanical(uint32_t base_address, bool simulate_mechanical);
void uz_pmsm_model_9ph_hw_write_switch_pspl(uint32_t base_address, bool switch_pspl);
void uz_pmsm_model_9ph_hw_write_control_dq_abc(uint32_t base_address, bool control_dq);

// Physical parameter
void uz_pmsm_model_9ph_hw_write_inertia(uint32_t base_address, float intertia);
void uz_pmsm_model_9ph_hw_write_friction_coefficient(uint32_t base_address, float mu);
void uz_pmsm_model_9ph_hw_write_coulomb_friction_constant(uint32_t base_address, float m_c);

void uz_pmsm_model_9ph_hw_write_L_d(uint32_t base_address, float L_d);
void uz_pmsm_model_9ph_hw_write_L_q(uint32_t base_address, float L_q);
void uz_pmsm_model_9ph_hw_write_r_1(uint32_t base_address, float r_1);
void uz_pmsm_model_9ph_hw_write_polepairs(uint32_t base_address, float polepairs);
void uz_pmsm_model_9ph_hw_write_psi_pm(uint32_t base_address, float psi_pm);

void uz_pmsm_model_9ph_hw_write_L_z1(uint32_t base_address, float inductance);
void uz_pmsm_model_9ph_hw_write_L_z2(uint32_t base_address, float inductance);
void uz_pmsm_model_9ph_hw_write_L_x1(uint32_t base_address, float inductance);
void uz_pmsm_model_9ph_hw_write_L_y1(uint32_t base_address, float inductance);
void uz_pmsm_model_9ph_hw_write_L_x2(uint32_t base_address, float inductance);
void uz_pmsm_model_9ph_hw_write_L_y2(uint32_t base_address, float inductance);
void uz_pmsm_model_9ph_hw_write_L_z3(uint32_t base_address, float inductance);

// Strobe
void uz_pmsm_model_9ph_hw_trigger_output_general_strobe(uint32_t base_address);
void uz_pmsm_model_9ph_hw_trigger_output_currents_dq_strobe(uint32_t base_address);
void uz_pmsm_model_9ph_hw_trigger_input_general_strobe(uint32_t base_address);
#endif // uz_pmsm_model_9ph_HW_H
