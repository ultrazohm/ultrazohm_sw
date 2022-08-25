#include "../../uz/uz_global_configuration.h"
#if UZ_PREDICTION_AND_COST_FUNCTION_FCS_MPC_6PHASE_PMSM_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm.h"
#include "uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw.h"

struct uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t {
    bool is_ready;
    struct uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_config_t config;
    struct uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_AXI_values_t AXI_values;
};

static uint32_t instance_counter = 0U;
static uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t instances[UZ_PREDICTION_AND_COST_FUNCTION_FCS_MPC_6PHASE_PMSM_MAX_INSTANCES] = { 0 };

static uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_allocation(void);

static uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_allocation(void){
    uz_assert(instance_counter < UZ_PREDICTION_AND_COST_FUNCTION_FCS_MPC_6PHASE_PMSM_MAX_INSTANCES);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_init(struct uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_config_t config){
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* self = uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    self->config = config;

    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_Lq(self->config.base_address, self->config.Lq);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_Ld(self->config.base_address, self->config.Ld);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Ld(self->config.base_address, self->config.SampleTime, self->config.Ld);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Lq(self->config.base_address, self->config.SampleTime, self->config.Lq);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Lx(self->config.base_address, self->config.SampleTime, self->config.Lx);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_pole_pairs(self->config.base_address, self->config.pole_pairs);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Ly(self->config.base_address, self->config.SampleTime, self->config.Ly);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_Rs(self->config.base_address, self->config.Rs);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_psiPM(self->config.base_address, self->config.psiPM);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_id_ref(self->config.base_address, self->config.id_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iq_ref(self->config.base_address, self->config.iq_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_ix_ref(self->config.base_address, self->config.ix_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iy_ref(self->config.base_address, self->config.iy_ref);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_use_AXI(self->config.base_address, self->config.use_AXI);
    return (self);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_set_AXI_values(uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* self, struct uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_AXI_values_t AXI_values){
    
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_id_k_1_AXI(self->config.base_address, AXI_values.id_k_1_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iq_k_1_AXI(self->config.base_address, AXI_values.iq_k_1_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_ix_k_1_AXI(self->config.base_address, AXI_values.ix_k_1_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iy_k_1_AXI(self->config.base_address, AXI_values.iy_k_1_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_omega_m_measured_AXI(self->config.base_address, AXI_values.omega_m_measured_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_d_voltage_per_switching_state_AXI(self->config.base_address, AXI_values.d_voltage_per_switching_state_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_q_voltage_per_switching_state_AXI(self->config.base_address, AXI_values.q_voltage_per_switching_state_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_x_voltage_per_switching_state_AXI(self->config.base_address, AXI_values.x_voltage_per_switching_state_AXI);
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_y_voltage_per_switching_state_AXI(self->config.base_address, AXI_values.y_voltage_per_switching_state_AXI);
}

float uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_get_J_AXI(uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* self){
  
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    float J_AXI = 0.0f;

    J_AXI = uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_get_J_AXI(self->config.base_address);

    return J_AXI;
}

#endif
