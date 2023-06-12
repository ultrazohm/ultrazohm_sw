#include <stdint.h>
float limit_value(float value, float limit);
float uz_PI_controller(
		// axi inputs
		float axi_referenceValue, float axi_sampletime, float axi_KI, float axi_KP, float axi_limit, bool axi_reset,
		// hw input
		float actualValue,
		// hw debug output
		float *d_I_sum, float *d_error, float *d_P_sum, float *d_preIntegrator, float *d_KI, float *d_KP, float *d_limit, float *d_preLimit
		);
