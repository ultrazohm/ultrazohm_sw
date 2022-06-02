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
#if UZ_PMSM_MODEL_9ph_MAX_INSTANCES > 0U
#include "uz_pmsm_model_9ph.h"
#include "uz_pmsm_model_9ph_hw.h"
#include <stdbool.h>
#include "../../uz/uz_HAL.h"


struct uz_pmsm_model_9ph_t
{
    bool is_ready;
    struct uz_pmsm_model_9ph_config_t config;
};

static size_t instance_counter = 0U;
static uz_pmsm_model_9ph_t instances[UZ_PMSM_MODEL_9ph_MAX_INSTANCES ] = {0};

static uz_pmsm_model_9ph_t *uz_pmsm_model_9ph_allocation(void);

static uz_pmsm_model_9ph_t *uz_pmsm_model_9ph_allocation(void)
{
    uz_assert(instance_counter < UZ_PMSM_MODEL_9ph_MAX_INSTANCES);
    uz_pmsm_model_9ph_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

// private function declarations
static void write_config_to_pl(uz_pmsm_model_9ph_t *self);


uz_pmsm_model_9ph_t *uz_pmsm_model_9ph_init(struct uz_pmsm_model_9ph_config_t config)
{
    uz_assert(0U != config.base_address);
    uz_assert(0U != config.ip_core_frequency_Hz);
    uz_assert(config.r_1 > 0.0f);
    uz_assert(config.L_d > 0.0f);
    uz_assert(config.L_q > 0.0f);
    uz_assert(config.L_z1 > 0.0f);
    uz_assert(config.L_z2 > 0.0f);
    uz_assert(config.L_x1 > 0.0f);
    uz_assert(config.L_y1 > 0.0f);
    uz_assert(config.L_x2 > 0.0f);
    uz_assert(config.L_y2 > 0.0f);
    uz_assert(config.L_z3 > 0.0f);
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

    uz_pmsm_model_9ph_t *self = uz_pmsm_model_9ph_allocation();
    self->config = config;
    write_config_to_pl(self);
    return (self);
}

void uz_pmsm_model_9ph_reset(uz_pmsm_model_9ph_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // Resets the model by writing 0.0f to all input registers
    // Then resets the integrators
    struct uz_pmsm_model_9ph_inputs_general_t inputs_general = {
        .load_torque=0.0f,
        .omega_mech_1_s=0.0f};
    uz_pmsm_model_9ph_set_inputs_general(self, inputs_general);
    uz_pmsm_model_9ph_trigger_input_general_strobe(self);
    uz_pmsm_model_9ph_hw_write_reset(self->config.base_address, false);
    uz_sleep_useconds(1U);
    uz_pmsm_model_9ph_hw_write_reset(self->config.base_address, true);
    uz_sleep_useconds(1U);
    uz_pmsm_model_9ph_hw_write_reset(self->config.base_address, false);
}

void uz_pmsm_model_9ph_set_inputs_general(uz_pmsm_model_9ph_t *self, struct uz_pmsm_model_9ph_inputs_general_t inputs)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    //memcpy( (void *)(self->config.base_address+inputs_Data_uz_pmsm_model), &inputs,sizeof(struct uz_pmsm_model_9ph_inputs_t) );
    uz_pmsm_model_9ph_hw_write_omega_mech(self->config.base_address, inputs.omega_mech_1_s);
    uz_pmsm_model_9ph_hw_write_load_torque(self->config.base_address, inputs.load_torque);
}
struct uz_pmsm_model_9ph_outputs_general_t uz_pmsm_model_9ph_get_outputs_general(uz_pmsm_model_9ph_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    struct uz_pmsm_model_9ph_outputs_general_t outputs = {
        .torque_Nm = 0.0f,
        .omega_mech_1_s = 0.0f,
    	.theta_el = 0.0f,
        .u_d = 0.0f,
        .u_q = 0.0f};
    outputs.torque_Nm = uz_pmsm_model_9ph_hw_read_torque(self->config.base_address);
    outputs.omega_mech_1_s = uz_pmsm_model_9ph_hw_read_omega_mech(self->config.base_address);
    outputs.theta_el = uz_pmsm_model_9ph_hw_read_theta_el(self->config.base_address);
    outputs.u_d = uz_pmsm_model_9ph_hw_read_u_d(self->config.base_address);
    outputs.u_q = uz_pmsm_model_9ph_hw_read_u_q(self->config.base_address);
    return outputs;
}

