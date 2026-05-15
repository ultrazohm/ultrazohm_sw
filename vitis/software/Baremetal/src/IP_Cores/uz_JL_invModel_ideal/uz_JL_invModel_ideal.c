
#include "../../uz/uz_global_configuration.h"
#if UZ_JL_INVMODEL_IDEAL_MAX_INSTANCES > 0U
#include "uz_JL_invModel_ideal.h"
#include "uz_JL_invModel_ideal_hw.h"
#include <stdbool.h> 
#include "../../uz/uz_HAL.h"
 
 struct uz_JL_invModel_ideal_t {
    bool is_ready;
    struct uz_JL_invModel_ideal_config_t config;
};
 
 static uint32_t instance_counter = 0U;
 static uz_JL_invModel_ideal_t instances[UZ_JL_INVMODEL_IDEAL_MAX_INSTANCES] = { 0 };
 
 static uz_JL_invModel_ideal_t* uz_JL_invModel_ideal_allocation(void);
 
 static uz_JL_invModel_ideal_t* uz_JL_invModel_ideal_allocation(void){
    uz_assert(instance_counter < UZ_JL_INVMODEL_IDEAL_MAX_INSTANCES);
    uz_JL_invModel_ideal_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
 }
 
 uz_JL_invModel_ideal_t* uz_JL_invModel_ideal_init(struct uz_JL_invModel_ideal_config_t config) 
 {
    uz_assert_not_zero(config.ip_core_frequency_Hz);
    uz_assert_not_zero(config.base_adress);
    uz_assert(config.Udc>0.0f);
    uz_JL_invModel_ideal_t* self = uz_JL_invModel_ideal_allocation();
    self->config = config;
    uz_JL_invModel_ideal_set_Udc(self, config.Udc);
    return (self);
 }

 void uz_JL_invModel_ideal_set_Udc(uz_JL_invModel_ideal_t *self, float Udc)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_invModel_ideal_hw_write_Udc(self->config.base_adress, Udc);
}

struct uz_JL_invModel_ideal_output_t uz_JL_invModel_ideal_get_outputs(uz_JL_invModel_ideal_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    struct uz_JL_invModel_ideal_output_t outputs = {
        .Ua = 0.0f,
        .Ub = 0.0f,
        .Uc = 0.0f};
    outputs.Ua = uz_JL_invModel_ideal_hw_read_out_Ua(self->config.base_adress);
    outputs.Ub = uz_JL_invModel_ideal_hw_read_out_Ub(self->config.base_adress);
    outputs.Uc = uz_JL_invModel_ideal_hw_read_out_Uc(self->config.base_adress);
    return outputs;
}

void uz_JL_invModel_ideal_trigger_output_strobe(uz_JL_invModel_ideal_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_invModel_ideal_hw_trigger_output_strobe(self->config.base_adress);
}
 #endif
