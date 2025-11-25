#include "xparameters.h"
#include "uz_PWM_3L_staticAllocator.h"
#include "uz_PWM_3L_hw.h"
#include "uz_PWM_3L_private.h"

static PWM_3L PWM_3L_instance = {
	.base_address = 0, //XPAR_PWM_3LEVEL_CONTROL_0_BASEADDR
	.carrier_freq = 100U,
	.phase_shift = 0,
	.u1 = 0.7
};

PWM_3L_handle uz_PWM_3L_staticAllocator(void){
	return(&PWM_3L_instance);
}
