#include "export_array.h"
#include <stdlib.h>
#include <stdio.h>

void export_histogram(float *array, uint32_t size,char* filepath[])
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