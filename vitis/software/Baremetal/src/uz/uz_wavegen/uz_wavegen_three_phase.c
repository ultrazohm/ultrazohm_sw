#include "../uz_global_configuration.h"
#include "uz_wavegen.h"
#include <math.h>
#include "../uz_math_constants.h"
#include "../uz_HAL.h"
#include "../uz_SystemTime/uz_SystemTime.h"

uz_3ph_abc_t uz_wavegen_three_phase_sample(float amplitude, float frequency_Hz, float offset)
{
    uz_assert(frequency_Hz > 0.0f);
    float t_Sec = uz_SystemTime_GetGlobalTimeInSec();
    float angle = 2.0f * UZ_PIf * t_Sec * frequency_Hz;
    uz_3ph_abc_t sine_output = {
        .a = amplitude * sinf(angle) + offset,
        .b = amplitude * sinf(angle + (2.0f * UZ_PIf / 3.0f)) + offset,
        .c = amplitude * sinf(angle + (4.0f * UZ_PIf / 3.0f)) + offset};
    return sine_output;
}