#include "uz_PWM_duty_freq_detection.h"
#include "../../uz/uz_global_configuration.h"
#if UZ_PWM_DUTY_FREQ_DETECTION_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_PWM_duty_freq_detection_hw.h"


struct uz_PWM_duty_freq_detection_t {
    bool is_ready;
    struct uz_PWM_duty_freq_detection_config_t config;
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

uz_PWM_duty_freq_detection_t* uz_PWM_duty_freq_detection_init(struct uz_PWM_duty_freq_detection_config_t config) {
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz); 
    uz_PWM_duty_freq_detection_t* self = uz_PWM_duty_freq_detection_allocation();
    self->config=config;
    return(self);
}

float uz_PWM_duty_freq_detection_get_frequency_in_Hz(uz_PWM_duty_freq_detection_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_PWM_duty_freq_detection_hw_trigger_output_strobe(self->config.base_address); 
    float PWM_period_ticks = (float)uz_PWM_duty_freq_detection_hw_get_PWM_period_ticks(self->config.base_address);
    return((float)self->config.ip_clk_frequency_Hz / PWM_period_ticks);
}

float uz_PWM_duty_freq_detection_get_duty_cycle_in_percent(uz_PWM_duty_freq_detection_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_PWM_duty_freq_detection_hw_trigger_output_strobe(self->config.base_address);
    uint32_t PWM_period_ticks = uz_PWM_duty_freq_detection_hw_get_PWM_period_ticks(self->config.base_address);
    uint32_t PWM_high_ticks = uz_PWM_duty_freq_detection_hw_get_PWM_hightime_ticks(self->config.base_address);
    return((float)PWM_high_ticks / (float)PWM_period_ticks);
}

float uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(float Duty_cycle_in_percent, struct linear_interpolation_parameters_t lin_interp_param) {
    uz_assert(Duty_cycle_in_percent >= 0.0f);
    uz_assert(Duty_cycle_in_percent <= 1.0f);
    return(Duty_cycle_in_percent * lin_interp_param.a + lin_interp_param.b);
}



#endif
