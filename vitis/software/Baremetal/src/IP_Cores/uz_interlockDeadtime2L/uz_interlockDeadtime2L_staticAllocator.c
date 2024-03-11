#include "uz_interlockDeadtime2L_staticAllocator.h"
#include "uz_interlockDeadtime2L_private.h"
#include "xparameters.h"

static uz_interlockDeadtime2L interlock_PWM_0 = { .base_address = XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_INTERLOCKDEADTIME_0_BASEADDR, .clock_frequency_MHz = 100, .deadtime_us = 0.15, .inverse_bottom_switch = false };
static uz_interlockDeadtime2L interlock_PWM_1 = { .base_address = XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_INTERLOCKDEADTIME_1_BASEADDR, .clock_frequency_MHz = 100, .deadtime_us = 0.15, .inverse_bottom_switch = false };
static uz_interlockDeadtime2L interlock_PWM_2 = { .base_address = XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_INTERLOCKDEADTIME_2_BASEADDR, .clock_frequency_MHz = 100, .deadtime_us = 1, .inverse_bottom_switch = false };
static uz_interlockDeadtime2L interlock_PWM_3 = { .base_address = XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_INTERLOCKDEADTIME_3_BASEADDR, .clock_frequency_MHz = 100, .deadtime_us = 1, .inverse_bottom_switch = false };

uz_interlockDeadtime2L_handle uz_interlockDeadtime2L_staticAllocator_PWM_0(void) {
	return (uz_interlockDeadtime2L_init(&interlock_PWM_0));
}

uz_interlockDeadtime2L_handle uz_interlockDeadtime2L_staticAllocator_PWM_1(void) {
	return (uz_interlockDeadtime2L_init(&interlock_PWM_1));
}

uz_interlockDeadtime2L_handle uz_interlockDeadtime2L_staticAllocator_PWM_2(void) {
	return (uz_interlockDeadtime2L_init(&interlock_PWM_2));
}

uz_interlockDeadtime2L_handle uz_interlockDeadtime2L_staticAllocator_PWM_3(void) {
	return (uz_interlockDeadtime2L_init(&interlock_PWM_3));
}
