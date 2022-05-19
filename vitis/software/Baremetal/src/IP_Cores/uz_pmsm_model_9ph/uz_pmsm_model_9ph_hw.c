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

#include "uz_pmsm_model_9ph_hw.h"
#include "uz_pmsm_model_9ph_hwaddr.h"
#include "../../uz/uz_AXI.h"


// Outputs general
float uz_pmsm_model_9ph_hw_read_torque(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + torque_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_omega_mech(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+out_omega_mech_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_theta_el(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+out_theta_el_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_u_d(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+u_d_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_u_q(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+u_q_Data_uz_pmsm_model_9ph);
}

// Outputs currents dq
float uz_pmsm_model_9ph_hw_read_i_d(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return (uz_axi_read_float(base_address + i_d_Data_uz_pmsm_model_9ph));
}

float uz_pmsm_model_9ph_hw_read_i_q(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return (uz_axi_read_float(base_address + i_q_Data_uz_pmsm_model_9ph));
}

float uz_pmsm_model_9ph_hw_read_i_z1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_z1_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_i_z2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_z2_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_i_x1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_x1_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_i_y1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_y1_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_i_x2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_x2_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_i_y2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_y2_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_i_z3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_z3_Data_uz_pmsm_model_9ph);
}

// Inputs general
void uz_pmsm_model_9ph_hw_write_load_torque(uint32_t base_address, float load_torque){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+load_torque_Data_uz_pmsm_model_9ph,load_torque);
}

void uz_pmsm_model_9ph_hw_write_omega_mech(uint32_t base_address, float omega_mech)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + in_omega_mech_Data_uz_pmsm_model_9ph, omega_mech);
}
/*
void uz_pmsm_model_9ph_hw_write_u_d(uint32_t base_address, float u_d)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + u_d_uz_pmsm_model_9ph, u_d);
}

void uz_pmsm_model_9ph_hw_write_u_q(uint32_t base_address, float u_q)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + u_q_uz_pmsm_model_9ph, u_q);
}
*/
// Model parameter
void uz_pmsm_model_9ph_hw_write_reset(uint32_t base_address, bool reset)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + Model_Parameter_reset_integrators_Data_uz_pmsm_model_9ph, reset);
}

void uz_pmsm_model_9ph_hw_write_simulate_mechanical(uint32_t base_address, bool simulate_mechanical){
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address+Model_Parameter_simulate_mechanical_Data_uz_pmsm_model_9ph,simulate_mechanical);
}

void uz_pmsm_model_9ph_hw_write_switch_pspl(uint32_t base_address, bool switch_pspl){
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address+Model_Parameter_switch_pspl_Data_uz_pmsm_model_9ph,switch_pspl);
}

void uz_pmsm_model_9ph_hw_write_control_dq_abc(uint32_t base_address, bool control_dq){
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address+Model_Parameter_control_dq_abc_Data_uz_pmsm_model_9ph,control_dq);
}

// Physical parameter
void uz_pmsm_model_9ph_hw_write_inertia(uint32_t base_address, float intertia){
    uz_assert_not_zero(base_address);
    uz_assert(intertia > 0.0f); // prevent division by zero and no negative inertia exists
    uz_axi_write_float(base_address+Physical_Parameter_1_J_Data_uz_pmsm_model_9ph,(1.0f/intertia));
}

void uz_pmsm_model_9ph_hw_write_friction_coefficient(uint32_t base_address, float mu)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + Physical_Parameter_mu_Data_uz_pmsm_model_9ph, mu);
}

void uz_pmsm_model_9ph_hw_write_coulomb_friction_constant(uint32_t base_address, float m_c)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + Physical_Parameter_M_R0_Data_uz_pmsm_model_9ph, m_c);
}

