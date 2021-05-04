#include "uz_d_gan_inverter_private.h"
#include "uz_d_gan_inverter_hwAddresses.h"
#include "../../uz/uz_HAL.h"
#include "uz_d_gan_inverter.h"

float uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(uz_d_gan_inverter_handle self, float dutyCycPerCent){
	uz_assert_not_NULL(self);
	return (dutyCycPerCent*1.6234+20.13);
}
