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
#if UZ_PMSM_MODEL3PH_DQ_MAX_INSTANCES > 0U
#include "uz_pmsm_model3ph_dq.h"
#include "uz_pmsm_model3ph_dq_hw.h"
#include <stdbool.h>
#include "../../uz/uz_HAL.h"

struct uz_pmsm_model3ph_t
{
    bool is_ready;
    struct uz_pmsm_model3ph_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_pmsm_model3ph_t instances[UZ_PMSM_MODEL3PH_DQ_MAX_INSTANCES] = {0};

static uz_pmsm_model3ph_t *uz_pmsm_model3ph_allocation(void);

static uz_pmsm_model3ph_t *uz_pmsm_model3ph_allocation(void)
{
    uz_assert(instance_counter < UZ_PMSM_MODEL3PH_DQ_MAX_INSTANCES);
    uz_pmsm_model3ph_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

// private function declarations
static void write_config_to_pl(uz_pmsm_model3ph_t *self);


uz_pmsm_model3ph_t *uz_pmsm_model3ph_init(struct uz_pmsm_model3ph_config_t config)
{
    uz_assert(0U != config.base_address);
    uz_assert(0U != config.ip_core_frequency_Hz);
    // If the mechanical system is not simulated, set default values
    if (!config.simulate_mechanical_system)
    {
        config.pmsm.J_kg_m_squared = 1.0f;              // If mechanical system is not simulated, set inertia to 1.0 to prevent division by zero
        config.friction_coefficient = 1.0f; // Random default values
        config.coulomb_friction_constant = 0.0f;
    }
    uz_PMSM_config_assert(config.pmsm);
    uz_assert(config.coulomb_friction_constant >= 0.0f);
    uz_assert(config.friction_coefficient >= 0.0f);

    uz_pmsm_model3ph_t *self = uz_pmsm_model3ph_allocation();
    self->config = config;
    write_config_to_pl(self);
    return (self);
}

void uz_pmsm_model3ph_reset(uz_pmsm_model3ph_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // Resets the model by writing 0.0f to all input registers
    // Then resets the integrators
    struct uz_pmsm_model3ph_inputs_t inputs = {
        .load_torque=0.0f,
        .omega_mech_1_s=0.0f,
        .voltages.d=0.0f,
        .voltages.q=0.0f
    };
    uz_pmsm_model3ph_set_inputs(self, inputs);
    uz_pmsm_model3ph_hw_trigger_input_strobe(self->config.base_address);
    uz_pmsm_model3ph_hw_write_reset(self->config.base_address, false);
    uz_sleep_useconds(1U);
    uz_pmsm_model3ph_hw_write_reset(self->config.base_address, true);
    uz_sleep_useconds(1U);
    uz_pmsm_model3ph_hw_write_reset(self->config.base_address, false);
}

void uz_pmsm_model3ph_set_inputs(uz_pmsm_model3ph_t *self, struct uz_pmsm_model3ph_inputs_t inputs)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    //memcpy( (void *)(self->config.base_address+inputs_Data_uz_pmsm_model), &inputs,sizeof(struct uz_pmsm_model3ph_inputs_t) );
    uz_pmsm_model3ph_hw_write_v_d(self->config.base_address, inputs.voltages.d);
    uz_pmsm_model3ph_hw_write_v_q(self->config.base_address, inputs.voltages.q);
    uz_pmsm_model3ph_hw_write_omega_mech(self->config.base_address, inputs.omega_mech_1_s);
    uz_pmsm_model3ph_hw_write_load_torque(self->config.base_address, inputs.load_torque);
}

struct uz_pmsm_model3ph_outputs_t uz_pmsm_model3ph_get_outputs(uz_pmsm_model3ph_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    struct uz_pmsm_model3ph_outputs_t outputs = {
        .currents.d = 0.0f,
        .currents.q = 0.0f,
        .torque_Nm = 0.0f,
        .omega_mech_1_s = 0.0f,
        .theta_el = 0.0f};
    outputs.currents.d =uz_pmsm_model3ph_hw_read_i_d(self->config.base_address);
    outputs.currents.q =uz_pmsm_model3ph_hw_read_i_q(self->config.base_address);
    outputs.torque_Nm =uz_pmsm_model3ph_hw_read_torque(self->config.base_address);
    outputs.omega_mech_1_s =uz_pmsm_model3ph_hw_read_omega_mech(self->config.base_address);
    outputs.theta_el =uz_pmsm_model3ph_hw_read_theta_el(self->config.base_address);
    return outputs;
}

void uz_pmsm_model3ph_trigger_input_strobe(uz_pmsm_model3ph_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsm_model3ph_hw_trigger_input_strobe(self->config.base_address);
}


void uz_pmsm_model3ph_trigger_output_strobe(uz_pmsm_model3ph_t *self){
        uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsm_model3ph_hw_trigger_output_strobe(self->config.base_address);
}


static void write_config_to_pl(uz_pmsm_model3ph_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsm_model3ph_hw_write_polepairs(self->config.base_address, self->config.pmsm.polePairs);
    uz_pmsm_model3ph_hw_write_r_1(self->config.base_address, self->config.pmsm.R_ph_Ohm);
    uz_pmsm_model3ph_hw_write_psi_pm(self->config.base_address, self->config.pmsm.Psi_PM_Vs);
    uz_pmsm_model3ph_hw_write_L_d(self->config.base_address, self->config.pmsm.Ld_Henry);
    uz_pmsm_model3ph_hw_write_L_q(self->config.base_address, self->config.pmsm.Lq_Henry);
    uz_pmsm_model3ph_hw_write_friction_coefficient(self->config.base_address, self->config.friction_coefficient);
    uz_pmsm_model3ph_hw_write_coulomb_friction_constant(self->config.base_address, self->config.coulomb_friction_constant);
    uz_pmsm_model3ph_hw_write_inertia(self->config.base_address, self->config.pmsm.J_kg_m_squared);
    uz_pmsm_model3ph_hw_write_simulate_mechanical(self->config.base_address, self->config.simulate_mechanical_system);
    uz_pmsm_model3ph_hw_write_switch_pspl(self->config.base_address, self->config.switch_pspl);
}

uz_3ph_dq_t uz_pmsm_model3ph_dq_get_input_voltages(uz_pmsm_model3ph_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_3ph_dq_t out = {0};
    uz_pmsm_model3ph_hw_trigger_fb_strobe(self->config.base_address);
    out.d = uz_pmsm_model3ph_hw_read_v_d(self->config.base_address);
    out.q = uz_pmsm_model3ph_hw_read_v_q(self->config.base_address);
    out.zero = 0.0f;
    return out;
}

#endif
