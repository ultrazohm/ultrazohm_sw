#include "../../uz/uz_global_configuration.h"
#if UZ_PHASE_VOLTAGES_PER_SWITCHING_STATE_FCS_MPC_6PHASE_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_phase_voltages_per_switching_state_fcs_mpc_6phase.h"
#include "uz_phase_voltages_per_switching_state_fcs_mpc_6phase_hw.h"

struct uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t {
    bool is_ready;
    struct uz_phase_voltages_per_switching_state_fcs_mpc_6phase_config_t config;
    struct uz_phase_voltages_per_switching_state_fcs_mpc_6phase_AXI_values_t AXI_values;
};

static uint32_t instance_counter = 0U;
static uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t instances[UZ_PHASE_VOLTAGES_PER_SWITCHING_STATE_FCS_MPC_6PHASE_MAX_INSTANCES] = { 0 };

static uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* uz_phase_voltages_per_switching_state_fcs_mpc_6phase_allocation(void);

static uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* uz_phase_voltages_per_switching_state_fcs_mpc_6phase_allocation(void){
    uz_assert(instance_counter < UZ_PHASE_VOLTAGES_PER_SWITCHING_STATE_FCS_MPC_6PHASE_MAX_INSTANCES);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* uz_phase_voltages_per_switching_state_fcs_mpc_6phase_init(struct uz_phase_voltages_per_switching_state_fcs_mpc_6phase_config_t config){
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* self = uz_phase_voltages_per_switching_state_fcs_mpc_6phase_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    self->config = config;

    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_offset(self->config.base_address, self->config.theta_el_offset);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_u_dc_link_voltage(self->config.base_address, self->config.u_dc_link_voltage);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_use_AXI(self->config.base_address, self->config.use_AXI);

    return (self);
}

void  uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_AXI_values(uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* self, struct uz_phase_voltages_per_switching_state_fcs_mpc_6phase_AXI_values_t AXI_values){
    
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_AXI(self->config.base_address, AXI_values.theta_el_AXI);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_Index_AXI(self->config.base_address, AXI_values.Index_AXI);
}

uz_6ph_dvoltage_qvoltage_xvoltage_yvoltage_t uz_phase_voltages_per_switching_state_fcs_mpc_6phase_read_dvoltage_qvoltage_xvoltage_yvoltage(uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* self){

    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_6ph_dvoltage_qvoltage_xvoltage_yvoltage_t voltage = {0};

    voltage.d = uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_d_voltage_per_switching_state(self->config.base_address);
    voltage.q = uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_q_voltage_per_switching_state(self->config.base_address);
    voltage.x = uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_x_voltage_per_switching_state(self->config.base_address);
    voltage.y = uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_y_voltage_per_switching_state(self->config.base_address);

    return voltage;
}

#endif