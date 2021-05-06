#pragma once
#include <stdint.h>

struct uz_d_gan_inverter{
  const uint32_t base_address;
  uint32_t PWMFreqTicks_H1;
  uint32_t PWMhightimeTicks_H1;
  uint32_t PWMlowtimeTicks_H1;
  float PWMdutyCycPerCent_H1;
  uint32_t PWMFreqTicks_L1;
  uint32_t PWMhightimeTicks_L1;
  uint32_t PWMlowtimeTicks_L1;
  float PWMdutyCycPerCent_L1;
  uint32_t PWMFreqTicks_H2;
  uint32_t PWMhightimeTicks_H2;
  uint32_t PWMlowtimeTicks_H2;
  float PWMdutyCycPerCent_H2;
  uint32_t PWMFreqTicks_L2;
  uint32_t PWMhightimeTicks_L2;
  uint32_t PWMlowtimeTicks_L2;
  float PWMdutyCycPerCent_L2;
  uint32_t PWMFreqTicks_H3;
  uint32_t PWMhightimeTicks_H3;
  uint32_t PWMlowtimeTicks_H3;
  float PWMdutyCycPerCent_H3;
  uint32_t PWMFreqTicks_L3;
  uint32_t PWMhightimeTicks_L3;
  uint32_t PWMlowtimeTicks_L3;
  float PWMdutyCycPerCent_L3;
  uint32_t OC_GaN;
  uint32_t FAULT_GaN;
  uint32_t I_DIAG;
  uint32_t PWM_EN;
};
