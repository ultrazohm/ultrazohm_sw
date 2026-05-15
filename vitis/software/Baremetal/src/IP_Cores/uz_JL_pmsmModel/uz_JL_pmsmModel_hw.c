
#include "uz_JL_pmsmModel_hw.h"
#include "uz_JL_pmsmModel_hwAdresse.h"
#include "../../uz/uz_AXI.h"

void uz_JL_pmsmModel_hw_write_reset(uint32_t base_address, bool reset)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + IPCore_Reset_uz_JL_pmsmModel, reset);
}

// Write function for config PMSM parameters
void uz_JL_pmsmModel_hw_write_R1(uint32_t base_address, float mot_R1)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + r1_Data_uz_JL_pmsmModel, mot_R1);
}

void uz_JL_pmsmModel_hw_write_psi_pm(uint32_t base_address, float psi_pm)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + psi_pm_Data_uz_JL_pmsmModel, psi_pm);
}

void uz_JL_pmsmModel_hw_write_L_d(uint32_t base_address, float L_d)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + Ld_Data_uz_JL_pmsmModel, L_d);
    float rec_Ld = 1/(L_d);
    uz_axi_write_float(base_address + rec_mot_Ld_Data_uz_JL_pmsmModel, rec_Ld);
}

void uz_JL_pmsmModel_hw_write_L_q(uint32_t base_address, float L_q)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + Lq_Data_uz_JL_pmsmModel, L_q);
    float rec_Lq = 1/(L_q);
    uz_axi_write_float(base_address + rec_mot_Lq_Data_uz_JL_pmsmModel, rec_Lq);
}

void uz_JL_pmsmModel_hw_write_mot_p(uint32_t base_address, float mot_p)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + polpaare_Data_uz_JL_pmsmModel, mot_p);
}

void uz_JL_pmsmModel_hw_write_mot_J(uint32_t base_address, float mot_J)
{
    uz_assert_not_zero(base_address);
    float rec_J = 1/mot_J;
    uz_axi_write_float(base_address + mot_J_Data_uz_JL_pmsmModel, rec_J);
}

// void uz_JL_pmsmModel_hw_write_n_N(uint32_t base_address, float n_n)
// {
//     uz_assert_not_zero(base_address);
//     uz_axi_write_float(base_address + mot_n_N_Data_uz_JL_pmsmModel, n_n);
// }

// void uz_JL_pmsmModel_hw_write_M_N(uint32_t base_address, float M_n)
// {
//     uz_assert_not_zero(base_address);
//     uz_axi_write_float(base_address + PMSM_config_mot_M_N_Data_uz_JL_pmsmModel, M_n);
// }

// void uz_JL_pmsmModel_hw_write_I_max(uint32_t base_address, float I_max)
// {
//     uz_assert_not_zero(base_address);
//     uz_axi_write_float(base_address + PMSM_config_mot_I_max_Data_uz_JL_pmsmModel, I_max);
// }

//write Live parameters

void uz_JL_pmsmModel_hw_write_Last_J(uint32_t base_address, float Last_J)
{
    uz_assert_not_zero(base_address);
    float rec_J = 0;
    if (Last_J != 0)
    {
         rec_J = 1/Last_J;
    }
    else
    {
         rec_J = 0;
    }
    uz_axi_write_float(base_address + Last_J_Data_uz_JL_pmsmModel, rec_J);
}

void uz_JL_pmsmModel_hw_write_Last_M(uint32_t base_address, float Last_M)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + Last_M_Data_uz_JL_pmsmModel, Last_M);
}

void uz_JL_pmsmModel_hw_write_bremse(uint32_t base_address, bool bremse)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + Bremse_Data_uz_JL_pmsmModel, bremse);
}

void uz_JL_pmsmModel_hw_write_switchUabc_dq(uint32_t base_address, bool switchUabc_dq)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + switchUabc_dq_Data_uz_JL_pmsmModel, switchUabc_dq);
}

void uz_JL_pmsmModel_hw_write_Udq(uint32_t base_address, float Udq[2])
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + Ud_Data_uz_JL_pmsmModel, Udq[0]);
    uz_axi_write_float(base_address + Uq_Data_uz_JL_pmsmModel, Udq[1]);
}

// read outputs
float uz_JL_pmsmModel_hw_read_omega_mech(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + omega_mech_Data_uz_JL_pmsmModel);
}

float uz_JL_pmsmModel_hw_read_phi_mech(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + phi_mech_Data_uz_JL_pmsmModel);
}

float uz_JL_pmsmModel_hw_read_torque(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + pmsm_M_Mot_Data_uz_JL_pmsmModel);
}

float uz_JL_pmsmModel_hw_read_I_a(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + pmsm_Iu_Data_uz_JL_pmsmModel);
}

float uz_JL_pmsmModel_hw_read_I_b(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + pmsm_Iv_Data_uz_JL_pmsmModel);
}

float uz_JL_pmsmModel_hw_read_I_c(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address + pmsm_Iw_Data_uz_JL_pmsmModel);
}

// void uz_JL_pmsmModel_hw_trigger_output_strobe(uint32_t base_address)
// {
//     uz_assert_not_zero_uint32(base_address);
//     uz_axi_write_bool(base_address+Iabc_Strobe_uz_JL_pmsmModel,true);
//     uz_axi_write_bool(base_address+Iabc_Strobe_uz_JL_pmsmModel,false);
// }

// void uz_JL_pmsmModel_hw_trigger_input_strobe(uint32_t base_address)
// {
//     uz_assert_not_zero_uint32(base_address);
//     uz_axi_write_bool(base_address+Udq_Strobe_uz_JL_pmsmModel,true);
//     uz_axi_write_bool(base_address+Udq_Strobe_uz_JL_pmsmModel,false);
// }
