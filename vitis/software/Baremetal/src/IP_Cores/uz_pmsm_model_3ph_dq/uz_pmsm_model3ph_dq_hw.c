/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2021 Tobias Schindler
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

#include "uz_pmsm_model3ph_dq_hw.h"
#include "uz_pmsm_model3ph_dq_hwAddresses.h"
#include "../../uz/uz_AXI.h"

float uz_pmsm_model3ph_hw_read_torque(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + torque_Data_uz_pmsm_model3ph);
}

float uz_pmsm_model3ph_hw_read_i_q(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return (uz_axi_read_float(base_address + i_q_Data_uz_pmsm_model3ph));
}

float uz_pmsm_model3ph_hw_read_i_d(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return (uz_axi_read_float(base_address + i_d_Data_uz_pmsm_model3ph));
}

float uz_pmsm_model3ph_hw_read_theta_el(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return (uz_axi_read_float(base_address + theta_el_Data_uz_pmsm_model3ph));
}

void uz_pmsm_model3ph_hw_write_reset(uint32_t base_address, bool reset)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + reset_integrators_Data_uz_pmsm_model3ph, reset);
}

void uz_pmsm_model3ph_hw_write_omega_mech(uint32_t base_address, float omega_mech)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + in_omega_mech_Data_uz_pmsm_model3ph, omega_mech);
}

void uz_pmsm_model3ph_hw_write_v_q(uint32_t base_address, float v_q)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + v_q_Data_uz_pmsm_model3ph, v_q);
}

void uz_pmsm_model3ph_hw_write_v_d(uint32_t base_address, float v_d)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + v_d_Data_uz_pmsm_model3ph, v_d);
}

void uz_pmsm_model3ph_hw_write_friction_coefficient(uint32_t base_address, float mu)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + mu_Data_uz_pmsm_model3ph, mu);
}

void uz_pmsm_model3ph_hw_write_coulomb_friction_constant(uint32_t base_address, float m_c)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + M_n0_Data_uz_pmsm_model3ph, m_c);
}

void uz_pmsm_model3ph_hw_write_r_1(uint32_t base_address, float r_1)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + R1_Data_uz_pmsm_model3ph, r_1);
}

void uz_pmsm_model3ph_hw_write_polepairs(uint32_t base_address, float polepairs)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + polepairs_Data_uz_pmsm_model3ph, polepairs);
}

void uz_pmsm_model3ph_hw_write_psi_pm(uint32_t base_address, float psi_pm)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + psi_pm_Data_uz_pmsm_model3ph, psi_pm);
}

void uz_pmsm_model3ph_hw_write_L_d(uint32_t base_address, float L_d)
{
    uz_assert_not_zero(base_address);
    uz_assert(L_d > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects recirpocal of L_d to not have to invert L_d in the IP-Core
    uz_axi_write_float(base_address + reciprocal_L_d_Data_uz_pmsm_model3ph, (1.0f / L_d));
}

void uz_pmsm_model3ph_hw_write_L_q(uint32_t base_address, float L_q)
{
    uz_assert_not_zero(base_address);
    uz_assert(L_q > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects recirpocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + reciprocal_L_q_Data_uz_pmsm_model3ph, (1.0f / L_q));
}

float uz_pmsm_model3ph_hw_read_omega_mech(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+out_omega_mech_Data_uz_pmsm_model3ph);
}

void uz_pmsm_model3ph_hw_write_simulate_mechanical(uint32_t base_address, bool simulate_mechanical){
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address+simulate_mechanical_Data_uz_pmsm_model3ph,simulate_mechanical);
}

void uz_pmsm_model3ph_hw_write_inertia(uint32_t base_address, float intertia){
    uz_assert_not_zero(base_address);
    uz_assert(intertia > 0.0f); // prevent division by zero and no negative inertia exists
    uz_axi_write_float(base_address+reciprocal_J_Data_uz_pmsm_model3ph,(1.0f/intertia));
}

void uz_pmsm_model3ph_hw_write_load_torque(uint32_t base_address, float load_torque){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+load_torque_Data_uz_pmsm_model3ph,load_torque);
}

void uz_pmsm_model3ph_hw_write_switch_pspl(uint32_t base_address, bool switch_pspl)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + use_axi_input_Data_uz_pmsm_model3ph, switch_pspl);
}

// Voltage Input readout
float uz_pmsm_model3ph_hw_read_v_d(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + voltage_input_dq_out_axi_fb_Data_uz_pmsm_model3ph);
}

float uz_pmsm_model3ph_hw_read_v_q(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + voltage_input_dq_out_axi_fb_Data_uz_pmsm_model3ph+0x04);
}

void uz_pmsm_model3ph_hw_trigger_input_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+inputs_Strobe_uz_pmsm_model3ph,true);
    uz_axi_write_bool(base_address+inputs_Strobe_uz_pmsm_model3ph,false);
}

void uz_pmsm_model3ph_hw_trigger_output_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+outputs_Strobe_uz_pmsm_model3ph,true);
    uz_axi_write_bool(base_address+outputs_Strobe_uz_pmsm_model3ph,false);
}

void uz_pmsm_model3ph_hw_trigger_fb_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+voltage_input_dq_out_axi_fb_Strobe_uz_pmsm_model3ph,true);
    uz_axi_write_bool(base_address+voltage_input_dq_out_axi_fb_Strobe_uz_pmsm_model3ph,false);
}