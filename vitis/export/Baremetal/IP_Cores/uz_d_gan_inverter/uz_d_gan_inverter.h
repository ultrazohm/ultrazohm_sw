#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct uz_d_gan_inverter uz_d_gan_inverter;
typedef uz_d_gan_inverter *uz_d_gan_inverter_handle;

float uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(uz_d_gan_inverter_handle self, float dutyCycPerCent);
void uz_d_gan_inverter_UpdateStates(uz_d_gan_inverter_handle self);
