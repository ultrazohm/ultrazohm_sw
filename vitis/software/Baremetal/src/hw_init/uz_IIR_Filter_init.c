#include "../include/uz_IIR_Filter_init.h"
#include "../uz/uz_global_configuration.h"

static const struct uz_IIR_Filter_config Config_SpeedFilter_Load = {
	.selection = LowPass_first_order,
	.cutoff_frequency_Hz = 10.0f,
	.sample_frequency_Hz = UZ_CONTROL_FREQUENCY
};


struct uz_IIR_Filter_t* init_SpeedFilter_Load(void) {
	return (uz_signals_IIR_Filter_init(Config_SpeedFilter_Load));
}


