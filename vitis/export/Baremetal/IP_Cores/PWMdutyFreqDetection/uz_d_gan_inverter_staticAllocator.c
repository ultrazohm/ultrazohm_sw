#include "uz_d_gan_inverter_staticAllocator.h"
#include "xparameters.h"

static uz_d_gan_inverter d_gan_inverter_instance1={
  .base_address=XPAR_UZ_D_GAN_INVERTER_UZ_D_GAN_INVERTER_0_BASEADDR,
  .PWMFreqTicks_H1=0,
  .PWMhightimeTicks_H1=0,
  .PWMlowtimeTicks_H1=0,
  .PWMdutyCycPerCent_H1=0,
  .PWMFreqTicks_L1=0,
  .PWMhightimeTicks_L1=0,
  .PWMlowtimeTicks_L1=0,
  .PWMdutyCycPerCent_L1=0,
  .OC_GaN_H1=0,
  .OC_GaN_L1=0,
  .OC_GaN_H2=0,
  .OC_GaN_L2=0,
  .OC_GaN_H3=0,
  .OC_GaN_L3=0,
  .FAULT_GaN_H1=0,
  .FAULT_GaN_L1=0,
  .FAULT_GaN_H2=0,
  .FAULT_GaN_L2=0,
  .FAULT_GaN_H3=0,
  .FAULT_GaN_L3=0,
  .I_DIAG=0,
  .I1_DIAG=0,
  .I2_DIAG=0,
  .I3_DIAG=0,
  .PWM_EN=0
};

uz_d_gan_inverter_handle uz_d_gan_inverter_allocateAndInit_instance1(void){
  return (uz_d_gan_inverter_init(&d_gan_inverter_instance1) );
}