uz_9ph_abc_t uz_pmsm_model_9ph_get_output_currents(uz_pmsm_model_9ph_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_9ph_abc_t outputs = {
        .a1 = 0.0f,
        .b1 = 0.0f,
        .c1 = 0.0f,
        .a2 = 0.0f,
        .b2 = 0.0f,
        .c2 = 0.0f,
        .a3 = 0.0f,
        .b3 = 0.0f,
        .c3 = 0.0f};
    outputs.a1 = uz_pmsm_model_9ph_hw_read_i_a1(self->config.base_address);
    outputs.b1 = uz_pmsm_model_9ph_hw_read_i_b1(self->config.base_address);
    outputs.c1 = uz_pmsm_model_9ph_hw_read_i_c1(self->config.base_address);
    outputs.a2 = uz_pmsm_model_9ph_hw_read_i_a2(self->config.base_address);
    outputs.b2 = uz_pmsm_model_9ph_hw_read_i_b2(self->config.base_address);
    outputs.c2 = uz_pmsm_model_9ph_hw_read_i_c2(self->config.base_address);
    outputs.a3 = uz_pmsm_model_9ph_hw_read_i_a3(self->config.base_address);
    outputs.b3 = uz_pmsm_model_9ph_hw_read_i_b3(self->config.base_address);
    outputs.c3 = uz_pmsm_model_9ph_hw_read_i_c3(self->config.base_address);
    return outputs;
}


void uz_pmsm_model_9ph_trigger_input_general_strobe(uz_pmsm_model_9ph_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsm_model_9ph_hw_trigger_input_general_strobe(self->config.base_address);
}

void uz_pmsm_model_9ph_trigger_output_general_strobe(uz_pmsm_model_9ph_t *self){
        uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsm_model_9ph_hw_trigger_output_general_strobe(self->config.base_address);
}

void uz_pmsm_model_9ph_trigger_output_currents_strobe(uz_pmsm_model_9ph_t *self){
        uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsm_model_9ph_hw_trigger_output_currents_strobe(self->config.base_address);
}


static void write_config_to_pl(uz_pmsm_model_9ph_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsm_model_9ph_hw_write_polepairs(self->config.base_address, self->config.polepairs);
    uz_pmsm_model_9ph_hw_write_r_1(self->config.base_address, self->config.r_1);
    uz_pmsm_model_9ph_hw_write_psi_pm(self->config.base_address, self->config.psi_pm);
    uz_pmsm_model_9ph_hw_write_L_d(self->config.base_address, self->config.L_d);
    uz_pmsm_model_9ph_hw_write_L_q(self->config.base_address, self->config.L_q);
    uz_pmsm_model_9ph_hw_write_L_z1(self->config.base_address, self->config.L_z1);
    uz_pmsm_model_9ph_hw_write_L_z2(self->config.base_address, self->config.L_z2);
    uz_pmsm_model_9ph_hw_write_L_x1(self->config.base_address, self->config.L_x1);
    uz_pmsm_model_9ph_hw_write_L_y1(self->config.base_address, self->config.L_y1);
    uz_pmsm_model_9ph_hw_write_L_x2(self->config.base_address, self->config.L_x2);
    uz_pmsm_model_9ph_hw_write_L_y2(self->config.base_address, self->config.L_y2);
    uz_pmsm_model_9ph_hw_write_L_z3(self->config.base_address, self->config.L_z3);
    uz_pmsm_model_9ph_hw_write_friction_coefficient(self->config.base_address, self->config.friction_coefficient);
    uz_pmsm_model_9ph_hw_write_coulomb_friction_constant(self->config.base_address, self->config.coulomb_friction_constant);
    uz_pmsm_model_9ph_hw_write_inertia(self->config.base_address, self->config.inertia);
    uz_pmsm_model_9ph_hw_write_simulate_mechanical(self->config.base_address, self->config.simulate_mechanical_system);
    uz_pmsm_model_9ph_hw_write_switch_pspl(self->config.base_address, self->config.switch_pspl);
    uz_pmsm_model_9ph_hw_write_control_dq_abc(self->config.base_address, self->config.control_dq_abc);
}

#endif
