#include <stdint.h>
void uz_FOC(
		// axi inputs
		float axi_id_reference, float axi_iq_reference, float axi_sampletime, float axi_id_KI, float axi_id_KP, float axi_iq_KI, float axi_iq_KP, float axi_limit, bool axi_reset,
		// hw input
		float id_actual, float iq_actual, bool reset_PL,
		// hw output
		float *ud_ref, float *uq_ref);
float uz_PI_Controller_sample_parallel(float referenceValue, float actualValue, float sampletime, const float KI, const float KP, float limit, bool reset, float *I_sum);
float limit_value(float value, float limit);
