#include <stdbool.h>
#include "xparameters.h"
#include "../uz_d_gan_inverter/uz_d_gan_inverter_staticAllocator.h"

static uz_d_gan_inverter uz_d_gan_inverter_instance1={
  .base_address=XPAR_UZ_D_GAN_INVERTER_UZ_D_GAN_INVERTER_0_BASEADDR,
  .is_ready=0,
  .clockFreqHz=100000000,
  .PWMFreqTicks_H1=false,
  .PWMhightimeTicks_H1=0,
  .PWMlowtimeTicks_H1=0,
  .PWMdutyCycPerCent_H1=0,
  .PWMFreqTicks_L1=0,
  .PWMhightimeTicks_L1=0,
  .PWMlowtimeTicks_L1=0,
  .PWMdutyCycPerCent_L1=0,
  .PWMFreqTicks_H2=0,
  .PWMhightimeTicks_H2=0,
  .PWMlowtimeTicks_H2=0,
  .PWMdutyCycPerCent_H2=0,
  .PWMFreqTicks_L2=0,
  .PWMhightimeTicks_L2=0,
  .PWMlowtimeTicks_L2=0,
  .PWMdutyCycPerCent_L2=0,
  .PWMFreqTicks_H3=0,
  .PWMhightimeTicks_H3=0,
  .PWMlowtimeTicks_H3=0,
  .PWMdutyCycPerCent_H3=0,
  .PWMFreqTicks_L3=0,
  .PWMhightimeTicks_L3=0,
  .PWMlowtimeTicks_L3=0,
  .PWMdutyCycPerCent_L3=0,
  .OC_GaN=0,
  .FAULT_GaN=0,
  .I_DIAG=0,
  .PWM_EN=0
};

uz_d_gan_inverter_handle uz_d_gan_inverter_allocateAndInit_instance1(void){
  return (uz_d_gan_inverter_init(&uz_d_gan_inverter_instance1) );
}
