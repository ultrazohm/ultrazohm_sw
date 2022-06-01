#include "../../uz/uz_global_configuration.h"
#if UZ_INVERTER_ADAPTER_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_inverter_adapter.h"
#include "uz_inverter_adapter_hw.h"

struct uz_inverter_adapter_t {
    bool is_ready;
    struct uz_inverter_adapter_config_t config;
    struct uz_inverter_adapter_outputs_t outputs;
};

static size_t instance_counter = 0U;
static uz_inverter_adapter_t instances[UZ_INVERTER_ADAPTER_MAX_INSTANCES] = { 0 };

static uz_inverter_adapter_t* uz_inverter_adapter_allocation(void);

static uz_inverter_adapter_t* uz_inverter_adapter_allocation(void){
    uz_assert(instance_counter < UZ_INVERTER_ADAPTER_MAX_INSTANCES);
    uz_inverter_adapter_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_inverter_adapter_t* uz_inverter_adapter_init(struct uz_inverter_adapter_config_t config, struct uz_inverter_adapter_outputs_t outputs) {
    uz_assert(0U != config.base_address);
    uz_assert(0U != config.ip_clk_frequency_Hz); 
    uz_inverter_adapter_t* self = uz_inverter_adapter_allocation();
    self->config=config;
    self->outputs=outputs;
    return(self);
}

float uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(uz_inverter_adapter_t *self, float dutyCycleNormalized) {
    // linear interpolation of duty cycle to temperature function
    float a;
    float b;
    a = self->config.linear_interpolation_params.a;
    b = self->config.linear_interpolation_params.b;
    return(dutyCycleNormalized*a+b);
}

void uz_inverter_adapter_update_states(uz_inverter_adapter_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    //get OC status bit of each switch via bit mask and bit shift
    self->outputs.OC = uz_inverter_adapter_get_OC(self->config.base_address);
    self->outputs.OC_H1 = (((self->outputs.OC) & 0x01) >> 0);
    self->outputs.OC_L1 = (((self->outputs.OC) & 0x02) >> 1);
    self->outputs.OC_H2 = (((self->outputs.OC) & 0x04) >> 2);
    self->outputs.OC_L2 = (((self->outputs.OC) & 0x08) >> 3);
    self->outputs.OC_H3 = (((self->outputs.OC) & 0x10) >> 4);
    self->outputs.OC_L3 = (((self->outputs.OC) & 0x20) >> 5);

    //get FAULT status bit of each switch via bit mask and bit shift
    self->outputs.FAULT = uz_inverter_adapter_get_FAULT(self->config.base_address);
    self->outputs.FAULT_H1 = (((self->outputs.FAULT) & 0x01) >> 0);
    self->outputs.FAULT_L1 = (((self->outputs.FAULT) & 0x02) >> 1);
    self->outputs.FAULT_H2 = (((self->outputs.FAULT) & 0x04) >> 2);
    self->outputs.FAULT_L2 = (((self->outputs.FAULT) & 0x08) >> 3);
    self->outputs.FAULT_H3 = (((self->outputs.FAULT) & 0x10) >> 4);
    self->outputs.FAULT_L3 = (((self->outputs.FAULT) & 0x20) >> 5);

    //get I_DIAG status bit of each current amplifier via bit mask and bit shift
    self->outputs.I_DIAG = uz_inverter_adapter_get_I_DIAG(self->config.base_address);
    self->outputs.I_DC_DIAG = (((self->outputs.I_DIAG) & 0x01) >> 0);
    self->outputs.I1_DIAG = (((self->outputs.I_DIAG) & 0x02) >> 1);
    self->outputs.I2_DIAG = (((self->outputs.I_DIAG) & 0x04) >> 2);
    self->outputs.I3_DIAG = (((self->outputs.I_DIAG) & 0x08) >> 3);    

    //get duty cycle information of each switch containing the chip temperature information
    self->outputs.PWMdutyCycNormalized_H1 = uz_inverter_adapter_get_PWMdutyCycNormalized_H1(self->config.base_address);
    self->outputs.PWMdutyCycNormalized_L1 = uz_inverter_adapter_get_PWMdutyCycNormalized_L1(self->config.base_address);
    self->outputs.PWMdutyCycNormalized_H2 = uz_inverter_adapter_get_PWMdutyCycNormalized_H2(self->config.base_address);
    self->outputs.PWMdutyCycNormalized_L2 = uz_inverter_adapter_get_PWMdutyCycNormalized_L2(self->config.base_address);
    self->outputs.PWMdutyCycNormalized_H3 = uz_inverter_adapter_get_PWMdutyCycNormalized_H3(self->config.base_address);
    self->outputs.PWMdutyCycNormalized_L3 = uz_inverter_adapter_get_PWMdutyCycNormalized_L3(self->config.base_address);

    //calculate chip temperatures in degrees celsius from the duty cycle information
    self->outputs.ChipTempDegreesCelsius_H1 = uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(self, self->outputs.PWMdutyCycNormalized_H1);
    self->outputs.ChipTempDegreesCelsius_L1 = uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(self, self->outputs.PWMdutyCycNormalized_L1);
    self->outputs.ChipTempDegreesCelsius_H2 = uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(self, self->outputs.PWMdutyCycNormalized_H2);
    self->outputs.ChipTempDegreesCelsius_L2 = uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(self, self->outputs.PWMdutyCycNormalized_L2);
    self->outputs.ChipTempDegreesCelsius_H3 = uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(self, self->outputs.PWMdutyCycNormalized_H3);
    self->outputs.ChipTempDegreesCelsius_L3 = uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(self, self->outputs.PWMdutyCycNormalized_L3);
}

struct uz_inverter_adapter_outputs_t uz_inverter_adapter_get_outputs(uz_inverter_adapter_t *self) {

    return(self->outputs);
}

#endif