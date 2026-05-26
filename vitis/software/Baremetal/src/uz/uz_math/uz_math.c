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

float uz_math_mean_uint32_t(uz_array_uint32_t array)
{
    float mean = 0.0f;
    for (uint32_t i = 0; i < array.length; i++)
    {
        mean += (float)array.data[i];
    }
    mean = mean / (float)array.length;
    return mean;
}

float uz_math_variance_uncorrected(uz_array_float_t array)
{
    // See https://en.wikipedia.org/wiki/Variance regarding correction with 1/n or 1/(n-1)
    float mean = uz_math_mean(array);
    float variance = 0.0f;
    for (uint32_t i = 0; i < array.length; i++)
    {
        variance += (array.data[i] - mean) * (array.data[i] - mean);
    }
    variance = variance / (float)array.length;
    return (variance);
}

float uz_math_standard_deviation(uz_array_float_t array)
{
    float variance = uz_math_variance_uncorrected(array);
    return sqrtf(variance);
}