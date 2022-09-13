#include "../../uz/uz_global_configuration.h"
#if UZ_MIN_COST_FUNCTION_AND_VOPT_FCS_MPC_6PHASE_PMSM_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM.h"
#include "uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw.h"

struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t {
    bool is_ready;
    struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_config_t config;
    struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_AXI_values_t AXI_values;
};

static uint32_t instance_counter = 0U;
static uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t instances[UZ_MIN_COST_FUNCTION_AND_VOPT_FCS_MPC_6PHASE_PMSM_MAX_INSTANCES] = { 0 };

static uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_allocation(void);

static uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_allocation(void){
    uz_assert(instance_counter < UZ_MIN_COST_FUNCTION_AND_VOPT_FCS_MPC_6PHASE_PMSM_MAX_INSTANCES);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_init(struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_config_t config){
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* self = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    self->config = config;

   uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_use_AXI(self->config.base_address, self->config.use_AXI);
   return (self);
}

void uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_set_AXI_values(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* self, struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_AXI_values_t AXI_values){
    
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_J_in_AXI(self->config.base_address, AXI_values.J_in_AXI);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_Index_in_AXI(self->config.base_address, AXI_values.Index_in_AXI);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_d_phase_voltage_per_switchimng_state_AXI(self->config.base_address, AXI_values.d_phase_voltage_per_switchimng_state_AXI);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_q_phase_voltage_per_switchimng_state_AXI(self->config.base_address, AXI_values.q_phase_voltage_per_switchimng_state_AXI);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_x_phase_voltage_per_switchimng_state_AXI(self->config.base_address, AXI_values.x_phase_voltage_per_switchimng_state_AXI);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_y_phase_voltage_per_switchimng_state_AXI(self->config.base_address, AXI_values.y_phase_voltage_per_switchimng_state_AXI);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_valid_in_AXI(self->config.base_address, AXI_values.valid_in_AXI);
}

uz_6ph_optimal_dvoltage_qvoltage_xvoltage_yvoltage_t uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_last_applied_optimal_voltage_d_q_x_y(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* self){

    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_6ph_optimal_dvoltage_qvoltage_xvoltage_yvoltage_t voltage = {0};

    voltage.d = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_ud_AXI(self->config.base_address);
    voltage.q = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_uq_AXI(self->config.base_address);
    voltage.x = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_ux_AXI(self->config.base_address);
    voltage.y = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_uy_AXI(self->config.base_address);

    return voltage;
}

_Bool uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_done_complete_AXI(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* self){
    
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    _Bool done_complete = 0;

    done_complete = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_done_complete_AXI(self->config.base_address);

    return done_complete;
}

int32_t uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_Index_out(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* self){
    
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    int32_t Index_out = 0;

    Index_out = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_Index_out_AXI(self->config.base_address);

    return Index_out;
}

#endif