#include "uz_integrator.h"

float uz_integrator_eulerforward(float current_value, float old_value, float sample_time, bool clamping_active)
{
    float output_value = 0.0f;
    if (clamping_active)
    {
        output_value = old_value;
    }
    else
    {
        output_value = (current_value * sample_time) + old_value;
    }
    return output_value;
}

float uz_integrator_heun(float derivative_old, float derivative_predicted, float old_value, float sample_time, bool clamping_active)
{
    float output_value = 0.0f;
    if (clamping_active)
    {
        output_value = old_value;
    }
    else
    {
        output_value = old_value + 0.5f * sample_time * (derivative_old + derivative_predicted);
    }
    return output_value;
}