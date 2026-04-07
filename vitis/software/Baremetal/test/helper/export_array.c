#include "export_array.h"
#include <stdlib.h>
#include <stdio.h>

void export_array_float(uz_array_float_t exported_array, char filepath[])

{
    FILE *file1 = fopen(filepath, "w");
    if (file1 != NULL)
    {
        for (uint32_t i = 0; i < exported_array.length; i++)
        {
            fprintf(file1, "%d,%.4f\n", i, (double)exported_array.data[i]);
        }
    }
}

void export_array_uint32(uz_array_uint32_t exported_array, char filepath[])
{
    FILE *file1 = fopen(filepath, "w");
    if (file1 != NULL)
    {
        for (uint32_t i = 0; i < exported_array.length; i++)
        {
            fprintf(file1, "%d,%u\n", i, exported_array.data[i]);
        }
    }
}