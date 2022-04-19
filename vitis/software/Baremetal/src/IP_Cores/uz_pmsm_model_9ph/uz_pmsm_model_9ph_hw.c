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

// Outputs currents dq
float uz_pmsm_model_9ph_hw_read_i_d_outdq(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return (uz_axi_read_float(base_address + i_d_Data_uz_pmsm_model_9ph_outdq));
}

float uz_pmsm_model_9ph_hw_read_i_q_outdq(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return (uz_axi_read_float(base_address + i_q_Data_uz_pmsm_model_9ph_outdq));
}

float uz_pmsm_model_9ph_hw_read_i_o1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_o1_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_i_o2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_o2_Data_uz_pmsm_model_9ph);
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

float uz_pmsm_model_9ph_hw_read_i_zero(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_zero_Data_uz_pmsm_model_9ph);
}

// Outputs currents abc
float uz_pmsm_model_9ph_hw_read_i_a1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_a1_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_i_b1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_b1_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_i_c1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_c1_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_i_a2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_a2_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_i_b2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_b2_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_i_c2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_c2_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_i_a3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_a3_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_i_b3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_b3_Data_uz_pmsm_model_9ph);
}

float uz_pmsm_model_9ph_hw_read_i_c3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+i_c3_Data_uz_pmsm_model_9ph);
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

// Inputs voltages dq
void uz_pmsm_model_9ph_hw_write_u_q(uint32_t base_address, float u_q)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + u_q_Data_uz_pmsm_model_9ph, u_q);
}

void uz_pmsm_model_9ph_hw_write_u_d(uint32_t base_address, float u_d)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + u_d_Data_uz_pmsm_model_9ph, u_d);
}

void uz_pmsm_model_9ph_hw_write_u_o1(uint32_t base_address, float u_o1){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_o1_Data_uz_pmsm_model_9ph, u_o1);
}

void uz_pmsm_model_9ph_hw_write_u_o2(uint32_t base_address, float u_o2){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_o2_Data_uz_pmsm_model_9ph, u_o2);
}

void uz_pmsm_model_9ph_hw_write_u_x1(uint32_t base_address, float u_x1){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_x1_Data_uz_pmsm_model_9ph, u_x1);
}

void uz_pmsm_model_9ph_hw_write_u_y1(uint32_t base_address, float u_y1){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_y1_Data_uz_pmsm_model_9ph, u_y1);
}

void uz_pmsm_model_9ph_hw_write_u_x2(uint32_t base_address, float u_x2){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_x2_Data_uz_pmsm_model_9ph, u_x2);
}

void uz_pmsm_model_9ph_hw_write_u_y2(uint32_t base_address, float u_y2){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_y2_Data_uz_pmsm_model_9ph, u_y2);
}

void uz_pmsm_model_9ph_hw_write_u_zero(uint32_t base_address, float u_zero){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_zero_Data_uz_pmsm_model_9ph, u_zero);
}

// Inputs voltages abc
void uz_pmsm_model_9ph_hw_write_u_a1(uint32_t base_address, float u_a1){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_a1_Data_uz_pmsm_model_9ph, u_a1);
}

void uz_pmsm_model_9ph_hw_write_u_b1(uint32_t base_address, float u_b1){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_b1_Data_uz_pmsm_model_9ph, u_b1);
}

void uz_pmsm_model_9ph_hw_write_u_c1(uint32_t base_address, float u_c1){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_c1_Data_uz_pmsm_model_9ph, u_c1);
}

void uz_pmsm_model_9ph_hw_write_u_a2(uint32_t base_address, float u_a2){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_a2_Data_uz_pmsm_model_9ph, u_a2);
}

void uz_pmsm_model_9ph_hw_write_u_b2(uint32_t base_address, float u_b2){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_b2_Data_uz_pmsm_model_9ph, u_b2);
}

void uz_pmsm_model_9ph_hw_write_u_c2(uint32_t base_address, float u_c2){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_c2_Data_uz_pmsm_model_9ph, u_c2);
}

void uz_pmsm_model_9ph_hw_write_u_a3(uint32_t base_address, float u_a3){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_a3_Data_uz_pmsm_model_9ph, u_a3);
}

void uz_pmsm_model_9ph_hw_write_u_b3(uint32_t base_address, float u_b3){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_b3_Data_uz_pmsm_model_9ph, u_b3);
}

