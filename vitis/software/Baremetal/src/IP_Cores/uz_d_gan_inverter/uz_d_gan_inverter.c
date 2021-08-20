#include "../../uz/uz_global_configuration.h"
#if UZ_D_GAN_INVERTER_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz/uz_HAL.h"
#include "uz_d_gan_inverter.h" 
#include "uz_d_gan_inverter_hw.h" 

struct uz_d_gan_inverter_t {
    bool is_ready;
    struct uz_d_gan_inverter_config_t config;
    struct uz_d_gan_inverter_outputs_t outputs;
};

static size_t instance_counter = 0U;
static uz_d_gan_inverter_t instances[UZ_D_GAN_INVERTER_MAX_INSTANCES] = { 0 };

static uz_d_gan_inverter_t* uz_d_gan_inverter_allocation(void);

static uz_d_gan_inverter_t* uz_d_gan_inverter_allocation(void){
    uz_assert(instance_counter < UZ_D_GAN_INVERTER_MAX_INSTANCES);
    uz_d_gan_inverter_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_d_gan_inverter_t* uz_d_gan_inverter_init(struct uz_d_gan_inverter_config_t config) {
    uz_assert(0U != config.base_address);
    uz_assert(0U != config.ip_clk_frequency_Hz); 
    uz_d_gan_inverter_t* self = uz_d_gan_inverter_allocation();
    self->config=config;
    return(self);
}

float uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(float dutyCyclePerCent) {
    // linear regression of duty cycle to temperature function
    return(dutyCyclePerCent*1.6234+20.13);
}


void uz_d_gan_inverter_update_states(uz_d_gan_inverter_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    self->outputs.PWMdutyCycPerCent_H1 = uz_d_gan_inverter_get_PWMdutyCycPerCent_H1(self->config.base_address);
    self->outputs.PWMdutyCycPerCent_L1 = uz_d_gan_inverter_get_PWMdutyCycPerCent_L1(self->config.base_address);
    self->outputs.PWMdutyCycPerCent_H2 = uz_d_gan_inverter_get_PWMdutyCycPerCent_H2(self->config.base_address);
    self->outputs.PWMdutyCycPerCent_L2 = uz_d_gan_inverter_get_PWMdutyCycPerCent_L2(self->config.base_address);
    self->outputs.PWMdutyCycPerCent_H3 = uz_d_gan_inverter_get_PWMdutyCycPerCent_H3(self->config.base_address);
    self->outputs.PWMdutyCycPerCent_L3 = uz_d_gan_inverter_get_PWMdutyCycPerCent_L3(self->config.base_address);

    //get OC status bits of each switch via bit mask
    self->outputs.OC_H1 = (((uz_d_gan_inverter_get_OC_GaN(self->config.base_address)) & 0x1) >> 0);
    self->outputs.OC_L1 = (((uz_d_gan_inverter_get_OC_GaN(self->config.base_address)) & 0x2) >> 1);
    self->outputs.OC_H2 = (((uz_d_gan_inverter_get_OC_GaN(self->config.base_address)) & 0x4) >> 2);
    self->outputs.OC_L2 = (((uz_d_gan_inverter_get_OC_GaN(self->config.base_address)) & 0x8) >> 3);
    self->outputs.OC_H3 = (((uz_d_gan_inverter_get_OC_GaN(self->config.base_address)) & 0x10) >> 4);
    self->outputs.OC_L3 = (((uz_d_gan_inverter_get_OC_GaN(self->config.base_address)) & 0x20) >> 5);

    //get FAULT status bits of each switch via bit mask
    self->outputs.FAULT_H1 = (((uz_d_gan_inverter_get_FAULT_GaN(self->config.base_address)) & 0x1) >> 0);
    self->outputs.FAULT_L1 = (((uz_d_gan_inverter_get_FAULT_GaN(self->config.base_address)) & 0x2) >> 1);
    self->outputs.FAULT_H2 = (((uz_d_gan_inverter_get_FAULT_GaN(self->config.base_address)) & 0x4) >> 2);
    self->outputs.FAULT_L2 = (((uz_d_gan_inverter_get_FAULT_GaN(self->config.base_address)) & 0x8) >> 3);
    self->outputs.FAULT_H3 = (((uz_d_gan_inverter_get_FAULT_GaN(self->config.base_address)) & 0x10) >> 4);
    self->outputs.FAULT_L3 = (((uz_d_gan_inverter_get_FAULT_GaN(self->config.base_address)) & 0x20) >> 5);

    //get I_DIAG status bits of each current amplifier via bit mask
    self->outputs.I_DC_DIAG = (((uz_d_gan_inverter_get_I_DIAG(self->config.base_address)) & 0x1) >> 0);
    self->outputs.I1_DIAG = (((uz_d_gan_inverter_get_I_DIAG(self->config.base_address)) & 0x2) >> 1);
    self->outputs.I2_DIAG = (((uz_d_gan_inverter_get_I_DIAG(self->config.base_address)) & 0x4) >> 2);
    self->outputs.I3_DIAG = (((uz_d_gan_inverter_get_I_DIAG(self->config.base_address)) & 0x8) >> 3);    

    self->outputs.GaN_ChipTempDegreesCelsius_H1 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self->outputs.PWMdutyCycPerCent_H1);
    self->outputs.GaN_ChipTempDegreesCelsius_H1 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self->outputs.PWMdutyCycPerCent_L1);
    self->outputs.GaN_ChipTempDegreesCelsius_H1 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self->outputs.PWMdutyCycPerCent_H2);
    self->outputs.GaN_ChipTempDegreesCelsius_H1 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self->outputs.PWMdutyCycPerCent_L2);
    self->outputs.GaN_ChipTempDegreesCelsius_H1 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self->outputs.PWMdutyCycPerCent_H3);
    self->outputs.GaN_ChipTempDegreesCelsius_H1 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self->outputs.PWMdutyCycPerCent_L3);
}
#endif