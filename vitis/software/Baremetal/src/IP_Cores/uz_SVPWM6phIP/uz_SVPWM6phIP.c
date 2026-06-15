


#include "../../uz/uz_global_configuration.h"
#if UZ_SVPWM6phIP_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz/uz_HAL.h"
#include "uz_SVPWM6phIP.h"
#include "uz_SVPWM6phIP_hw.h"

struct uz_SVPWM6phIP_t {
    bool is_ready;
    struct uz_SVPWM6phIP_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_SVPWM6phIP_t instances[UZ_SVPWM6phIP_MAX_INSTANCES] = { 0 };

static uz_SVPWM6phIP_t* uz_SVPWM6pIP_allocation(void);

static uz_SVPWM6phIP_t* uz_SVPWM6pIP_allocation(void){
    uz_assert(instance_counter < UZ_SVPWM6phIP_MAX_INSTANCES);
    uz_SVPWM6phIP_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_SVPWM6phIP_t* uz_SVPWM6phIP_init(struct uz_SVPWM6phIP_config_t config) {
    uz_assert(0U != config.base_address);
    uz_assert(0U != config.ip_clk_frequency_Hz);     
    uz_SVPWM6phIP_t* self = uz_SVPWM6pIP_allocation();
    self->config=config;
    uz_assert_not_zero(self->is_ready);
    uz_SVPWM6phIP_hw_SetStatus(self->config.base_address, self->config.PWM_en);

    uz_SVPWM6phIP_hw_SetMode(self->config.base_address, self->config.PWM_mode);

    uz_SVPWM6phIP_hw_SetExternalCounterSource(self->config.base_address, self->config.use_external_counter);

    uz_SVPWM6phIP_hw_SetCarrierFrequency(self->config.base_address, self->config.ip_clk_frequency_Hz, self->config.PWM_freq_Hz);
    
    uz_SVPWM6phIP_hw_SetMinimumTon(self->config.base_address, self->config.min_Ton_time);

    uz_SVPWM6phIP_hw_Set_T_and_SV(self->config.base_address, self->config.init_T1, self->config.init_T2, self->config.init_T3, self->config.init_T4, self->config.init_T5, self->config.init_SV1, self->config.init_SV2, self->config.init_SV3, self->config.init_SV4, self->config.init_SV5);

    uz_SVPWM6phIP_hw_SetTristate(self->config.base_address, 1U, self->config.Tristate_HB1);
    uz_SVPWM6phIP_hw_SetTristate(self->config.base_address, 2U, self->config.Tristate_HB2);
    uz_SVPWM6phIP_hw_SetTristate(self->config.base_address, 3U, self->config.Tristate_HB3);
    uz_SVPWM6phIP_hw_SetTristate(self->config.base_address, 4U, self->config.Tristate_HB4);
    uz_SVPWM6phIP_hw_SetTristate(self->config.base_address, 5U, self->config.Tristate_HB5);
    uz_SVPWM6phIP_hw_SetTristate(self->config.base_address, 6U, self->config.Tristate_HB6);

    uz_SVPWM6phIP_hw_SetTriggerSource(self->config.base_address, self->config.trigger_source);

    return (self);
}

void uz_SVPWM6phIP_set_T_and_SV(struct uz_SVPWM6phIP_t *self, float T1, float T2, float T3, float T4, float T5, uint32_t SV1, uint32_t SV2, uint32_t SV3, uint32_t SV4, uint32_t SV5){
    uz_assert_not_NULL(self);
    uz_assert_not_zero_uint32(self->config.base_address);
    uz_assert_not_zero(self->is_ready);
    uz_SVPWM6phIP_hw_Set_T_and_SV(self->config.base_address, T1, T2, T3, T4, T5, SV1, SV2, SV3, SV4, SV5);
}

void uz_SVPWM6phIP_set_tristate(struct uz_SVPWM6phIP_t *self, bool Tristate_HB1, bool Tristate_HB2, bool Tristate_HB3, bool Tristate_HB4, bool Tristate_HB5, bool Tristate_HB6) {
    uz_assert_not_NULL(self);
    uz_assert_not_zero_uint32(self->config.base_address);
    uz_assert_not_zero(self->is_ready);
    self->config.Tristate_HB1 = Tristate_HB1;
    self->config.Tristate_HB2 = Tristate_HB2;
    self->config.Tristate_HB3 = Tristate_HB3;
    self->config.Tristate_HB4 = Tristate_HB4;
    self->config.Tristate_HB5 = Tristate_HB5;
    self->config.Tristate_HB6 = Tristate_HB6;
    uz_SVPWM6phIP_hw_SetTristate(self->config.base_address, 1U, Tristate_HB1);
    uz_SVPWM6phIP_hw_SetTristate(self->config.base_address, 2U, Tristate_HB2);    
    uz_SVPWM6phIP_hw_SetTristate(self->config.base_address, 3U, Tristate_HB3);
    uz_SVPWM6phIP_hw_SetTristate(self->config.base_address, 4U, Tristate_HB4);
    uz_SVPWM6phIP_hw_SetTristate(self->config.base_address, 5U, Tristate_HB5);
    uz_SVPWM6phIP_hw_SetTristate(self->config.base_address, 6U, Tristate_HB6);
}

void uz_SVPWM6phIP_set_PWM_mode(struct uz_SVPWM6phIP_t *self, enum uz_SVPWM6phIP_PWM_mode PWM_mode) {
    uz_assert_not_NULL(self);
    uz_assert_not_zero_uint32(self->config.base_address);
    uz_assert_not_zero(self->is_ready);
    self->config.PWM_mode = PWM_mode;
    uz_SVPWM6phIP_hw_SetMode(self->config.base_address, PWM_mode);    
}


#endif
