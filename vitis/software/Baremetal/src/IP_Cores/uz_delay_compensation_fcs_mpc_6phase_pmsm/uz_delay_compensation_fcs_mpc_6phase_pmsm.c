#include "../../uz/uz_global_configuration.h"
#if UZ_DELAY_COMPENSATION_FCS_MPC_6PHASE_PMSM_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_delay_compensation_fcs_mpc_6phase_pmsm.h"
#include "uz_delay_compensation_fcs_mpc_6phase_pmsm_hw.h"

struct uz_delay_compensation_fcs_mpc_6phase_t {
    bool is_ready;
    struct uz_delay_compensation_fcs_mpc_6phase_config_t config;
   // struct uz_delay_compensation_fcs_mpc_6phase_AXI_values_t AXI_values;
};

static uint32_t instance_counter = 0U;
static uz_delay_compensation_fcs_mpc_6phase_t instances[UZ_DELAY_COMPENSATION_FCS_MPC_6PHASE_PMSM_MAX_INSTANCES] = { 0 };

static uz_delay_compensation_fcs_mpc_6phase_t* uz_delay_compensation_fcs_mpc_6phase_allocation(void);

static uz_delay_compensation_fcs_mpc_6phase_t* uz_delay_compensation_fcs_mpc_6phase_allocation(void){
    uz_assert(instance_counter < UZ_DELAY_COMPENSATION_FCS_MPC_6PHASE_PMSM_MAX_INSTANCES);
    uz_delay_compensation_fcs_mpc_6phase_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_delay_compensation_fcs_mpc_6phase_t* uz_delay_compensation_fcs_mpc_6phase_init(struct uz_delay_compensation_fcs_mpc_6phase_config_t config){
    uz_delay_compensation_fcs_mpc_6phase_t* self = uz_delay_compensation_fcs_mpc_6phase_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    self->config = config;

    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_psiPM(self->config.base_address, self->config.psiPM);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Lq(self->config.base_address, self->config.Lq);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Ld(self->config.base_address, self->config.Ld);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Rs(self->config.base_address, self->config.Rs);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Ld(self->config.base_address, self->config.SampleTime, self->config.Ld);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_pole_pairs(self->config.base_address, self->config.pole_pairs);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Lq(self->config.base_address, self->config.SampleTime, self->config.Lq);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Lx(self->config.base_address, self->config.SampleTime, self->config.Lx);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Ly(self->config.base_address, self->config.SampleTime, self->config.Ly);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_use_AXI(self->config.base_address, self->config.use_AXI);
    return (self);
}
/*
void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_AXI_values(uz_delay_compensation_fcs_mpc_6phase_t* self, uz_delay_compensation_fcs_mpc_6phase_AXI_values_t AXI_values){
    
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_last_applied_optimal_voltage_ud(self->config.base_address, AXI_values.last_applied_optimal_voltage_ud);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_last_applied_optimal_voltage_uq(self->config.base_address, AXI_values.last_applied_optimal_voltage_uq);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_last_applied_optimal_voltage_ux(self->config.base_address, AXI_values.last_applied_optimal_voltage_ux);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_last_applied_optimal_voltage_uy(self->config.base_address, AXI_values.last_applied_optimal_voltage_uy);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_id_measured(self->config.base_address, AXI_values.id_measured);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_iq_measured(self->config.base_address, AXI_values.iq_measured);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_ix_measured(self->config.base_address, AXI_values.ix_measured);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_iy_measured(self->config.base_address, AXI_values.iy_measured);
    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_omega_m_measured(self->config.base_address, AXI_values.omega_m_measured);
}
*/
/*
uz_6ph_idk1_iqk1_ixk1_iyk1_t uz_delay_compensation_fcs_mpc_6phase_pmsm_get_idk1_iqK1_ixk1_iyk1(uz_delay_compensation_fcs_mpc_6phase_t* self){

    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_6ph_idk1_iqk1_ixk1_iyk1_t currents = {0};

    currents.id_k_1 = uz_delay_compensation_fcs_mpc_6phase_pmsm_get_id_k_1(self->config.base_address);
    currents.iq_k_1 = uz_delay_compensation_fcs_mpc_6phase_pmsm_get_iq_k_1(self->config.base_address);
    currents.ix_k_1 = uz_delay_compensation_fcs_mpc_6phase_pmsm_get_ix_k_1(self->config.base_address);
    currents.iy_k_1 = uz_delay_compensation_fcs_mpc_6phase_pmsm_get_iy_k_1(self->config.base_address);

    return currents;
}
*/
#endif
