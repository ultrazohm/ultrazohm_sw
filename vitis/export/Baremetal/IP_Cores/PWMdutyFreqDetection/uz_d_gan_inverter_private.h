#pragma once
#include <stdint.h>

struct uz_d_gan_inverter{
  const uint32_t base_address;
  uint32_t PWMFreqTicks;
  uint32_t PWMhightimeTicks;
  uint32_t PWMlowtimeTicks;
  float PWMdutyCycPerCent;
  uint32_t OC_GaN_H1;
  uint32_t OC_GaN_L1;
  uint32_t OC_GaN_H2;
  uint32_t OC_GaN_L2;
  uint32_t OC_GaN_H3;
  uint32_t OC_GaN_L3;
  uint32_t FAULT_GaN_H1;
  uint32_t FAULT_GaN_L1;
  uint32_t FAULT_GaN_H2;
  uint32_t FAULT_GaN_L2;
  uint32_t FAULT_GaN_H3;
  uint32_t FAULT_GaN_L3;
  uint32_t I_DIAG;
  uint32_t I1_DIAG;
  uint32_t I2_DIAG;
  uint32_t I3_DIAG;
  uint32_t PWM_EN;
};
