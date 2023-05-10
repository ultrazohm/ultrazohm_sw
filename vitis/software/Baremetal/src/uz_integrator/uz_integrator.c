#include "uz_integrator.h"

float uz_integrator_eulerforward(float current_value, float old_value, float time_step, bool clamping_active)
{
    float output_value = 0.0f;
    if (clamping_active)
    {
        output_value = old_value;
    }
    else
    {
        output_value = (current_value * time_step + old_value);
    }
    return output_value;
}