#include "../../uz/uz_global_configuration.h"
#if UZ_JL_PMSMMODEL_MAX_INSTANCES > 0U
#include "uz_JL_pmsmModel.h"
#include "uz_JL_pmsmModel_hw.h"
#include <stdbool.h> 
#include "../../uz/uz_HAL.h"

struct uz_JL_pmsmModel_t {
    bool is_ready;
    struct uz_JL_pmsmModel_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_JL_pmsmModel_t instances[UZ_JL_PMSMMODEL_MAX_INSTANCES] = { 0 };

static uz_JL_pmsmModel_t* uz_JL_pmsmModel_allocation(void);

static uz_JL_pmsmModel_t* uz_JL_pmsmModel_allocation(void){
    uz_assert(instance_counter < UZ_JL_PMSMMODEL_MAX_INSTANCES);
    uz_JL_pmsmModel_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

// uz_JL_pmsmModel_t* uz_JL_pmsmModel_init() {
//     uz_JL_pmsmModel_t* self = uz_JL_pmsmModel_allocation();
//     return (self);
// }

// private function declarations
static void write_config_to_pl(uz_JL_pmsmModel_t *self);

uz_JL_pmsmModel_t *uz_JL_pmsmModel_init(struct uz_JL_pmsmModel_config_t config)
{
    uz_assert(0U != config.base_address);
    uz_assert(0U != config.ip_core_frequency_Hz);
    uz_assert(config.r_1 > 0.0f);
    uz_assert(config.L_d > 0.0f);
    uz_assert(config.L_q > 0.0f);
    uz_assert(config.psi_pm >= 0.0f);
    uz_assert(config.mot_p > 0.0f);
    uz_assert(config.mot_J > 0.0f);
    // uz_assert(config.M_N > 0.0f);
    // uz_assert(config.n_N > 0.0f);
    // uz_assert(config.i_max > 0.0f);
    // If the mechanical system is not simulated, set default values

    uz_JL_pmsmModel_t *self = uz_JL_pmsmModel_allocation();
    self->config = config;
    write_config_to_pl(self);
    return (self);
}

void uz_JL_pmsmModel_reset(uz_JL_pmsmModel_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // Resets the model by writing 0.0f to all input registers
    // Then resets the integrators
    struct uz_JL_pmsmModel_inputs_t inputs = {
        .bremse=false,
        .Last_J=0.0f,
        .Last_M=0.0f,
        .SwitchUabc_dq = false,
        .Ud = 0.0f,
        .Uq = 0.0f,
    };
    uz_JL_pmsmModel_set_inputs(self, inputs);
    // uz_JL_pmsmModel_hw_trigger_input_strobe(self->config.base_address);
    uz_JL_pmsmModel_hw_write_reset(self->config.base_address, false);
    uz_sleep_useconds(1U);
    uz_JL_pmsmModel_hw_write_reset(self->config.base_address, true);
    uz_sleep_useconds(1U);
    uz_JL_pmsmModel_hw_write_reset(self->config.base_address, false);
}

void uz_JL_pmsmModel_set_inputs(uz_JL_pmsmModel_t *self, struct uz_JL_pmsmModel_inputs_t inputs)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    //memcpy( (void *)(self->config.base_address+inputs_Data_uz_pmsm_model), &inputs,sizeof(struct uz_pmsmModel_inputs_t) );
    uz_JL_pmsmModel_hw_write_bremse(self->config.base_address, inputs.bremse);
    uz_JL_pmsmModel_hw_write_Last_J(self->config.base_address, inputs.Last_J);
    uz_JL_pmsmModel_hw_write_Last_M(self->config.base_address, inputs.Last_M);
    uz_JL_pmsmModel_hw_write_switchUabc_dq(self->config.base_address, inputs.SwitchUabc_dq);
    float Udq[2] = {inputs.Ud, inputs.Uq};
    uz_JL_pmsmModel_hw_write_Udq(self->config.base_address, Udq);
}

struct uz_JL_pmsmModel_outputs_t uz_JL_pmsmModel_get_outputs(uz_JL_pmsmModel_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    struct uz_JL_pmsmModel_outputs_t outputs = {
        .i_a_A = 0.0f,
        .i_b_A = 0.0f,
        .i_c_A = 0.0f,
        .torque_Nm = 0.0f,
        .omega_mech_1_s = 0.0f,
        .phi_mech_rad = 0.0f};
    outputs.i_a_A =uz_JL_pmsmModel_hw_read_I_a(self->config.base_address);
    outputs.i_b_A =uz_JL_pmsmModel_hw_read_I_b(self->config.base_address);
    outputs.i_c_A =uz_JL_pmsmModel_hw_read_I_c(self->config.base_address);
    outputs.torque_Nm =uz_JL_pmsmModel_hw_read_torque(self->config.base_address);
    outputs.omega_mech_1_s = uz_JL_pmsmModel_hw_read_omega_mech(self->config.base_address);
    outputs.phi_mech_rad =uz_JL_pmsmModel_hw_read_phi_mech(self->config.base_address);
    return outputs;
}

// void uz_JL_pmsmModel_trigger_input_strobe(uz_JL_pmsmModel_t *self){
//     uz_assert_not_NULL(self);
//     uz_assert(self->is_ready);
//     uz_JL_pmsmModel_hw_trigger_input_strobe(self->config.base_address);
// }

// void uz_JL_pmsmModel_trigger_output_strobe(uz_JL_pmsmModel_t *self){
//     uz_assert_not_NULL(self);
//     uz_assert(self->is_ready);
//     uz_JL_pmsmModel_hw_trigger_output_strobe(self->config.base_address);
// }


static void write_config_to_pl(uz_JL_pmsmModel_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_pmsmModel_hw_write_R1(self->config.base_address, self->config.r_1);
    uz_JL_pmsmModel_hw_write_L_d(self->config.base_address,  self->config.L_d);
    uz_JL_pmsmModel_hw_write_L_q(self->config.base_address,  self->config.L_q);
    uz_JL_pmsmModel_hw_write_psi_pm(self->config.base_address,  self->config.psi_pm);
    uz_JL_pmsmModel_hw_write_mot_p(self->config.base_address,  self->config.mot_p);
    uz_JL_pmsmModel_hw_write_mot_J(self->config.base_address,  self->config.mot_J);
    // uz_JL_pmsmModel_hw_write_M_N(self->config.base_address,  self->config.M_N);
    // uz_JL_pmsmModel_hw_write_n_N(self->config.base_address,  self->config.n_N);
    // uz_JL_pmsmModel_hw_write_I_max(self->config.base_address,  self->config.i_max);
}

#endif

