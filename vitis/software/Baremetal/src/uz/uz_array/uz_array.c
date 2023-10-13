#include "uz_array.h"

#include <stdio.h>

// helpers
void resetFloatArray(float *arr, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        arr[i] = 0.0f;
    }
}

void resetuintArray(uint32_t *arr, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        arr[i] = 0;
    }
}

void exportFloatArrayToCSV(const char *filename, const float *array, int size)
{
    // Check if the file can be opened for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Unable to create the CSV file");
        return;
    }

    // Write the array to the file in CSV format
    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%.8f", (double)array[i]); // Assuming 2 decimal places, adjust as needed
        if (i < size - 1)
        {
            fprintf(file, ",");
        }
        else
        {
            fprintf(file, "\n");
        }
    }

    // Close the file
    fclose(file);
}