#include "../include/init_torque_filter.h"

struct uz_IIR_Filter_config torque_filter_config = {
		.cutoff_frequency_Hz = 100.0f,
		.sample_frequency_Hz = UZ_PWM_FREQUENCY/INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE,
		.selection = LowPass_first_order
};

uz_IIR_Filter_t* init_torque_filter(void){
	return uz_signals_IIR_Filter_init(torque_filter_config);
}

