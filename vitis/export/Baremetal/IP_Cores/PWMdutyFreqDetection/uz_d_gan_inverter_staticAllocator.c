#include "uz_d_gan_inverter_staticAllocator.h"
#include "xparameters.h"

static uz_d_gan_inverter d_gan_inverter_instance1={
  .base_address=XPAR_PWMDUTYFREQDETECTION_0_BASEADDR,
  .PWMFreqTicks=0,
  .PWMhightimeTicks=0,
  .PWMlowtimeTicks=0,
  .PWMdutyCycPerCent=0
};

uz_d_gan_inverter_handle uz_d_gan_inverter_allocateAndInit_instance1(void){
  return (uz_d_gan_inverter_init(&d_gan_inverter_instance1) );
}
