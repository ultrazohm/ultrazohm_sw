#include "../include/uz_IIR_Filter_init.h"

static const struct uz_IIR_Filter_config speed_prefilter_Last_config;


struct uz_IIR_Filter_t* uz_speed_prefilter_Last_init(void) {
	return (uz_signals_IIR_Filter_init(speed_prefilter_Last_config));
}

static const struct uz_IIR_Filter_config speed_prefilter_Last_config = {
	.selection = LowPass_first_order,
	.cutoff_frequency_Hz = 10.0f,
	.sample_frequency_Hz = 10e3f
};
