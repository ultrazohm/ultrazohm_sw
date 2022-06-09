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

static uint32_t instance_counter = 0U;
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
    uz_assert_not_zero(self->is_ready);
    uz_PWM_SS_2L_hw_SetStatus(self->config.base_address, self->config.PWM_en);

    uz_PWM_SS_2L_hw_SetMode(self->config.base_address, self->config.PWM_mode);

    uz_PWM_SS_2L_hw_SetExternalCounterSource(self->config.base_address, self->config.use_external_counter);

    uz_PWM_SS_2L_hw_SetCarrierFrequency(self->config.base_address, self->config.ip_clk_frequency_Hz, self->config.PWM_freq_Hz);
    
    uz_PWM_SS_2L_hw_SetMinimumPulseWidth(self->config.base_address, self->config.min_pulse_width);

    uz_PWM_SS_2L_hw_SetDutyCycle(self->config.base_address, self->config.init_dutyCyc_A, self->config.init_dutyCyc_B, self->config.init_dutyCyc_C);

    uz_PWM_SS_2L_hw_SetTristate(self->config.base_address, 1U, self->config.Tristate_HB1);
    uz_PWM_SS_2L_hw_SetTristate(self->config.base_address, 2U, self->config.Tristate_HB2);
    uz_PWM_SS_2L_hw_SetTristate(self->config.base_address, 3U, self->config.Tristate_HB3);

    uz_PWM_SS_2L_hw_SetTriangleShift(self->config.base_address, self->config.triangle_shift_HB1, self->config.triangle_shift_HB2, self->config.triangle_shift_HB3);

    return (self);
}

void uz_PWM_SS_2L_set_duty_cycle(struct uz_PWM_SS_2L_t *self, float dutyCyc_A, float dutyCyc_B, float dutyCyc_C) {
    uz_assert_not_NULL(self);
    uz_assert_not_zero_uint32(self->config.base_address);
    uz_assert_not_zero(self->is_ready);
    uz_PWM_SS_2L_hw_SetDutyCycle(self->config.base_address, dutyCyc_A, dutyCyc_B, dutyCyc_C);
}

void uz_PWM_SS_2L_set_tristate(struct uz_PWM_SS_2L_t *self, bool Tristate_HB1, bool Tristate_HB2, bool Tristate_HB3) {
    uz_assert_not_NULL(self);
    uz_assert_not_zero_uint32(self->config.base_address);
    uz_assert_not_zero(self->is_ready);
    self->config.Tristate_HB1 = Tristate_HB1;
    self->config.Tristate_HB2 = Tristate_HB2;
    self->config.Tristate_HB3 = Tristate_HB3;
    uz_PWM_SS_2L_hw_SetTristate(self->config.base_address, 1U, Tristate_HB1);
    uz_PWM_SS_2L_hw_SetTristate(self->config.base_address, 2U, Tristate_HB2);    
    uz_PWM_SS_2L_hw_SetTristate(self->config.base_address, 3U, Tristate_HB3);
}

void uz_PWM_SS_2L_set_PWM_mode(struct uz_PWM_SS_2L_t *self, enum uz_PWM_SS_2L_PWM_mode PWM_mode) {
    uz_assert_not_NULL(self);
    uz_assert_not_zero_uint32(self->config.base_address);
    uz_assert_not_zero(self->is_ready);
    self->config.PWM_mode = PWM_mode;
    uz_PWM_SS_2L_hw_SetMode(self->config.base_address, PWM_mode);    
}

void uz_PWM_SS_2L_set_triangle_shift(struct uz_PWM_SS_2L_t *self, float triangle_shift_HB1, float triangle_shift_HB2, float triangle_shift_HB3) {
    uz_assert_not_NULL(self);
    uz_assert_not_zero_uint32(self->config.base_address);
    uz_assert_not_zero(self->is_ready);
    self->config.triangle_shift_HB1 = triangle_shift_HB1;
    self->config.triangle_shift_HB2 = triangle_shift_HB2;
    self->config.triangle_shift_HB3 = triangle_shift_HB3;
    uz_PWM_SS_2L_hw_SetTriangleShift(self->config.base_address, triangle_shift_HB1, triangle_shift_HB2, triangle_shift_HB3);    
}
#endif
