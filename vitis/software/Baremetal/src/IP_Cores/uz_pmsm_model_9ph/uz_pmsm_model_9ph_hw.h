#ifndef uz_pmsm_model_9ph_HW_H
#define uz_pmsm_model_9ph_HW_H

#include <stdint.h>
#include <stdbool.h>

// Inputs general
void uz_pmsm_model_9ph_hw_write_load_torque(uint32_t base_address, float load_torque);
void uz_pmsm_model_9ph_hw_write_omega_mech(uint32_t base_address, float omega_mech);

// Outputs general
float uz_pmsm_model_9ph_hw_read_i_d(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_q(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_torque(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_omega_mech(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_theta_el(uint32_t base_address);

// Outputs currents dq
float uz_pmsm_model_9ph_hw_read_i_d_outdq(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_q_outdq(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_o1(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_o2(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_x1(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_y1(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_x2(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_y2(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_zero(uint32_t base_address);

// Outputs currents abc
float uz_pmsm_model_9ph_hw_read_i_a1(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_b1(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_c1(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_a2(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_b2(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_c2(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_a3(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_b3(uint32_t base_address);
float uz_pmsm_model_9ph_hw_read_i_c3(uint32_t base_address);

// Inputs voltages dq
void uz_pmsm_model_9ph_hw_write_u_q(uint32_t base_address, float u_q);
void uz_pmsm_model_9ph_hw_write_u_d(uint32_t base_address, float u_d);
void uz_pmsm_model_9ph_hw_write_u_o1(uint32_t base_address, float u_o1);
void uz_pmsm_model_9ph_hw_write_u_o2(uint32_t base_address, float u_o2);
void uz_pmsm_model_9ph_hw_write_u_x1(uint32_t base_address, float u_x1);
void uz_pmsm_model_9ph_hw_write_u_y1(uint32_t base_address, float u_y1);
void uz_pmsm_model_9ph_hw_write_u_x2(uint32_t base_address, float u_x2);
void uz_pmsm_model_9ph_hw_write_u_y2(uint32_t base_address, float u_y2);
void uz_pmsm_model_9ph_hw_write_u_zero(uint32_t base_address, float u_zero);

// Inputs voltages abc
void uz_pmsm_model_9ph_hw_write_u_a1(uint32_t base_address, float u_a1);
void uz_pmsm_model_9ph_hw_write_u_b1(uint32_t base_address, float u_b1);
void uz_pmsm_model_9ph_hw_write_u_c1(uint32_t base_address, float u_c1);
void uz_pmsm_model_9ph_hw_write_u_a2(uint32_t base_address, float u_a2);
void uz_pmsm_model_9ph_hw_write_u_b2(uint32_t base_address, float u_b2);
void uz_pmsm_model_9ph_hw_write_u_c2(uint32_t base_address, float u_c2);
void uz_pmsm_model_9ph_hw_write_u_a3(uint32_t base_address, float u_a3);
void uz_pmsm_model_9ph_hw_write_u_b3(uint32_t base_address, float u_b3);
void uz_pmsm_model_9ph_hw_write_u_c3(uint32_t base_address, float u_c3);

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

void uz_pmsm_model_9ph_hw_write_L_o1(uint32_t base_address, float L_o1);
void uz_pmsm_model_9ph_hw_write_L_o2(uint32_t base_address, float L_o2);
void uz_pmsm_model_9ph_hw_write_L_x1(uint32_t base_address, float L_x1);
void uz_pmsm_model_9ph_hw_write_L_y1(uint32_t base_address, float L_y1);
void uz_pmsm_model_9ph_hw_write_L_x2(uint32_t base_address, float L_x2);
void uz_pmsm_model_9ph_hw_write_L_y2(uint32_t base_address, float L_y2);
void uz_pmsm_model_9ph_hw_write_L_zero(uint32_t base_address, float L_zero);

// Strobe
void uz_pmsm_model_9ph_hw_trigger_output_general_strobe(uint32_t base_address);
void uz_pmsm_model_9ph_hw_trigger_output_currents_dq_strobe(uint32_t base_address);
void uz_pmsm_model_9ph_hw_trigger_output_currents_abc_strobe(uint32_t base_address);
void uz_pmsm_model_9ph_hw_trigger_input_general_strobe(uint32_t base_address);
void uz_pmsm_model_9ph_hw_trigger_input_voltages_dq_strobe(uint32_t base_address);
void uz_pmsm_model_9ph_hw_trigger_input_voltages_abc_strobe(uint32_t base_address);
#endif // uz_pmsm_model_9ph_HW_H
