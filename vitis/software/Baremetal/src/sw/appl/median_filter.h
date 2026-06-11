#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include <stdbool.h>

#define MEDIAN_FILTER_SIZE    (5U)

/**
 * @brief Median filter instance data.
 */
typedef struct
{
    float buffer[MEDIAN_FILTER_SIZE];
    unsigned int index;
    bool initialized;
} MedianFilter5_t;

/**
 * @brief Initializes a median filter instance.
 *
 * @param filter Pointer to filter instance
 * @param initialValue Initial value used to fill the buffer
 */
void MedianFilter5_Init(MedianFilter5_t *filter, float initialValue);

/**
 * @brief Updates the filter with a new sample.
 *
 * @param filter Pointer to filter instance
 * @param newValue New input sample
 *
 * @return Median of the last five samples
 */
float MedianFilter5_Update(MedianFilter5_t *filter, float newValue);

/**
 * @brief Resets the filter.
 *
 * After reset, the next call to Init() should be used before Update().
 *
 * @param filter Pointer to filter instance
 */
void MedianFilter5_Reset(MedianFilter5_t *filter);

#endif /* MEDIAN_FILTER_H */
