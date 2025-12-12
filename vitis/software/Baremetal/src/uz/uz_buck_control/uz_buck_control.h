#ifndef UZ_BUCK_CONTROL_H
#define UZ_BUCK_CONTROL_H

#include <stdbool.h>
#include "../uz_piController/uz_piController.h"

typedef struct uz_buck_control_t uz_buck_control_t;

struct buck_control_act_val
{
    float input_current_Ampere;
    float output_voltage_Volt;
    float input_voltage_Volt;
    float output_current_Ampere;
};

struct buck_control_ref_val
{
    float ref_input_current_Ampere;
    float ref_output_voltage_Volt;
    float ref_output_current_Ampere;
};

enum uz_buck_control_mode
{
    uz_buck_input_current_mode,
    uz_buck_output_voltage_mode,
    uz_buck_output_current_mode,
};

struct buck_control_config
{
    float max_duty_cycle;
    float min_duty_cycle;
    float rated_input_voltage_Volt;
    float input_current_max_reference;
    float input_current_min_reference;
    enum uz_buck_control_mode control_mode;
    float input_current_controller_max_reference;
    float input_current_controller_min_reference;
    float input_current_controller_max_control_signal;
    float input_current_controller_min_control_signal;
    float input_current_controller_kp;
    float input_current_controller_ki;
    float output_voltage_controller_max_control_signal;
    float output_voltage_controller_min_control_signal;
    float output_voltage_controller_max_reference;
    float output_voltage_controller_min_reference;
    float output_voltage_controller_kp;
    float output_voltage_controller_ki;
    float output_current_controller_max_control_signal;
    float output_current_controller_min_control_signal;
    float output_current_controller_max_reference;
    float output_current_controller_min_reference;
    float output_current_controller_kp;
    float output_current_controller_ki;
    float sampling_frequency_Hz;
};

uz_buck_control_t *uz_buck_control_init(struct buck_control_config external_config);

float uz_buck_control_sample(uz_buck_control_t *self, struct buck_control_ref_val ref_val, struct buck_control_act_val act_val);
// Write reset function

float uz_buck_input_current_control(uz_buck_control_t *self, float input_current_reference, float input_current_actual);
float uz_buck_output_voltage_control(uz_buck_control_t *self, struct buck_control_ref_val reference_values, struct buck_control_act_val actual_values);
float uz_buck_output_current_control(uz_buck_control_t *self, struct buck_control_ref_val reference_values, struct buck_control_act_val actual_values);

#endif // UZ_BUCK_CONTROL_H