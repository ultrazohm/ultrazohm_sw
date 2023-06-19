#include "../../uz/uz_global_configuration.h"
#if UZ_INVERTER_ADAPTER_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_inverter_adapter.h"
#include "uz_inverter_adapter_hw.h"

struct uz_inverter_adapter_t {
    bool is_ready;
    uint32_t temp_select_counter;
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
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz); 
    uz_inverter_adapter_t* self = uz_inverter_adapter_allocation();
    self->config=config;
    self->outputs=outputs;
    return(self);
}

float uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(uz_inverter_adapter_t *self, float dutyCycleNormalized) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // local variables for readability in the return statement below
    float a;
    float b;
    a = self->config.linear_interpolation_params.a;
    b = self->config.linear_interpolation_params.b;
    // linear interpolation of duty cycle to temperature function
    return(dutyCycleNormalized*a+b);
}

void uz_inverter_adapter_update_states(uz_inverter_adapter_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    //get OC status bit of each switch via bit mask and bit shift
    self->outputs.OC = uz_inverter_adapter_hw_get_OC(self->config.base_address);
    self->outputs.OC_H1 = extract_state_from_bitpattern(self->outputs.OC, 0U);
    self->outputs.OC_L1 = extract_state_from_bitpattern(self->outputs.OC, 1U);
    self->outputs.OC_H2 = extract_state_from_bitpattern(self->outputs.OC, 2U);
    self->outputs.OC_L2 = extract_state_from_bitpattern(self->outputs.OC, 3U);
    self->outputs.OC_H3 = extract_state_from_bitpattern(self->outputs.OC, 4U);
    self->outputs.OC_L3 = extract_state_from_bitpattern(self->outputs.OC, 5U);

    //get FAULT status bit of each switch via bit mask and bit shift
    self->outputs.FAULT = uz_inverter_adapter_hw_get_FAULT(self->config.base_address);
    self->outputs.FAULT_H1 = extract_state_from_bitpattern(self->outputs.FAULT, 0U);
    self->outputs.FAULT_L1 = extract_state_from_bitpattern(self->outputs.FAULT, 1U);
    self->outputs.FAULT_H2 = extract_state_from_bitpattern(self->outputs.FAULT, 2U);
    self->outputs.FAULT_L2 = extract_state_from_bitpattern(self->outputs.FAULT, 3U);
    self->outputs.FAULT_H3 = extract_state_from_bitpattern(self->outputs.FAULT, 4U);
    self->outputs.FAULT_L3 = extract_state_from_bitpattern(self->outputs.FAULT, 5U);

    //get I_DIAG status bit of each current amplifier via bit mask and bit shift
    self->outputs.I_DIAG = uz_inverter_adapter_hw_get_I_DIAG(self->config.base_address);
    self->outputs.I_DC_DIAG = extract_state_from_bitpattern(self->outputs.I_DIAG, 0U);
    self->outputs.I1_DIAG = extract_state_from_bitpattern(self->outputs.I_DIAG, 1U);
    self->outputs.I2_DIAG = extract_state_from_bitpattern(self->outputs.I_DIAG, 2U);
    self->outputs.I3_DIAG = extract_state_from_bitpattern(self->outputs.I_DIAG, 3U);    

    //calculate chip temperatures in degrees celsius from the duty cycle information
	//get duty cycle information of each switch containing the chip temperature information
    //Only reads out 1 temperature per clock to reduces execution time
	switch(self->temp_select_counter) {
        case (0U):
            self->outputs.PWMdutyCycNormalized_H1 = uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H1(self->config.base_address);
            self->outputs.ChipTempDegreesCelsius_H1 = uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(self, self->outputs.PWMdutyCycNormalized_H1);
            self->temp_select_counter++;
            break;
        
        case (1U):
            self->outputs.PWMdutyCycNormalized_L1 = uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L1(self->config.base_address);
            self->outputs.ChipTempDegreesCelsius_L1 = uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(self, self->outputs.PWMdutyCycNormalized_L1);
            self->temp_select_counter++;
            break;
        
        case (2U):
            self->outputs.PWMdutyCycNormalized_H2 = uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H2(self->config.base_address);
            self->outputs.ChipTempDegreesCelsius_H2 = uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(self, self->outputs.PWMdutyCycNormalized_H2);
            self->temp_select_counter++;
            break;
        
        case (3U):
            self->outputs.PWMdutyCycNormalized_L2 = uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L2(self->config.base_address);
            self->outputs.ChipTempDegreesCelsius_L2 = uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(self, self->outputs.PWMdutyCycNormalized_L2);
            self->temp_select_counter++;
            break;

        case (4U):
            self->outputs.PWMdutyCycNormalized_H3 = uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H3(self->config.base_address);
            self->outputs.ChipTempDegreesCelsius_H3 = uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(self, self->outputs.PWMdutyCycNormalized_H3);
            self->temp_select_counter++;
            break;

        case (5U):
            self->outputs.PWMdutyCycNormalized_L3 = uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L3(self->config.base_address);
            self->outputs.ChipTempDegreesCelsius_L3 = uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(self, self->outputs.PWMdutyCycNormalized_L3);
            self->temp_select_counter = 0U;
            break;

        default:
            break;

    }
}

struct uz_inverter_adapter_outputs_t uz_inverter_adapter_get_outputs(uz_inverter_adapter_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_inverter_adapter_update_states(self);
    return(self->outputs);
}

void uz_inverter_adapter_set_PWM_EN(uz_inverter_adapter_t *self, bool pwm_en_onoff) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_inverter_adapter_hw_set_PWM_EN(self->config.base_address, pwm_en_onoff);
}

bool extract_state_from_bitpattern(uint32_t bitpattern, uint32_t position) {
    bool state=false;
    if((bitpattern & (1<<position)) >> position) {
        state=true;
    }
return state;
}
#endif
