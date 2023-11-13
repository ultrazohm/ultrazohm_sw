#include "uz_math.h"

#include <math.h>

float uz_math_mean(float *vector, uint32_t size)

{

    float mean = 0.0f;

    for (uint32_t i = 0; i < size; i++)

    {

        mean += vector[i];
    }

    mean = mean / (float)size;

    return mean;
}

float uz_math_variance(float *vector, uint32_t size)
{

    float mean = uz_math_mean(vector, size);

    float variance = 0.0f;

    for (uint32_t i = 0; i < size; i++)

    {

        variance += (vector[i] - mean) * (vector[i] - mean);
    }

    variance = variance / (float)size;

    return (variance);
}

float uz_math_standard_deviation(float *vector, uint32_t size)
{

    float variance = uz_math_variance(vector, size);

    return sqrtf(variance);
}