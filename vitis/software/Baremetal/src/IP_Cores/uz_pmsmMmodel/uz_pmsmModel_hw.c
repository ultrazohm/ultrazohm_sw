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

#include "uz_pmsmModel_hw.h"
#include "uz_pmsmModel_hwAddresses.h"
#include "../../uz/uz_AXI.h"

float uz_pmsmModel_hw_read_torque(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + torque_Data_uz_pmsm_model);
}

float uz_pmsmModel_hw_read_i_q(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return (uz_axi_read_float(base_address + i_q_Data_uz_pmsm_model));
}

float uz_pmsmModel_hw_read_i_d(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return (uz_axi_read_float(base_address + i_d_Data_uz_pmsm_model));
}

void uz_pmsmModel_hw_write_reset(uint32_t base_address, bool reset)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + reset_integrators_Data_uz_pmsm_model, reset);
}

void uz_pmsmModel_hw_write_omega_mech(uint32_t base_address, float omega_mech)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + in_omega_mech_Data_uz_pmsm_model, omega_mech);
}

void uz_pmsmModel_hw_write_v_q(uint32_t base_address, float v_q)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + v_q_Data_uz_pmsm_model, v_q);
}

void uz_pmsmModel_hw_write_v_d(uint32_t base_address, float v_d)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + v_d_Data_uz_pmsm_model, v_d);
}

void uz_pmsmModel_hw_write_friction_coefficient(uint32_t base_address, float mu)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + mu_Data_uz_pmsm_model, mu);
}

void uz_pmsmModel_hw_write_coulomb_friction_constant(uint32_t base_address, float m_c)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + M_n0_Data_uz_pmsm_model, m_c);
}

void uz_pmsmModel_hw_write_r_1(uint32_t base_address, float r_1)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + R1_Data_uz_pmsm_model, r_1);
}

void uz_pmsmModel_hw_write_polepairs(uint32_t base_address, float polepairs)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + polepairs_Data_uz_pmsm_model, polepairs);
}

void uz_pmsmModel_hw_write_psi_pm(uint32_t base_address, float psi_pm)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + psi_pm_Data_uz_pmsm_model, psi_pm);
}

void uz_pmsmModel_hw_write_L_d(uint32_t base_address, float L_d)
{
    uz_assert_not_zero(base_address);
    uz_assert(L_d > 0.0f); // prevent division by zero & negative inductance makes no sense
    uz_axi_write_float(base_address + Ld_Data_uz_pmsm_model, L_d);
}

void uz_pmsmModel_hw_write_L_q(uint32_t base_address, float L_q)
{
    uz_assert_not_zero(base_address);
    uz_assert(L_q > 0.0f); // prevent division by zero & negative inductance makes no sense
    uz_axi_write_float(base_address + Lq_Data_uz_pmsm_model, L_q);
}

float uz_pmsmModel_hw_read_omega_mech(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+out_omega_mech_Data_uz_pmsm_model);
}

void uz_pmsmModel_hw_write_simulate_mechanical(uint32_t base_address, bool simulate_mechanical){
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address+simulate_mechanical_Data_uz_pmsm_model,simulate_mechanical);
}

void uz_pmsmModel_hw_write_simulate_nonlinear(uint32_t base_address, bool simulate_nonlinear){
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address+simulate_nonlinear_Data_uz_pmsm_model,simulate_nonlinear);
}

void uz_pmsmModel_hw_write_inertia(uint32_t base_address, float intertia){
    uz_assert_not_zero(base_address);
    uz_assert(intertia > 0.0f); // prevent division by zero and no negative inertia exists
    uz_axi_write_float(base_address+reciprocal_J_Data_uz_pmsm_model,(1.0f/intertia));
}

void uz_pmsmModel_hw_write_load_torque(uint32_t base_address, float load_torque){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+load_torque_Data_uz_pmsm_model,load_torque);
}

//Fitting Parameter
void uz_pmsmModel_hw_write_ad1(uint32_t base_address, float ad1){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+ad1_Data_uz_pmsm_model,ad1);
}

void uz_pmsmModel_hw_write_ad2(uint32_t base_address, float ad2){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+ad2_Data_uz_pmsm_model,ad2);
}

void uz_pmsmModel_hw_write_ad3(uint32_t base_address, float ad3){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+ad3_Data_uz_pmsm_model,ad3);
}

void uz_pmsmModel_hw_write_ad4(uint32_t base_address, float ad4){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+ad4_Data_uz_pmsm_model,ad4);
}

void uz_pmsmModel_hw_write_ad5(uint32_t base_address, float ad5){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+ad5_Data_uz_pmsm_model,ad5);
}

void uz_pmsmModel_hw_write_ad6(uint32_t base_address, float ad6){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+ad6_Data_uz_pmsm_model,ad6);
}


void uz_pmsmModel_hw_write_aq1(uint32_t base_address, float aq1){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+aq1_Data_uz_pmsm_model,aq1);
}

