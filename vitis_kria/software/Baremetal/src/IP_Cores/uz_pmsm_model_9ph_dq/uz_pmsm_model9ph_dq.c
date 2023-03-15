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

#include "../../uz/uz_global_configuration.h"
#if UZ_PMSM_MODEL9PH_DQ_MAX_INSTANCES > 0U 
#include "uz_pmsm_model9ph_dq.h"
#include "uz_pmsm_model9ph_dq_hw.h"
#include <stdbool.h>
#include "../../uz/uz_HAL.h"


struct uz_pmsm_model9ph_dq_t
{
    bool is_ready;
    struct uz_pmsm_model9ph_dq_config_t config;
};

static size_t instance_counter = 0U;
static uz_pmsm_model9ph_dq_t instances[UZ_PMSM_MODEL9PH_DQ_MAX_INSTANCES ] = {0};

static uz_pmsm_model9ph_dq_t *uz_pmsm_model9ph_dq_allocation(void);

static uz_pmsm_model9ph_dq_t *uz_pmsm_model9ph_dq_allocation(void)
{
    uz_assert(instance_counter < UZ_PMSM_MODEL9PH_DQ_MAX_INSTANCES);
    uz_pmsm_model9ph_dq_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

// private function declarations
static void write_config_to_pl(uz_pmsm_model9ph_dq_t *self);


uz_pmsm_model9ph_dq_t *uz_pmsm_model9ph_dq_init(struct uz_pmsm_model9ph_dq_config_t config){
    uz_assert(0U != config.base_address);
    uz_assert(0U != config.ip_core_frequency_Hz);
    uz_assert(config.r_1 > 0.0f);
    uz_assert(config.inductance.d > 0.0f);
    uz_assert(config.inductance.q > 0.0f);
    uz_assert(config.inductance.x1 > 0.0f);
    uz_assert(config.inductance.y1 > 0.0f);
    uz_assert(config.inductance.x2 > 0.0f);
    uz_assert(config.inductance.y2 > 0.0f);
    uz_assert(config.inductance.x3 > 0.0f);
    uz_assert(config.inductance.y3 > 0.0f);
    uz_assert(config.inductance.zero > 0.0f);
    uz_assert(config.psi_pm >= 0.0f);
    uz_assert(config.polepairs > 0.0f);
    // If the mechanical system is not simulated, set default values
    if (!config.simulate_mechanical_system)
    {
        config.inertia = 1.0f;              // If mechanical system is not simulated, set inertia to 1.0 to prevent division by zero
        config.friction_coefficient = 1.0f; // Random default values
        config.coulomb_friction_constant = 0.0f;
    }
    uz_assert(config.inertia > 0.0f);
    uz_assert(config.coulomb_friction_constant >= 0.0f);
    uz_assert(config.friction_coefficient >= 0.0f);

    uz_pmsm_model9ph_dq_t *self = uz_pmsm_model9ph_dq_allocation();
    self->config = config;
    write_config_to_pl(self);
    return (self);
}

void uz_pmsm_model9ph_dq_reset(uz_pmsm_model9ph_dq_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // Resets the model by writing 0.0f to all input registers
    // Then resets the integrators
    uz_pmsm_model9ph_dq_set_inputs_general(self, 0.0f, 0.0f);
    // if voltages are set from PS: also reset them
    if(self->config.switch_pspl){
        uz_9ph_dq_t zero_voltages = {0};
        uz_pmsm_model9ph_dq_set_voltage(self, zero_voltages);
    }
    uz_pmsm_model9ph_hw_write_reset(self->config.base_address, false);
    uz_sleep_useconds(1U);
    uz_pmsm_model9ph_hw_write_reset(self->config.base_address, true);
    uz_sleep_useconds(1U);
    uz_pmsm_model9ph_hw_write_reset(self->config.base_address, false);
}

void uz_pmsm_model9ph_dq_set_use_axi_input(uz_pmsm_model9ph_dq_t *self, bool use_axi){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->config.switch_pspl=use_axi;
    uz_pmsm_model9ph_hw_write_switch_pspl(self->config.base_address, self->config.switch_pspl);
}

void uz_pmsm_model9ph_dq_set_inputs_general(uz_pmsm_model9ph_dq_t *self, float omega_mech, float load_torque){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsm_model9ph_hw_write_omega_mech(self->config.base_address, omega_mech);
    uz_pmsm_model9ph_hw_write_load_torque(self->config.base_address, load_torque);
}

struct uz_pmsm_model9ph_dq_outputs_general_t uz_pmsm_model9ph_dq_get_outputs_general(uz_pmsm_model9ph_dq_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    struct uz_pmsm_model9ph_dq_outputs_general_t outputs = {
        .torque = 0.0f,
        .omega_mech = 0.0f,
    	.theta_el = 0.0f};
    outputs.torque = uz_pmsm_model9ph_hw_read_torque(self->config.base_address);
    outputs.omega_mech = uz_pmsm_model9ph_hw_read_omega_mech(self->config.base_address);
    outputs.theta_el = uz_pmsm_model9ph_hw_read_theta_el(self->config.base_address);
    return outputs;
}

void uz_pmsm_model9ph_dq_set_voltage(uz_pmsm_model9ph_dq_t *self, uz_9ph_dq_t voltages){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsm_model9ph_hw_write_u_d(self->config.base_address, voltages.d);
    uz_pmsm_model9ph_hw_write_u_q(self->config.base_address, voltages.q);
    uz_pmsm_model9ph_hw_write_u_x1(self->config.base_address, voltages.x1);
    uz_pmsm_model9ph_hw_write_u_y1(self->config.base_address, voltages.y1);
    uz_pmsm_model9ph_hw_write_u_x2(self->config.base_address, voltages.x2);
    uz_pmsm_model9ph_hw_write_u_y2(self->config.base_address, voltages.y2);
    uz_pmsm_model9ph_hw_write_u_x3(self->config.base_address, voltages.x3);
    uz_pmsm_model9ph_hw_write_u_y3(self->config.base_address, voltages.y3);
    uz_pmsm_model9ph_hw_write_u_zero(self->config.base_address, voltages.zero);
    uz_pmsm_model9ph_trigger_voltage_input_strobe(self);
}

void uz_pmsm_model9ph_dq_set_voltage_unsafe(uz_pmsm_model9ph_dq_t *self, uz_9ph_dq_t voltages){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsm_model9ph_hw_write_voltage_dq_unsafe(self->config.base_address,voltages);
}

uz_9ph_dq_t uz_pmsm_model9ph_dq_get_input_voltages(uz_pmsm_model9ph_dq_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_9ph_dq_t out = {0};
    uz_pmsm_model9ph_trigger_voltage_output_strobe(self);
    out.d = uz_pmsm_model9ph_hw_read_u_d(self->config.base_address);
    out.q = uz_pmsm_model9ph_hw_read_u_q(self->config.base_address);
    out.x1 = uz_pmsm_model9ph_hw_read_u_x1(self->config.base_address);
    out.y1 = uz_pmsm_model9ph_hw_read_u_y1(self->config.base_address);
    out.x2 = uz_pmsm_model9ph_hw_read_u_x2(self->config.base_address);
    out.y2 = uz_pmsm_model9ph_hw_read_u_y2(self->config.base_address);
    out.x3 = uz_pmsm_model9ph_hw_read_u_x3(self->config.base_address);
    out.y3 = uz_pmsm_model9ph_hw_read_u_y3(self->config.base_address);
    out.zero = uz_pmsm_model9ph_hw_read_u_zero(self->config.base_address);
    return out;
}

uz_9ph_dq_t uz_pmsm_model9ph_dq_get_input_voltages_unsafe(uz_pmsm_model9ph_dq_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_pmsm_model9ph_hw_read_voltage_dq_unsafe(self->config.base_address);
}

uz_9ph_dq_t uz_pmsm_model9ph_dq_get_output_currents(uz_pmsm_model9ph_dq_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_9ph_dq_t out = {0};
    uz_pmsm_model9ph_trigger_current_output_strobe(self);
    out.d = uz_pmsm_model9ph_hw_read_i_d(self->config.base_address);
    out.q =  uz_pmsm_model9ph_hw_read_i_q(self->config.base_address);
    out.x1 = uz_pmsm_model9ph_hw_read_i_x1(self->config.base_address);
    out.y1 = uz_pmsm_model9ph_hw_read_i_y1(self->config.base_address);
    out.x2 = uz_pmsm_model9ph_hw_read_i_x2(self->config.base_address);
    out.y2 = uz_pmsm_model9ph_hw_read_i_y2(self->config.base_address);
    out.x3 = uz_pmsm_model9ph_hw_read_i_x3(self->config.base_address);
    out.y3 = uz_pmsm_model9ph_hw_read_i_y3(self->config.base_address);
    out.zero = uz_pmsm_model9ph_hw_read_i_zero(self->config.base_address);
    return out;
}

uz_9ph_dq_t uz_pmsm_model9ph_dq_get_output_currents_unsafe(uz_pmsm_model9ph_dq_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_pmsm_model9ph_hw_read_currents_dq_unsafe(self->config.base_address);
}

static void write_config_to_pl(uz_pmsm_model9ph_dq_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsm_model9ph_hw_write_polepairs(self->config.base_address, self->config.polepairs);
    uz_pmsm_model9ph_hw_write_r_1(self->config.base_address, self->config.r_1);
    uz_pmsm_model9ph_hw_write_psi_pm(self->config.base_address, self->config.psi_pm);
    uz_pmsm_model9ph_hw_write_L_d(self->config.base_address, self->config.inductance.d);
    uz_pmsm_model9ph_hw_write_L_q(self->config.base_address, self->config.inductance.q);
    uz_pmsm_model9ph_hw_write_L_x1(self->config.base_address, self->config.inductance.x1);
    uz_pmsm_model9ph_hw_write_L_y1(self->config.base_address, self->config.inductance.y1);
    uz_pmsm_model9ph_hw_write_L_x2(self->config.base_address, self->config.inductance.x2);
    uz_pmsm_model9ph_hw_write_L_y2(self->config.base_address, self->config.inductance.y2);
    uz_pmsm_model9ph_hw_write_L_x3(self->config.base_address, self->config.inductance.x3);
    uz_pmsm_model9ph_hw_write_L_y3(self->config.base_address, self->config.inductance.y3);
    uz_pmsm_model9ph_hw_write_L_zero(self->config.base_address, self->config.inductance.zero);
    uz_pmsm_model9ph_hw_write_friction_coefficient(self->config.base_address, self->config.friction_coefficient);
    uz_pmsm_model9ph_hw_write_coulomb_friction_constant(self->config.base_address, self->config.coulomb_friction_constant);
    uz_pmsm_model9ph_hw_write_inertia(self->config.base_address, self->config.inertia);
    uz_pmsm_model9ph_hw_write_simulate_mechanical(self->config.base_address, self->config.simulate_mechanical_system);
    uz_pmsm_model9ph_hw_write_switch_pspl(self->config.base_address, self->config.switch_pspl);
}

void uz_pmsm_model9ph_trigger_voltage_input_strobe(uz_pmsm_model9ph_dq_t *self){
        uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsm_model9ph_trigger_voltage_input_strobe_hw(self->config.base_address);
}

void uz_pmsm_model9ph_trigger_voltage_output_strobe(uz_pmsm_model9ph_dq_t *self){
        uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsm_model9ph_trigger_voltage_output_strobe_hw(self->config.base_address);
}

void uz_pmsm_model9ph_trigger_current_output_strobe(uz_pmsm_model9ph_dq_t *self){
        uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsm_model9ph_trigger_current_output_strobe_hw(self->config.base_address);
}

#endif
