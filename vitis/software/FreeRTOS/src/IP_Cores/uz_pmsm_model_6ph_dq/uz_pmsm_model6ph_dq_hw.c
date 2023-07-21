/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 * Copyright 2021 Tobias Schindler
 * Copyright 2022 Valentin Hoppe
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

#include "uz_pmsm_model6ph_dq_hw.h"
#include "uz_pmsm_model6ph_dq_addr.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_Transformation/uz_Transformation.h"
#include <string.h>


// Model settings
void uz_pmsm_model6ph_hw_write_reset(uint32_t base_address, bool reset){
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + reset_integrators_Data_uz_pmsm_model_6ph_dq, reset);
}
void uz_pmsm_model6ph_hw_write_switch_pspl(uint32_t base_address, bool switch_pspl){
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + use_axi_input_Data_uz_pmsm_model_6ph_dq, switch_pspl);
}
void uz_pmsm_model6ph_hw_write_simulate_mechanical(uint32_t base_address, bool simulate_mechanical){
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + simulate_mechanical_Data_uz_pmsm_model_6ph_dq, simulate_mechanical);
}


// General inputs
void uz_pmsm_model6ph_hw_write_load_torque(uint32_t base_address, float load_torque){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + load_torque_Data_uz_pmsm_model_6ph_dq, load_torque);
}
void uz_pmsm_model6ph_hw_write_omega_mech(uint32_t base_address, float omega_mech){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + omega_mech_Data_uz_pmsm_model_6ph_dq, omega_mech);
}

// General outputs
float uz_pmsm_model6ph_hw_read_theta_el(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + theta_el_out_axi_Data_uz_pmsm_model_6ph_dq);
}
float uz_pmsm_model6ph_hw_read_torque(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + M_Mi_out_axi_Data_uz_pmsm_model_6ph_dq);
}
float uz_pmsm_model6ph_hw_read_omega_mech(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + omega_mech_out_axi_Data_uz_pmsm_model_6ph_dq);
}

// Voltage input
void uz_pmsm_model6ph_hw_write_voltage_dq_unsafe(uint32_t base_address, uz_6ph_dq_t phase_voltage){

    uz_assert_not_zero_uint32(base_address);
#pragma GCC diagnostic push                            // http://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast" // base address is uint32_t, axi_x_input is unsigned int, void is 4 or 8 byte depending if the code runs in the test environment or UZ - thus suppress this warning
    memcpy((void *)(base_address + voltage_input_dq_axi_Data_uz_pmsm_model_6ph_dq), &phase_voltage, sizeof(struct uz_6ph_dq_t));
#pragma GCC diagnostic pop
    uz_axi_write_bool(base_address+ voltage_input_dq_axi_Strobe_uz_pmsm_model_6ph_dq, true);
    uz_axi_write_bool(base_address+ voltage_input_dq_axi_Strobe_uz_pmsm_model_6ph_dq, false);
}
void uz_pmsm_model6ph_hw_write_u_d(uint32_t base_address, float voltage){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + voltage_input_dq_axi_Data_uz_pmsm_model_6ph_dq+0x00, voltage);
}
void uz_pmsm_model6ph_hw_write_u_q(uint32_t base_address, float voltage){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + voltage_input_dq_axi_Data_uz_pmsm_model_6ph_dq+0x04, voltage);
}
void uz_pmsm_model6ph_hw_write_u_x(uint32_t base_address, float voltage){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + voltage_input_dq_axi_Data_uz_pmsm_model_6ph_dq+0x08, voltage);
}
void uz_pmsm_model6ph_hw_write_u_y(uint32_t base_address, float voltage){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + voltage_input_dq_axi_Data_uz_pmsm_model_6ph_dq+0x0C, voltage);
}
void uz_pmsm_model6ph_hw_write_u_z1(uint32_t base_address, float voltage){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + voltage_input_dq_axi_Data_uz_pmsm_model_6ph_dq+0x10, voltage);
}
void uz_pmsm_model6ph_hw_write_u_z2(uint32_t base_address, float voltage){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + voltage_input_dq_axi_Data_uz_pmsm_model_6ph_dq+0x14, voltage);
}

