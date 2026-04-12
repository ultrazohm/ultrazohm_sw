#include "../uz_global_configuration.h"
#if UZ_BUCK_CONTROL_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_buck_control.h"
#include "../uz_signals/uz_signals.h"

typedef struct uz_buck_control_t
{
    bool is_ready;
    struct buck_control_config config;
    float duty_cycle;
    struct uz_PI_Controller *input_current_controller;
    struct uz_PI_Controller *output_voltage_controller;
    struct uz_PI_Controller *output_current_controller;
} uz_buck_control_t;

static uint32_t instance_counter = 0U;
static uz_buck_control_t instances[UZ_BUCK_CONTROL_MAX_INSTANCES] = {0};

static uz_buck_control_t *uz_buck_control_allocation(void);

static uz_buck_control_t *uz_buck_control_allocation(void)
{
    uz_assert(instance_counter < UZ_BUCK_CONTROL_MAX_INSTANCES);
    uz_buck_control_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_buck_control_t *uz_buck_control_init(struct buck_control_config external_config)
{
    uz_buck_control_t *self = uz_buck_control_allocation();
    self->config = external_config;
    uz_assert(self->config.sampling_frequency_Hz > 0.0f);
    uz_assert(self->config.control_mode != 0); // User must select available control mode

    struct uz_PI_Controller_config input_current_controller_config = {
        .Kp = self->config.input_current_controller_kp,
        .Ki = self->config.input_current_controller_ki,
        .lower_limit = self->config.input_current_controller_min_control_signal,
        .upper_limit = self->config.input_current_controller_max_control_signal,
        .type = UZ_PI_PARALLEL,
        .samplingTime_sec = 1.0f / self->config.sampling_frequency_Hz};

    struct uz_PI_Controller_config output_voltage_controller_config = {
        .Kp = self->config.output_voltage_controller_kp,
        .Ki = self->config.output_voltage_controller_ki,
        .lower_limit = self->config.output_voltage_controller_min_control_signal,
        .upper_limit = self->config.output_voltage_controller_max_control_signal,
        .type = UZ_PI_PARALLEL,
        .samplingTime_sec = 1.0f / self->config.sampling_frequency_Hz};

    struct uz_PI_Controller_config output_current_controller_config = {
        .Kp = self->config.output_current_controller_kp,
        .Ki = self->config.output_current_controller_ki,
        .lower_limit = self->config.output_current_controller_min_control_signal,
        .upper_limit = self->config.output_current_controller_max_control_signal,
        .type = UZ_PI_PARALLEL,
        .samplingTime_sec = 1.0f / self->config.sampling_frequency_Hz};

    self->input_current_controller = uz_PI_Controller_init(input_current_controller_config);
    self->output_voltage_controller = uz_PI_Controller_init(output_voltage_controller_config);
    self->output_current_controller = uz_PI_Controller_init(output_current_controller_config);
    self->duty_cycle = 0.0f;

    return (self);
}

float uz_buck_control_sample(uz_buck_control_t *self, struct buck_control_ref_val ref_val, struct buck_control_act_val act_val)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    switch (self->config.control_mode)
    {
    case uz_buck_input_current_mode:
        ref_val.ref_output_voltage_Volt = uz_buck_input_current_control(self, ref_val.ref_input_current_Ampere, act_val.input_current_Ampere);
        ref_val.ref_output_current_Ampere = uz_buck_output_voltage_control(self, ref_val, act_val);
        self->duty_cycle = uz_buck_output_current_control(self, ref_val, act_val); // LOC triggers an assertion
        break;
    case uz_buck_output_voltage_mode:
        ref_val.ref_output_current_Ampere = uz_buck_output_voltage_control(self, ref_val, act_val);
        self->duty_cycle = uz_buck_output_current_control(self, ref_val, act_val);
        break;
    case uz_buck_output_current_mode:
        self->duty_cycle = uz_buck_output_current_control(self, ref_val, act_val);
        break;
    default:
        uz_assert(false);
    }

    return (self->duty_cycle);
}

float uz_buck_input_current_control(uz_buck_control_t *self, float input_current_reference, float input_current_actual)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    input_current_reference = uz_signals_saturation(input_current_reference, self->config.input_current_controller_max_reference, self->config.input_current_controller_min_reference);
    float control_voltage = uz_PI_Controller_sample(self->input_current_controller, input_current_reference, input_current_actual, false);
    return control_voltage;
}

float uz_buck_output_voltage_control(uz_buck_control_t *self, struct buck_control_ref_val reference_values, struct buck_control_act_val actual_values)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    // Why is this the case here? Always required?
    // reference_values.ref_output_voltage_Volt += actual_values.output_voltage_Volt;

    reference_values.ref_output_voltage_Volt = uz_signals_saturation(reference_values.ref_output_voltage_Volt, self->config.output_voltage_controller_max_reference, self->config.output_voltage_controller_min_reference);
    reference_values.ref_output_current_Ampere = uz_PI_Controller_sample(self->output_voltage_controller, reference_values.ref_output_voltage_Volt, actual_values.output_voltage_Volt, false);
    return (reference_values.ref_output_current_Ampere);
}

float uz_buck_output_current_control(uz_buck_control_t *self, struct buck_control_ref_val reference_values, struct buck_control_act_val actual_values)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(actual_values.input_voltage_Volt > 0.0f);
    reference_values.ref_output_current_Ampere=uz_signals_saturation(reference_values.ref_output_current_Ampere,self->config.output_current_controller_max_reference,self->config.output_current_controller_min_reference);
    float control_voltage = uz_PI_Controller_sample(self->output_current_controller, reference_values.ref_output_current_Ampere, actual_values.output_current_Ampere, false);
    // control_voltage += actual_values.output_voltage_Volt; // Open loop control for improved controller performance
    // control_voltage = uz_signals_saturation(control_voltage, actual_values.input_voltage_Volt, 0.0f);

    self->duty_cycle = control_voltage / actual_values.input_voltage_Volt;
    self->duty_cycle=uz_signals_saturation(self->duty_cycle, 1.0f, 0.0f);
    uz_assert(!isnan(self->duty_cycle));
    uz_assert(self->duty_cycle >= 0.0f);
    uz_assert(self->duty_cycle <= 1.0f);
    return (self->duty_cycle);
}

void uz_buck_control_reset(uz_buck_control_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->duty_cycle=0.0f;
    uz_PI_Controller_reset(self->output_current_controller);
    uz_PI_Controller_reset(self->input_current_controller);
    uz_PI_Controller_reset(self->output_voltage_controller);
}

/*
Ablaufplan:

3 Fälle: i_HS_control, u_UC_control und i_UC_control
-> soll im Betrieb zwischen den Modi umgeschalten werden können?

1. i_HS_ref - i_HS_act
2. PI regler auf i_HS Fehler
3. Ausgabe des Reglers u_UC_ref
4. Addiere u_UC_act auf u_UC_ref
4. Wenn U_UC_control = true, dann u_UC_ref_extern = u_UC_ref
5. Begrenzung von u_UC_ref auf max. zulässige Spannung
6. u_UC_ref - u_UC_act
7. PI regler auf u_UC Fehler, Ausgabe des Reglers i_UC_ref
8. Wenn i_UC_control = true, dann i_UC_ref_extern = i_UC_ref
9. i_UC_ref - i_UC_act
10. PI regler auf i_UC Fehler, Ausgabe des Reglers Duty_cycle
11. Begrenzung des Duty_cycle auf max. zulässiges Tastverhältnis [0 1]
*/

#endif
