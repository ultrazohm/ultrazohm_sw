#pragma once
#include <stdint.h>

struct uz_d_gan_inverter{
  const uint32_t base_address;
  uint32_t PWMFreqTicks;
  uint32_t PWMhightimeTicks;
  uint32_t PWMlowtimeTicks;
  float PWMdutyCycPerCent;
};
