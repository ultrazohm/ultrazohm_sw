#include "uz_PWM_SS_2L.h"

#include "../../uz/uz_global_configuration.h"
#if UZ_PWM_SS_2L_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz/uz_HAL.h"
#include "uz_PWM_SS_2L.h" 
#include "uz_PWM_SS_2L_hw.h" 

struct uz_PWM_SS_2L_t {
    bool is_ready;
    struct uz_PWM_SS_2L_config_t config;
};

static size_t instance_counter = 0U;
static uz_PWM_SS_2L_t instances[UZ_PWM_SS_2L_MAX_INSTANCES] = { 0 };

static uz_PWM_SS_2L_t* uz_PWM_SS_2L_allocation(void);

static uz_PWM_SS_2L_t* uz_PWM_SS_2L_allocation(void){
    uz_assert(instance_counter < UZ_PWM_SS_2L_MAX_INSTANCES);
    uz_PWM_SS_2L_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_PWM_SS_2L_t* uz_PWM_SS_2L_init(struct uz_PWM_SS_2L_config_t config) {
    uz_assert(0U != config.base_address);
    uz_assert(0U != config.ip_clk_frequency_Hz);     
    uz_PWM_SS_2L_t* self = uz_PWM_SS_2L_allocation();
    self->config=config;
    return (self);
}

void uz_PWM_SS_2L_set_config(struct uz_PWM_SS_2L_t *instance) {
    uz_assert_not_zero(instance->config.base_address);
    uz_assert_not_zero(instance->config.ip_clk_frequency_Hz);
    uz_assert_not_zero(instance->is_ready);
    
    uz_PWM_SS_2L_hw_SetStatus(instance->config.base_address, instance->config.PWM_en);

    uz_PWM_SS_2L_hw_SetMode(instance->config.base_address, instance->config.PWM_mode);

    uz_PWM_SS_2L_hw_SetCarrierFrequency(instance->config.base_address, instance->config.ip_clk_frequency_Hz, instance->config.PWM_freq_Hz);
    
    uz_PWM_SS_2L_hw_SetMinimumPulseWidth(instance->config.base_address, instance->config.min_pulse_width);

    uz_PWM_SS_2L_hw_SetDutyCycle(instance->config.base_address, instance->config.init_dutyCyc_A, instance->config.init_dutyCyc_B, instance->config.init_dutyCyc_C);

    uz_PWM_SS_2L_hw_SetTristate(instance->config.base_address, 1, instance->config.Tristate_HB1);
    uz_PWM_SS_2L_hw_SetTristate(instance->config.base_address, 2, instance->config.Tristate_HB2);
    uz_PWM_SS_2L_hw_SetTristate(instance->config.base_address, 3, instance->config.Tristate_HB3);
}

void uz_PWM_SS_2L_set_duty_cycle(struct uz_PWM_SS_2L_t *instance, float dutyCyc_A, float dutyCyc_B, float dutyCyc_C) {
    uz_assert_not_zero(instance->config.base_address);
    uz_assert_not_zero(instance->is_ready);

    uz_PWM_SS_2L_hw_SetDutyCycle(instance->config.base_address, dutyCyc_A, dutyCyc_B, dutyCyc_C);
}
#endif
