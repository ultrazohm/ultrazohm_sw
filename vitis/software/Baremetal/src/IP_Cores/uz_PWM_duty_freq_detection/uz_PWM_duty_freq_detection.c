#include "uz_PWM_duty_freq_detection.h"
#include "../../uz/uz_global_configuration.h"
#if UZ_PWM_DUTY_FREQ_DETECTION_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_PWM_duty_freq_detection.h"
#include "uz_PWM_duty_freq_detection_hw.h"


struct uz_PWM_duty_freq_detection_t {
    bool is_ready;
    struct uz_PWM_duty_freq_detection_config_t config;
    struct uz_PWM_duty_freq_detection_outputs_t outputs;
};

static size_t instance_counter = 0U;
static uz_PWM_duty_freq_detection_t instances[UZ_PWM_DUTY_FREQ_DETECTION_MAX_INSTANCES] = { 0 };

static uz_PWM_duty_freq_detection_t* uz_PWM_duty_freq_detection_allocation(void);

static uz_PWM_duty_freq_detection_t* uz_PWM_duty_freq_detection_allocation(void){
    uz_assert(instance_counter < UZ_PWM_DUTY_FREQ_DETECTION_MAX_INSTANCES);
    uz_PWM_duty_freq_detection_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_PWM_duty_freq_detection_t* uz_PWM_duty_freq_detection_init(struct uz_PWM_duty_freq_detection_config_t config, struct uz_PWM_duty_freq_detection_outputs_t outputs) {
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz); 
    uz_PWM_duty_freq_detection_t* self = uz_PWM_duty_freq_detection_allocation();
    self->config=config;
    self->outputs=outputs;
    return(self);
}




float uz_PWM_duty_freq_detection_PWMdutyCycNormalized_to_DegreesCelsius(uz_PWM_duty_freq_detection_t *self, float dutyCycleNormalized) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // local variables for readability in the return statement below
    float a;
    float b;
    a = self->config.linear_interpolation_parameters_t.a;
    b = self->config.linear_interpolation_parameters_t.b;
    // linear interpolation of duty cycle to temperature function
    return(dutyCycleNormalized*a+b);
}


void uz_PWM_duty_freq_detection_update_states(uz_PWM_duty_freq_detection_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    self->outputs.PWMdutyCycNormalized = uz_PWM_duty_freq_detection_hw_get_PWMdutyCycNormalized(self->config.base_address);
    self->outputs.PWMFreq = uz_PWM_duty_freq_detection_hw_get_PWMFreqTicks(self->config.base_address);
    self->outputs.PWMhightime = uz_PWM_duty_freq_detection_hw_get_PWMhightimeTicks(self->config.base_address);
    self->outputs.PWMlowtime = uz_PWM_duty_freq_detection_hw_get_PWMlowtimeTicks(self->config.base_address);

    self->outputs.TempDegreesCelsius = uz_PWM_duty_freq_detection_PWMdutyCycNormalized_to_DegreesCelsius(self, self->outputs.PWMdutyCycNormalized);

}

struct uz_PWM_duty_freq_detection_outputs_t uz_PWM_duty_freq_detection_get_outputs(uz_PWM_duty_freq_detection_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_PWM_duty_freq_detection_update_states(self);
    return(self->outputs);
}


#endif