void uz_pmsm_model_9ph_hw_write_u_c3(uint32_t base_address, float u_c3){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_c3_Data_uz_pmsm_model_9ph, u_c3);
}

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

void uz_pmsm_model_9ph_hw_write_L_q(uint32_t base_address, float L_q)
{
    uz_assert_not_zero(base_address);
    uz_assert(L_q > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects reciprocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + Physical_Parameter_reciprocal_L_q_Data_uz_pmsm_model_9ph, (1.0f / L_q));
}

void uz_pmsm_model_9ph_hw_write_r_1(uint32_t base_address, float r_1)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + Physical_Parameter_R1_Data_uz_pmsm_model_9ph, r_1);
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

void uz_pmsm_model_9ph_hw_write_L_o1(uint32_t base_address, float L_o1)
{
    uz_assert_not_zero(base_address);
    uz_assert(L_o1 > 0.0f); // prevent division by zero & negative inductance makes no sense
    uz_axi_write_float(base_address + Physical_Parameter_L_o1_Data_uz_pmsm_model_9ph, L_o1);
}

void uz_pmsm_model_9ph_hw_write_L_o2(uint32_t base_address, float L_o2)
{
    uz_assert_not_zero(base_address);
    uz_assert(L_o2 > 0.0f); // prevent division by zero & negative inductance makes no sense
    uz_axi_write_float(base_address + Physical_Parameter_L_o2_Data_uz_pmsm_model_9ph, L_o2);
}

void uz_pmsm_model_9ph_hw_write_L_x1(uint32_t base_address, float L_x1)
{
    uz_assert_not_zero(base_address);
    uz_assert(L_x1 > 0.0f); // prevent division by zero & negative inductance makes no sense
    uz_axi_write_float(base_address + Physical_Parameter_L_x1_Data_uz_pmsm_model_9ph, L_x1);
}

void uz_pmsm_model_9ph_hw_write_L_y1(uint32_t base_address, float L_y1)
{
    uz_assert_not_zero(base_address);
    uz_assert(L_y1 > 0.0f); // prevent division by zero & negative inductance makes no sense
    uz_axi_write_float(base_address + Physical_Parameter_L_y1_Data_uz_pmsm_model_9ph, L_y1);
}

void uz_pmsm_model_9ph_hw_write_L_x2(uint32_t base_address, float L_x2)
{
    uz_assert_not_zero(base_address);
    uz_assert(L_x2 > 0.0f); // prevent division by zero & negative inductance makes no sense
    uz_axi_write_float(base_address + Physical_Parameter_L_x2_Data_uz_pmsm_model_9ph, L_x2);
}

void uz_pmsm_model_9ph_hw_write_L_y2(uint32_t base_address, float L_y2)
{
    uz_assert_not_zero(base_address);
    uz_assert(L_y2 > 0.0f); // prevent division by zero & negative inductance makes no sense
    uz_axi_write_float(base_address + Physical_Parameter_L_y2_Data_uz_pmsm_model_9ph, L_y2);
}

void uz_pmsm_model_9ph_hw_write_L_zero(uint32_t base_address, float L_zero)
{
    uz_assert_not_zero(base_address);
    uz_assert(L_zero > 0.0f); // prevent division by zero & negative inductance makes no sense
    uz_axi_write_float(base_address + Physical_Parameter_L_zero_Data_uz_pmsm_model_9ph, L_zero);
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

void uz_pmsm_model_9ph_hw_trigger_output_currents_abc_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+output_currents_abc_Strobe_uz_pmsm_model_9ph,true);
    uz_axi_write_bool(base_address+output_currents_abc_Strobe_uz_pmsm_model_9ph,false);
}

void uz_pmsm_model_9ph_hw_trigger_input_general_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+inputs_general_Strobe_uz_pmsm_model_9ph,true);
    uz_axi_write_bool(base_address+inputs_general_Strobe_uz_pmsm_model_9ph,false);
}

void uz_pmsm_model_9ph_hw_trigger_input_voltages_dq_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+input_voltages_dq_Strobe_uz_pmsm_model_9ph,true);
    uz_axi_write_bool(base_address+input_voltages_dq_Strobe_uz_pmsm_model_9ph,false);
}

void uz_pmsm_model_9ph_hw_trigger_input_voltages_abc_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+input_voltages_abc_Strobe_uz_pmsm_model_9ph,true);
    uz_axi_write_bool(base_address+input_voltages_abc_Strobe_uz_pmsm_model_9ph,false);
}