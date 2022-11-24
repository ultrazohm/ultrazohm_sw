#include "../../uz/uz_global_configuration.h"
#if UZ_PREDICTION_AND_COST_FUNCTION_8_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_prediction_and_cost_function_8.h"
#include "uz_prediction_and_cost_function_8_hw.h"

struct uz_prediction_and_cost_function_8_t {
    bool is_ready;
    struct uz_prediction_and_cost_function_8_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_prediction_and_cost_function_8_t instances[UZ_PREDICTION_AND_COST_FUNCTION_8_MAX_INSTANCES] = { 0 };

static uz_prediction_and_cost_function_8_t* uz_prediction_and_cost_function_8_allocation(void);

static uz_prediction_and_cost_function_8_t* uz_prediction_and_cost_function_8_allocation(void){
    uz_assert(instance_counter < UZ_PREDICTION_AND_COST_FUNCTION_8_MAX_INSTANCES);
    uz_prediction_and_cost_function_8_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_prediction_and_cost_function_8_t* uz_prediction_and_cost_function_8_init(struct uz_prediction_and_cost_function_8_config_t config){
    uz_prediction_and_cost_function_8_t* self = uz_prediction_and_cost_function_8_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    self->config = config;

    uz_prediction_and_cost_function_8_hw_set_Lq(self->config.base_address, self->config.Lq);
    uz_prediction_and_cost_function_8_hw_set_Ld(self->config.base_address, self->config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ld(self->config.base_address, self->config.SampleTime, self->config.Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lq(self->config.base_address, self->config.SampleTime, self->config.Lq);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lx(self->config.base_address, self->config.SampleTime, self->config.Lx);
    uz_prediction_and_cost_function_8_hw_set_pole_pairs(self->config.base_address, self->config.pole_pairs);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ly(self->config.base_address, self->config.SampleTime, self->config.Ly);
    uz_prediction_and_cost_function_8_hw_set_Rs(self->config.base_address, self->config.Rs);
    uz_prediction_and_cost_function_8_hw_set_psiPM(self->config.base_address, self->config.psiPM);
    uz_prediction_and_cost_function_8_hw_set_id_ref(self->config.base_address, self->config.id_ref);
    uz_prediction_and_cost_function_8_hw_set_iq_ref(self->config.base_address, self->config.iq_ref);
    uz_prediction_and_cost_function_8_hw_set_ix_ref(self->config.base_address, self->config.ix_ref);
    uz_prediction_and_cost_function_8_hw_set_iy_ref(self->config.base_address, self->config.iy_ref);
    return (self);
}

void uz_prediction_and_cost_function_8_idref_iqref_ixref_iyref_update(uz_prediction_and_cost_function_8_t* self, uz_6ph_idref_iqref_ixref_iyref_t updated_values){
 
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    uz_prediction_and_cost_function_8_hw_set_id_ref(self->config.base_address, updated_values.id_ref);
    uz_prediction_and_cost_function_8_hw_set_iq_ref(self->config.base_address, updated_values.iq_ref);
    uz_prediction_and_cost_function_8_hw_set_ix_ref(self->config.base_address, updated_values.ix_ref);
    uz_prediction_and_cost_function_8_hw_set_iy_ref(self->config.base_address, updated_values.iy_ref);
}

int32_t uz_prediction_and_cost_function_8_read_Index(uz_prediction_and_cost_function_8_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    int32_t Index = 0;
    Index = uz_prediction_and_cost_function_8_hw_get_Index(self->config.base_address);

    return Index;
}
/*
void uz_prediction_and_cost_function_8_set_done_phase_voltages_AXI(uz_prediction_and_cost_function_8_t* self, _Bool done_phase_voltages_AXI){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    uz_prediction_and_cost_function_8_hw_set_done_phase_voltages(self->config.base_address, done_phase_voltages_AXI);
}

void uz_prediction_and_cost_function_8_set_done_vsd_and_park_AXI(uz_prediction_and_cost_function_8_t* self, _Bool done_vsd_and_park_AXI){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    uz_prediction_and_cost_function_8_hw_set_done_vsd_and_park(self->config.base_address, done_vsd_and_park_AXI);
}

void uz_prediction_and_cost_function_8_set_current_valid_in_AXI(uz_prediction_and_cost_function_8_t* self, _Bool current_valid_in_AXI){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    uz_prediction_and_cost_function_8_hw_set_current_valid_in(self->config.base_address, current_valid_in_AXI);
}
*/
_Bool uz_prediction_and_cost_function_8_read_done_prediction_and_cost_function(uz_prediction_and_cost_function_8_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    _Bool done_prediction_and_cost_function = 0;
    done_prediction_and_cost_function = uz_prediction_and_cost_function_8_hw_get_done_prediction_and_cost_function(self->config.base_address);

    return done_prediction_and_cost_function;
}

#endif