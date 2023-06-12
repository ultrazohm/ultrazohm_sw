#include <stdint.h>

bool uz_PI_Controller_sample_parallel(float referenceValue, float actualValue, float sampletime, const float KI, const float KP, float limit, bool reset, float *I_sum, float *out);
void uz_FOC(float actual_id, float actual_iq, float sampletime, bool reset_PL, float *ref_ud, float *ref_uq, float set_i_d, float set_i_q, float KP_d, float KI_d, float KP_q, float KI_q, bool reset_PS, float limit, float *out_KP_d, float *out_idref, bool *out_status, float *test_out_pl);