// Voltage output
uz_6ph_dq_t uz_pmsm_model6ph_hw_read_voltage_dq_unsafe(uint32_t base_address)
{
    uz_6ph_dq_t readout = {0};
    uz_axi_write_bool(base_address+ voltage_input_dq_out_axi_fb_Strobe_uz_pmsm_model_6ph_dq, true);
    uz_axi_write_bool(base_address+ voltage_input_dq_out_axi_fb_Strobe_uz_pmsm_model_6ph_dq, false);
    uz_assert_not_zero_uint32(base_address);
#pragma GCC diagnostic push                            // http://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast" // base address is uint32_t, axi_x_input is unsigned int, void is 4 or 8 byte depending if the code runs in the test environment or UZ - thus suppress this warning
    memcpy(&readout, (void *)(base_address + voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_6ph_dq), sizeof(struct uz_6ph_dq_t));
#pragma GCC diagnostic pop

    return readout;
}
float uz_pmsm_model6ph_hw_read_u_d(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_6ph_dq+0x00);
}
float uz_pmsm_model6ph_hw_read_u_q(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_6ph_dq+0x04);
}
float uz_pmsm_model6ph_hw_read_u_x(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_6ph_dq+0x08);
}
float uz_pmsm_model6ph_hw_read_u_y(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_6ph_dq+0x0C);
}
float uz_pmsm_model6ph_hw_read_u_z1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_6ph_dq+0x10);
}
float uz_pmsm_model6ph_hw_read_u_z2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_6ph_dq+0x14);
}

// Current output
uz_6ph_dq_t uz_pmsm_model6ph_hw_read_currents_dq_unsafe(uint32_t base_address)
{
    uz_6ph_dq_t readout = {0};
    uz_axi_write_bool(base_address+ currents_dq_out_axi_Strobe_uz_pmsm_model_6ph_dq, true);
    uz_axi_write_bool(base_address+ currents_dq_out_axi_Strobe_uz_pmsm_model_6ph_dq, false);
    uz_assert_not_zero_uint32(base_address);
#pragma GCC diagnostic push                            // http://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast" // base address is uint32_t, axi_x_input is unsigned int, void is 4 or 8 byte depending if the code runs in the test environment or UZ - thus suppress this warning
    memcpy(&readout, (void *)(base_address + currents_dq_out_axi_Data_uz_pmsm_model_6ph_dq), sizeof(struct uz_6ph_dq_t));
#pragma GCC diagnostic pop

    return readout;
}

float uz_pmsm_model6ph_hw_read_i_d(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + currents_dq_out_axi_Data_uz_pmsm_model_6ph_dq+0x00);
}
float uz_pmsm_model6ph_hw_read_i_q(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + currents_dq_out_axi_Data_uz_pmsm_model_6ph_dq+0x04);
}
float uz_pmsm_model6ph_hw_read_i_x(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + currents_dq_out_axi_Data_uz_pmsm_model_6ph_dq+0x08);
}
float uz_pmsm_model6ph_hw_read_i_y(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + currents_dq_out_axi_Data_uz_pmsm_model_6ph_dq+0x0C);
}
float uz_pmsm_model6ph_hw_read_i_z1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + currents_dq_out_axi_Data_uz_pmsm_model_6ph_dq+0x10);
}
float uz_pmsm_model6ph_hw_read_i_z2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + currents_dq_out_axi_Data_uz_pmsm_model_6ph_dq+0x14);
}

