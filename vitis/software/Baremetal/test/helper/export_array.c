#include "export_array.h"
#include <stdlib.h>
#include <stdio.h>

void export_array(float *array, uint32_t size, char filepath[])

{
    FILE *file1 = fopen(filepath, "w");
    if (file1 != NULL)
    {
        for (uint32_t i = 0; i < size; i++)
        {
            fprintf(file1, "%d,%.4f\n", i, (double)array[i]);
        }
    }
}

void export_array_uint32(uint32_t *array, uint32_t size, char filepath[])

{
    FILE *file1 = fopen(filepath, "w");
    if (file1 != NULL)
    {
        for (uint32_t i = 0; i < size; i++)
        {
            fprintf(file1, "%d,%u\n", i, array[i]);
        }
    }
}