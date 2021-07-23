#define UZ_PMSMMODEL_MAX_INSTANCES 11U
#if UZ_PMSMMODEL_MAX_INSTANCES > 0U
#include "uz_pmsmModel.h"
#include "uz_pmsmModel_hw.h"
#include <stdbool.h>
#include "../../uz/uz_HAL.h"

struct uz_pmsmModel_t
{
    bool is_ready;
    struct uz_pmsmModel_config_t config;
};

static size_t instance_counter = 0U;
static uz_pmsmModel_t instances[UZ_PMSMMODEL_MAX_INSTANCES] = {0};

static uz_pmsmModel_t *uz_pmsmModel_allocation(void);

static uz_pmsmModel_t *uz_pmsmModel_allocation(void)
{
    uz_assert(instance_counter < UZ_PMSMMODEL_MAX_INSTANCES);
    uz_pmsmModel_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

// private function declarations
static void write_config_to_pl(uz_pmsmModel_t *self);


uz_pmsmModel_t *uz_pmsmModel_init(struct uz_pmsmModel_config_t config)
{
    uz_assert(0U != config.base_address);
    uz_assert(0U != config.ip_core_frequency_Hz);
    uz_assert(config.r_1 > 0.0f);
    uz_assert(config.L_d > 0.0f);
    uz_assert(config.L_q > 0.0f);
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

    uz_pmsmModel_t *self = uz_pmsmModel_allocation();
    self->config = config;
    write_config_to_pl(self);
    return (self);
}

void uz_pmsmModel_reset(uz_pmsmModel_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // Resets the model by writing 0.0f to all input registers
    // Then resets the integrators
    struct uz_pmsmModel_inputs_t inputs = {
        .load_torque=0.0f,
        .omega_mech_1_s=0.0f,
        .u_d_V=0.0f,
        .u_q_V=0.0f
    };
    uz_pmsmModel_set_inputs(self, inputs);
    uz_pmsmModel_hw_trigger_input_strobe(self->config.base_address);
    uz_pmsmModel_hw_write_reset(self->config.base_address, false);
    uz_sleep_useconds(1U);
    uz_pmsmModel_hw_write_reset(self->config.base_address, true);
    uz_sleep_useconds(1U);
    uz_pmsmModel_hw_write_reset(self->config.base_address, false);
}

void uz_pmsmModel_set_inputs(uz_pmsmModel_t *self, struct uz_pmsmModel_inputs_t inputs)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    //memcpy( (void *)(self->config.base_address+inputs_Data_uz_pmsm_model), &inputs,sizeof(struct uz_pmsmModel_inputs_t) );
    uz_pmsmModel_hw_write_u_d(self->config.base_address, inputs.u_d_V);
    uz_pmsmModel_hw_write_u_q(self->config.base_address, inputs.u_q_V);
    uz_pmsmModel_hw_write_omega_mech(self->config.base_address, inputs.omega_mech_1_s);
    uz_pmsmModel_hw_write_load_torque(self->config.base_address, inputs.load_torque);
}

struct uz_pmsmModel_outputs_t uz_pmsmModel_get_outputs(uz_pmsmModel_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    struct uz_pmsmModel_outputs_t outputs = {
        .i_d_A = 0.0f,
        .i_q_A = 0.0f,
        .torque_Nm = 0.0f,
        .omega_mech_1_s = 0.0f};
    outputs.i_d_A =uz_pmsmModel_hw_read_i_d(self->config.base_address);
    outputs.i_q_A =uz_pmsmModel_hw_read_i_q(self->config.base_address);
    outputs.torque_Nm =uz_pmsmModel_hw_read_torque(self->config.base_address);
    outputs.omega_mech_1_s =uz_pmsmModel_hw_read_omega_mech(self->config.base_address);
//    memcpy(&outputs, (void *)(self->config.base_address+outputs_Data_uz_pmsm_model),sizeof(struct uz_pmsmModel_outputs_t) );
    return outputs;
}

void uz_pmsmModel_trigger_input_strobe(uz_pmsmModel_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsmModel_hw_trigger_input_strobe(self->config.base_address);
}


void uz_pmsmModel_trigger_output_strobe(uz_pmsmModel_t *self){
        uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsmModel_hw_trigger_output_strobe(self->config.base_address);
}


static void write_config_to_pl(uz_pmsmModel_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_pmsmModel_hw_write_polepairs(self->config.base_address, self->config.polepairs);
    uz_pmsmModel_hw_write_r_1(self->config.base_address, self->config.r_1);
    uz_pmsmModel_hw_write_psi_pm(self->config.base_address, self->config.psi_pm);
    uz_pmsmModel_hw_write_L_d(self->config.base_address, self->config.L_d);
    uz_pmsmModel_hw_write_L_q(self->config.base_address, self->config.L_q);
    uz_pmsmModel_hw_write_friction_coefficient(self->config.base_address, self->config.friction_coefficient);
    uz_pmsmModel_hw_write_coulomb_friction_constant(self->config.base_address, self->config.coulomb_friction_constant);
    uz_pmsmModel_hw_write_inertia(self->config.base_address, self->config.inertia);
    uz_pmsmModel_hw_write_simulate_mechanical(self->config.base_address, self->config.simulate_mechanical_system);
}

#endif