// Physical parameter
void uz_pmsm_model6ph_hw_write_inertia(uint32_t base_address, float intertia){
    uz_assert_not_zero(base_address);
    uz_assert(intertia > 0.0f); // prevent division by zero and no negative inertia exists
    uz_axi_write_float(base_address + physical_parameters_1_J_Data_uz_pmsm_model_6ph_dq, (1.0f / intertia));
}
void uz_pmsm_model6ph_hw_write_friction_coefficient(uint32_t base_address, float mu){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + physical_parameters_mu_Data_uz_pmsm_model_6ph_dq, mu);
}
void uz_pmsm_model6ph_hw_write_coulomb_friction_constant(uint32_t base_address, float m_c){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + physical_parameters_M_R0_Data_uz_pmsm_model_6ph_dq, m_c);
}
void uz_pmsm_model6ph_hw_write_L_d(uint32_t base_address, float inductance){
    uz_assert_not_zero(base_address);
    uz_assert(inductance > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_d to not have to invert L_d in the IP-Core
    uz_axi_write_float(base_address + physical_parameters_1_L_d_Data_uz_pmsm_model_6ph_dq, (1.0f / inductance));
}
void uz_pmsm_model6ph_hw_write_L_q(uint32_t base_address, float inductance){
    uz_assert_not_zero(base_address);
    uz_assert(inductance > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + physical_parameters_1_L_q_Data_uz_pmsm_model_6ph_dq, (1.0f / inductance));
}
void uz_pmsm_model6ph_hw_write_r_1(uint32_t base_address, float r_1){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + physical_parameters_R_1_Data_uz_pmsm_model_6ph_dq, (r_1));
}
void uz_pmsm_model6ph_hw_write_polepairs(uint32_t base_address, float polepairs){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + physical_parameters_polepair_Data_uz_pmsm_model_6ph_dq, polepairs);
}
void uz_pmsm_model6ph_hw_write_psi_pm(uint32_t base_address, float psi_pm){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + physical_parameters_psi_pm_Data_uz_pmsm_model_6ph_dq, psi_pm);
}
void uz_pmsm_model6ph_hw_write_L_x(uint32_t base_address, float inductance){
    uz_assert_not_zero(base_address);
    uz_assert(inductance > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + physical_parameters_L_x_Data_uz_pmsm_model_6ph_dq, (1.0f / inductance));
}
void uz_pmsm_model6ph_hw_write_L_y(uint32_t base_address, float inductance){
    uz_assert_not_zero(base_address);
    uz_assert(inductance > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + physical_parameters_L_y_Data_uz_pmsm_model_6ph_dq, (1.0f / inductance));
}
void uz_pmsm_model6ph_hw_write_L_z1(uint32_t base_address, float inductance){
    uz_assert_not_zero(base_address);
    uz_assert(inductance > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + physical_parameters_L_z1_Data_uz_pmsm_model_6ph_dq, (1.0f / inductance));
}
void uz_pmsm_model6ph_hw_write_L_z2(uint32_t base_address, float inductance){
    uz_assert_not_zero(base_address);
    uz_assert(inductance > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + physical_parameters_L_z2_Data_uz_pmsm_model_6ph_dq, (1.0f / inductance));
}

// Strobe
void uz_pmsm_model6ph_trigger_voltage_input_strobe_hw(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+voltage_input_dq_axi_Strobe_uz_pmsm_model_6ph_dq,true);
    uz_axi_write_bool(base_address+voltage_input_dq_axi_Strobe_uz_pmsm_model_6ph_dq,false);
}
void uz_pmsm_model6ph_trigger_voltage_output_strobe_hw(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+voltage_input_dq_out_axi_fb_Strobe_uz_pmsm_model_6ph_dq,true);
    uz_axi_write_bool(base_address+voltage_input_dq_out_axi_fb_Strobe_uz_pmsm_model_6ph_dq,false);
}
void uz_pmsm_model6ph_trigger_current_output_strobe_hw(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+currents_dq_out_axi_Strobe_uz_pmsm_model_6ph_dq,true);
    uz_axi_write_bool(base_address+currents_dq_out_axi_Strobe_uz_pmsm_model_6ph_dq,false);
}