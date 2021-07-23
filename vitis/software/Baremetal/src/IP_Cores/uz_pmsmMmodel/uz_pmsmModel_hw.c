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

void uz_pmsmModel_hw_write_u_q(uint32_t base_address, float u_q)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + u_q_Data_uz_pmsm_model, u_q);
}

void uz_pmsmModel_hw_write_u_d(uint32_t base_address, float u_d)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + u_d_Data_uz_pmsm_model, u_d);
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
    // Hardware expects recirpocal of L_d to not have to invert L_d in the IP-Core
    uz_axi_write_float(base_address + reciprocal_L_d_Data_uz_pmsm_model, (1.0f / L_d));
}

void uz_pmsmModel_hw_write_L_q(uint32_t base_address, float L_q)
{
    uz_assert_not_zero(base_address);
    uz_assert(L_q > 0.0f); // prevent division by zero & negative inductance makes no sense
    // Hardware expects recirpocal of L_q to not have to invert it in the IP-Core
    uz_axi_write_float(base_address + reciprocal_L_q_Data_uz_pmsm_model, (1.0f / L_q));
}

float uz_pmsmModel_hw_read_omega_mech(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+out_omega_mech_Data_uz_pmsm_model);
}

void uz_pmsmModel_hw_write_simulate_mechanical(uint32_t base_address, bool simulate_mechanical){
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address+simulate_mechanical_Data_uz_pmsm_model,simulate_mechanical);
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