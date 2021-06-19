#include "uz_pmsmModel_hw.h"
#include "uz_pmsmModel_hwAddresses.h"
#include "../uz/uz_AXI.h"

float uz_pmsmModel_hw_read_torque(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+torque_Data_uz_pmsm_model);
}

float uz_pmsmModel_hw_read_i_q(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return (uz_axi_read_float(base_address+i_q_Data_uz_pmsm_model));
}

float uz_pmsmModel_hw_read_i_d(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return (uz_axi_read_float(base_address+i_d_Data_uz_pmsm_model));
}

void uz_pmsmModel_hw_write_reset(uint32_t base_address, bool reset){
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address+reset_Data_uz_pmsm_model,reset);
}

void uz_pmsmModel_hw_write_omega_mech(uint32_t base_address, float omega_mech) {
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+omega_mech_Data_uz_pmsm_model,omega_mech);
}

void uz_pmsmModel_hw_write_u_q(uint32_t base_address, float u_q){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_q_Data_uz_pmsm_model, u_q);
}

void uz_pmsmModel_hw_write_u_d(uint32_t base_address, float u_d){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+u_d_Data_uz_pmsm_model, u_d);
}