#include "uz_math.h"

#include <math.h>

float uz_math_mean(uz_array_float_t array)
{
    float mean = 0.0f;
    for (uint32_t i = 0; i < array.length; i++)
    {
        mean += array.data[i];
    }
    mean = mean / (float)array.length;
    return mean;
}

float uz_math_variance(uz_array_float_t array)
{
    float mean = uz_math_mean(array);
    float variance = 0.0f;
    for (uint32_t i = 0; i < array.length; i++)
    {
        variance += (array.data[i] - mean) * (array.data[i] - mean);
    }
    variance = variance / array.length;
    return (variance);
}

float uz_math_standard_deviation(uz_array_float_t array)
{
    float variance = uz_math_variance(array);
    return sqrtf(variance);
}