void uz_pmsm_model_9ph_hw_write_L_d(uint32_t base_address, float L_d)
{
    uz_assert_not_zero(base_address);
    uz_assert(L_d > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_d to not have to invert L_d in the IP-Core
    uz_axi_write_float(base_address + Physical_Parameter_reciprocal_L_d_Data_uz_pmsm_model_9ph, (1.0f / L_d));
}

void uz_pmsm_model_9ph_hw_write_L_q(uint32_t base_address, float inductance)
{
    uz_assert_not_zero(base_address);
    uz_assert(inductance > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + Physical_Parameter_reciprocal_L_q_Data_uz_pmsm_model_9ph, (1.0f / inductance));
}

void uz_pmsm_model_9ph_hw_write_r_1(uint32_t base_address, float r_1)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + Physical_Parameter_R1_Data_uz_pmsm_model_9ph, (r_1));
}

void uz_pmsm_model_9ph_hw_write_polepairs(uint32_t base_address, float polepairs)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + Physical_Parameter_polepairs_Data_uz_pmsm_model_9ph, polepairs);
}

void uz_pmsm_model_9ph_hw_write_psi_pm(uint32_t base_address, float psi_pm)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + Physical_Parameter_psi_pm_Data_uz_pmsm_model_9ph, psi_pm);
}

void uz_pmsm_model_9ph_hw_write_L_z1(uint32_t base_address, float inductance)
{
    uz_assert_not_zero(base_address);
    uz_assert(inductance > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + Physical_Parameter_L_z1_Data_uz_pmsm_model_9ph, (1.0f / inductance));
}

void uz_pmsm_model_9ph_hw_write_L_z2(uint32_t base_address, float inductance)
{
    uz_assert_not_zero(base_address);
    uz_assert(inductance > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + Physical_Parameter_L_z2_Data_uz_pmsm_model_9ph, (1.0f / inductance));
}

void uz_pmsm_model_9ph_hw_write_L_x1(uint32_t base_address, float inductance)
{
    uz_assert_not_zero(base_address);
    uz_assert(inductance > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + Physical_Parameter_L_x1_Data_uz_pmsm_model_9ph, (1.0f / inductance));
}

void uz_pmsm_model_9ph_hw_write_L_y1(uint32_t base_address, float inductance)
{
    uz_assert_not_zero(base_address);
    uz_assert(inductance > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + Physical_Parameter_L_y1_Data_uz_pmsm_model_9ph, (1.0f / inductance));
}

void uz_pmsm_model_9ph_hw_write_L_x2(uint32_t base_address, float inductance)
{
    uz_assert_not_zero(base_address);
    uz_assert(inductance > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + Physical_Parameter_L_x2_Data_uz_pmsm_model_9ph, (1.0f / inductance));
}

void uz_pmsm_model_9ph_hw_write_L_y2(uint32_t base_address, float inductance)
{
    uz_assert_not_zero(base_address);
    uz_assert(inductance > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + Physical_Parameter_L_y2_Data_uz_pmsm_model_9ph, (1.0f / inductance));
}

void uz_pmsm_model_9ph_hw_write_L_z3(uint32_t base_address, float inductance)
{
    uz_assert_not_zero(base_address);
    uz_assert(inductance > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + Physical_Parameter_L_z3_Data_uz_pmsm_model_9ph, (1.0f / inductance));
}

// Strobe
void uz_pmsm_model_9ph_hw_trigger_output_general_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+output_general_Strobe_uz_pmsm_model_9ph,true);
    uz_axi_write_bool(base_address+output_general_Strobe_uz_pmsm_model_9ph,false);
}

void uz_pmsm_model_9ph_hw_trigger_output_currents_dq_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+output_currents_dq_Strobe_uz_pmsm_model_9ph,true);
    uz_axi_write_bool(base_address+output_currents_dq_Strobe_uz_pmsm_model_9ph,false);
}

void uz_pmsm_model_9ph_hw_trigger_input_general_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+inputs_general_Strobe_uz_pmsm_model_9ph,true);
    uz_axi_write_bool(base_address+inputs_general_Strobe_uz_pmsm_model_9ph,false);
}