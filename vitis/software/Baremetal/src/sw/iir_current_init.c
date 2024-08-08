#include "../include/iir_current.h"

struct uz_IIR_Filter_config iir_config_filt1 = {
            		.selection = LowPass_first_order,
            		.cutoff_frequency_Hz = 500.0f,
            		.sample_frequency_Hz = UZ_PWM_FREQUENCY
            };

uz_IIR_Filter_t* IIR_current_init_i_a1() {
	return(uz_signals_IIR_Filter_init(iir_config_filt1));

};

uz_IIR_Filter_t* IIR_current_init_i_b1() {
	return(uz_signals_IIR_Filter_init(iir_config_filt1));

};

uz_IIR_Filter_t* IIR_current_init_i_c1() {
	return(uz_signals_IIR_Filter_init(iir_config_filt1));

};
