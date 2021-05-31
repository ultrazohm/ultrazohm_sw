#pragma once
#include <stdint.h>
#include <stdbool.h>

#define	UZ_D_GAN_ADC_CONV_FACTORS {33.8780, 60.9756, 150.875, 150.875}
//ATTENTON: conversion factor depends on the used ADC board?
//	float PhaseCurrentAmpere = 33.8780;
//	float DC_CurrentAmpere = 60.9756;
//	float DC_VoltageVolt = 150.875;
//	float PhaseVoltageVolt = 150.875;

typedef struct _uz_d_gan_inverter_ADC_conversion_factors_{
	float PhaseCurrentAmpere;
	float DC_CurrentAmpere;
	float DC_VoltageVolt;
	float PhaseVoltageVolt;
} uz_d_gan_inverter_ADC_conversion_factors;

struct uz_d_gan_inverter{
  const uint32_t base_address;
  bool is_ready;
  uz_d_gan_inverter_ADC_conversion_factors uz_d_gan_inverter_ADC_conversion_factors;
  uint32_t clockFreqHz;
  uint32_t PWMFreqTicks_H1;
  uint32_t PWMhightimeTicks_H1;
  uint32_t PWMlowtimeTicks_H1;
  float PWMdutyCycPerCent_H1;
  float GaN_ChipTempDegreesCelsius_H1;
  uint32_t PWMFreqTicks_L1;
  uint32_t PWMhightimeTicks_L1;
  uint32_t PWMlowtimeTicks_L1;
  float PWMdutyCycPerCent_L1;
  float GaN_ChipTempDegreesCelsius_L1;
  uint32_t PWMFreqTicks_H2;
  uint32_t PWMhightimeTicks_H2;
  uint32_t PWMlowtimeTicks_H2;
  float PWMdutyCycPerCent_H2;
  float GaN_ChipTempDegreesCelsius_H2;
  uint32_t PWMFreqTicks_L2;
  uint32_t PWMhightimeTicks_L2;
  uint32_t PWMlowtimeTicks_L2;
  float PWMdutyCycPerCent_L2;
  float GaN_ChipTempDegreesCelsius_L2;
  uint32_t PWMFreqTicks_H3;
  uint32_t PWMhightimeTicks_H3;
  uint32_t PWMlowtimeTicks_H3;
  float PWMdutyCycPerCent_H3;
  float GaN_ChipTempDegreesCelsius_H3;
  uint32_t PWMFreqTicks_L3;
  uint32_t PWMhightimeTicks_L3;
  uint32_t PWMlowtimeTicks_L3;
  float PWMdutyCycPerCent_L3;
  float GaN_ChipTempDegreesCelsius_L3;
  uint32_t OC_GaN;
  uint32_t FAULT_GaN;
  uint32_t I_DIAG;
  uint32_t PWM_EN;
};