void uz_pmsmModel_hw_write_aq2(uint32_t base_address, float aq2){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+aq2_Data_uz_pmsm_model,aq2);
}

void uz_pmsmModel_hw_write_aq3(uint32_t base_address, float aq3){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+aq3_Data_uz_pmsm_model,aq3);
}

void uz_pmsmModel_hw_write_aq4(uint32_t base_address, float aq4){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+aq4_Data_uz_pmsm_model,aq4);
}

void uz_pmsmModel_hw_write_aq5(uint32_t base_address, float aq5){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+aq5_Data_uz_pmsm_model,aq5);
}

void uz_pmsmModel_hw_write_aq6(uint32_t base_address, float aq6){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+aq6_Data_uz_pmsm_model,aq6);
}

void uz_pmsmModel_hw_write_reciprocal_F1G1(uint32_t base_address, float F1G1){
    uz_assert_not_zero(base_address);
    uz_assert(F1G1 != 0.0f); // prevent division by zero and no negative inertia exists
    uz_axi_write_float(base_address+reciprocal_F1G1_Data_uz_pmsm_model,(1.0f/F1G1));
}

void uz_pmsmModel_hw_write_reciprocal_F2G2(uint32_t base_address, float F2G2){
    uz_assert_not_zero(base_address);
    uz_assert(F2G2 != 0.0f); // prevent division by zero and no negative inertia exists
    uz_axi_write_float(base_address+reciprocal_F2G2_Data_uz_pmsm_model,(1.0f/F2G2));
}

//FittingParameter that are calculated in driver

//Multiply
void uz_pmsmModel_hw_write_ad4_mul_ad5(uint32_t base_address, float ad4, float ad5){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+ad4_mul_ad5_Data_uz_pmsm_model,(ad4*ad5));
}

void uz_pmsmModel_hw_write_ad1_mul_ad2(uint32_t base_address, float ad1, float ad2){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+ad1_mul_ad2_Data_uz_pmsm_model,(ad1*ad2));
}

void uz_pmsmModel_hw_write_aq4_mul_aq5(uint32_t base_address, float aq4, float aq5){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+aq4_mul_aq5_Data_uz_pmsm_model,(aq4*aq5));
}

void uz_pmsmModel_hw_write_aq1_mul_aq2(uint32_t base_address, float aq1, float aq2){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+aq1_mul_aq2_Data_uz_pmsm_model,(aq1*aq2));
}

//Divide
void uz_pmsmModel_hw_write_aq4_div_aq5(uint32_t base_address, float aq4, float aq5){
    uz_assert_not_zero(base_address);
    uz_assert(aq5 != 0.0f); // prevent division by zero
    uz_axi_write_float(base_address+aq4_div_aq5_Data_uz_pmsm_model,(aq4/aq5));
}

void uz_pmsmModel_hw_write_aq1_div_aq2(uint32_t base_address, float aq1, float aq2){
    uz_assert_not_zero(base_address);
    uz_assert(aq2 != 0.0f); // prevent division by zero
    uz_axi_write_float(base_address+aq1_div_aq2_Data_uz_pmsm_model,(aq1/aq2));
}

void uz_pmsmModel_hw_write_ad4_div_ad5(uint32_t base_address, float ad4, float ad5){
    uz_assert_not_zero(base_address);
    uz_assert(ad5 != 0.0f); // prevent division by zero
    uz_axi_write_float(base_address+ad4_div_ad5_Data_uz_pmsm_model,(ad4/ad5));
}

void uz_pmsmModel_hw_write_ad1_div_ad2(uint32_t base_address, float ad1, float ad2){
    uz_assert_not_zero(base_address);
    uz_assert(ad2 != 0.0f); // prevent division by zero
    uz_axi_write_float(base_address+ad1_div_ad2_Data_uz_pmsm_model,(ad1/ad2));
}

void uz_pmsmModel_hw_write_aq3_min_aq6(uint32_t base_address, float aq3, float aq6){
    uz_assert_not_zero(base_address);
    uz_assert(aq3 != 0); // prevent difference becoming zero
    uz_axi_write_float(base_address+aq3_min_aq6_Data_uz_pmsm_model,(0.5f*(aq3-aq6)));
}


//Strobes
void uz_pmsmModel_hw_trigger_input_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+inputs_Strobe_uz_pmsm_model,true);
    uz_axi_write_bool(base_address+inputs_Strobe_uz_pmsm_model,false);
}

void uz_pmsmModel_hw_trigger_output_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+outputs_Strobe_uz_pmsm_model,true);
    uz_axi_write_bool(base_address+outputs_Strobe_uz_pmsm_model,false);
}

void uz_pmsmModel_hw_trigger_fitting_parameter_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+fitting_parameter_Strobe_uz_pmsm_model ,true);
    uz_axi_write_bool(base_address+fitting_parameter_Strobe_uz_pmsm_model ,false);
}




