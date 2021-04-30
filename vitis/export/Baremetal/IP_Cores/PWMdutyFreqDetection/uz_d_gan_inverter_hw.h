#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct uz_d_gan_inverter uz_d_gan_inverter;
typedef uz_d_gan_inverter *uz_d_gan_inverter_handle;

uz_d_gan_inverter_handle uz_d_gan_inverter_init(uz_d_gan_inverter_handle self);
int uz_d_gan_inverter_get_PWMFreqTicks(uz_d_gan_inverter_handle self);
int uz_d_gan_inverter_get_PWMhightimeTicks(uz_d_gan_inverter_handle self);
int uz_d_gan_inverter_get_PWMlowtimeTicks(uz_d_gan_inverter_handle self);
float uz_d_gan_inverter_get_PWMdutyCycPerCent(uz_d_gan_inverter_handle self);
