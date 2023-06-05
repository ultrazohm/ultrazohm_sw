#include <stdint.h>
float limit_value(float value, float limit);
float uz_PI_controller(float referenceValue, float actualValue, float sampletime, float KI, float KP, float limit, bool reset, float *axi_referenceValue, float *axi_actualValue, float *error, float *P_sum);
