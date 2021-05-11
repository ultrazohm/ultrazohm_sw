#include "../uz_d_gan_inverter/uz_d_gan_inverter.h"
#include "../uz_d_gan_inverter/uz_d_gan_inverter_hw.h"

#include "../../uz/uz_HAL.h"
#include "../uz_d_gan_inverter/uz_d_gan_inverter_hwAddresses.h"
#include "../uz_d_gan_inverter/uz_d_gan_inverter_private.h"

float uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(uz_d_gan_inverter_handle self, float dutyCycPerCent){
	uz_assert_not_NULL(self);
	return (dutyCycPerCent*1.6234+20.13);
}

void uz_d_gan_inverter_UpdateStates(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);

	uz_d_gan_inverter_get_PWMFreqTicks_H1(self);
	uz_d_gan_inverter_get_PWMhightimeTicks_H1(self);
	uz_d_gan_inverter_get_PWMlowtimeTicks_H1(self);
	uz_d_gan_inverter_get_PWMdutyCycPerCent_H1(self);

	uz_d_gan_inverter_get_PWMFreqTicks_L1(self);
	uz_d_gan_inverter_get_PWMhightimeTicks_L1(self);
	uz_d_gan_inverter_get_PWMlowtimeTicks_L1(self);
	uz_d_gan_inverter_get_PWMdutyCycPerCent_L1(self);

	uz_d_gan_inverter_get_PWMFreqTicks_H2(self);
	uz_d_gan_inverter_get_PWMhightimeTicks_H2(self);
	uz_d_gan_inverter_get_PWMlowtimeTicks_H2(self);
	uz_d_gan_inverter_get_PWMdutyCycPerCent_H2(self);

	uz_d_gan_inverter_get_PWMFreqTicks_L2(self);
	uz_d_gan_inverter_get_PWMhightimeTicks_L2(self);
	uz_d_gan_inverter_get_PWMlowtimeTicks_L2(self);
	uz_d_gan_inverter_get_PWMdutyCycPerCent_L2(self);

	uz_d_gan_inverter_get_PWMFreqTicks_H3(self);
	uz_d_gan_inverter_get_PWMhightimeTicks_H3(self);
	uz_d_gan_inverter_get_PWMlowtimeTicks_H3(self);
	uz_d_gan_inverter_get_PWMdutyCycPerCent_H3(self);

	uz_d_gan_inverter_get_PWMFreqTicks_L3(self);
	uz_d_gan_inverter_get_PWMhightimeTicks_L3(self);
	uz_d_gan_inverter_get_PWMlowtimeTicks_L3(self);
	uz_d_gan_inverter_get_PWMdutyCycPerCent_L3(self);

	uz_d_gan_inverter_get_FAULT_GaN(self);
	uz_d_gan_inverter_get_OC_GaN(self);
	uz_d_gan_inverter_get_I_DIAG(self);

	self->GaN_ChipTempDegreesCelsius_H1 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self, self->PWMdutyCycPerCent_H1);
	self->GaN_ChipTempDegreesCelsius_L1 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self, self->PWMdutyCycPerCent_L1);
	self->GaN_ChipTempDegreesCelsius_H2 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self, self->PWMdutyCycPerCent_H2);
	self->GaN_ChipTempDegreesCelsius_L2 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self, self->PWMdutyCycPerCent_L2);
	self->GaN_ChipTempDegreesCelsius_H3 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self, self->PWMdutyCycPerCent_H3);
	self->GaN_ChipTempDegreesCelsius_L3 = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(self, self->PWMdutyCycPerCent_L3);
}
