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

uz_d_gan_inverter_t* uz_d_gan_inverter_init(struct uz_d_gan_inverter_config_t config, struct uz_d_gan_inverter_outputs_t outputs) {
    uz_assert(0U != config.base_address);
    uz_assert(0U != config.ip_clk_frequency_Hz); 
    uz_d_gan_inverter_t* self = uz_d_gan_inverter_allocation();
    self->config=config;
    self->outputs=outputs;
    return(self);
}

float uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(float dutyCyclePerCent) {
    // linear regression of duty cycle to temperature function
    return(dutyCyclePerCent*1.6235+20.107);
}

void uz_d_gan_inverter_update_states(uz_d_gan_inverter_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    //get OC status bit of each switch via bit mask and bit shift
    self->outputs.OC = uz_d_gan_inverter_get_OC_GaN(self->config.base_address);
    self->outputs.OC_H1 = (((self->outputs.OC) & 0x01) >> 0);
    self->outputs.OC_L1 = (((self->outputs.OC) & 0x02) >> 1);
    self->outputs.OC_H2 = (((self->outputs.OC) & 0x04) >> 2);
    self->outputs.OC_L2 = (((self->outputs.OC) & 0x08) >> 3);
    self->outputs.OC_H3 = (((self->outputs.OC) & 0x10) >> 4);
    self->outputs.OC_L3 = (((self->outputs.OC) & 0x20) >> 5);

    //get FAULT status bit of each switch via bit mask and bit shift
    self->outputs.FAULT = uz_d_gan_inverter_get_FAULT_GaN(self->config.base_address);
    self->outputs.FAULT_H1 = (((self->outputs.FAULT) & 0x01) >> 0);
    self->outputs.FAULT_L1 = (((self->outputs.FAULT) & 0x02) >> 1);
    self->outputs.FAULT_H2 = (((self->outputs.FAULT) & 0x04) >> 2);
    self->outputs.FAULT_L2 = (((self->outputs.FAULT) & 0x08) >> 3);
    self->outputs.FAULT_H3 = (((self->outputs.FAULT) & 0x10) >> 4);
    self->outputs.FAULT_L3 = (((self->outputs.FAULT) & 0x20) >> 5);

    //get I_DIAG status bit of each current amplifier via bit mask and bit shift
    self->outputs.I_DIAG = uz_d_gan_inverter_get_I_DIAG(self->config.base_address);
    self->outputs.I_DC_DIAG = (((self->outputs.I_DIAG) & 0x01) >> 0);
    self->outputs.I1_DIAG = (((self->outputs.I_DIAG) & 0x02) >> 1);
    self->outputs.I2_DIAG = (((self->outputs.I_DIAG) & 0x04) >> 2);
    self->outputs.I3_DIAG = (((self->outputs.I_DIAG) & 0x08) >> 3);    

    //get duty cycle information of each switch containing the chip temperature information
    self->outputs.PWMdutyCycPerCent_H1 = uz_d_gan_inverter_get_PWMdutyCycPerCent_H1(self->config.base_address);
    self->outputs.PWMdutyCycPerCent_L1 = uz_d_gan_inverter_get_PWMdutyCycPerCent_L1(self->config.base_address);
    self->outputs.PWMdutyCycPerCent_H2 = uz_d_gan_inverter_get_PWMdutyCycPerCent_H2(self->config.base_address);
    self->outputs.PWMdutyCycPerCent_L2 = uz_d_gan_inverter_get_PWMdutyCycPerCent_L2(self->config.base_address);
    self->outputs.PWMdutyCycPerCent_H3 = uz_d_gan_inverter_get_PWMdutyCycPerCent_H3(self->config.base_address);
    self->outputs.PWMdutyCycPerCent_L3 = uz_d_gan_inverter_get_PWMdutyCycPerCent_L3(self->config.base_address);

    //calculate chip temperatures in degrees celsius from the duty cycle information
    self->outputs.GaN_ChipTempDegreesCelsius_H1 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self->outputs.PWMdutyCycPerCent_H1);
    self->outputs.GaN_ChipTempDegreesCelsius_L1 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self->outputs.PWMdutyCycPerCent_L1);
    self->outputs.GaN_ChipTempDegreesCelsius_H2 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self->outputs.PWMdutyCycPerCent_H2);
    self->outputs.GaN_ChipTempDegreesCelsius_L2 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self->outputs.PWMdutyCycPerCent_L2);
    self->outputs.GaN_ChipTempDegreesCelsius_H3 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self->outputs.PWMdutyCycPerCent_H3);
    self->outputs.GaN_ChipTempDegreesCelsius_L3 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self->outputs.PWMdutyCycPerCent_L3);
}
#endif