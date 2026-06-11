#include "median_filter.h"

/* Swap two float values */
static void Swap(float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

/* Sort five values and return the middle element */
static float CalculateMedian5(const float values[MEDIAN_FILTER_SIZE])
{
    float sorted[MEDIAN_FILTER_SIZE];
    unsigned int i;
    unsigned int j;

    for (i = 0U; i < MEDIAN_FILTER_SIZE; i++)
    {
        sorted[i] = values[i];
    }

    for (i = 0U; i < MEDIAN_FILTER_SIZE - 1U; i++)
    {
        for (j = i + 1U; j < MEDIAN_FILTER_SIZE; j++)
        {
            if (sorted[j] < sorted[i])
            {
                Swap(&sorted[i], &sorted[j]);
            }
        }
    }

    return sorted[MEDIAN_FILTER_SIZE / 2U];
}

void MedianFilter5_Init(MedianFilter5_t *filter, float initialValue)
{
    unsigned int i;

    for (i = 0U; i < MEDIAN_FILTER_SIZE; i++)
    {
        filter->buffer[i] = initialValue;
    }

    filter->index = 0U;
    filter->initialized = true;
}

float MedianFilter5_Update(MedianFilter5_t *filter, float newValue)
{
    if (!filter->initialized)
    {
        MedianFilter5_Init(filter, newValue);
    }

    filter->buffer[filter->index] = newValue;
    filter->index++;

    if (filter->index >= MEDIAN_FILTER_SIZE)
    {
        filter->index = 0U;
    }

    return CalculateMedian5(filter->buffer);
}

void MedianFilter5_Reset(MedianFilter5_t *filter)
{
    filter->index = 0U;
    filter->initialized = false;
}
