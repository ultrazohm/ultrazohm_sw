#include "export_array.h"
#include <stdlib.h>
#include <stdio.h>

void export_histogram(float *array, uint32_t size,char filepath[])
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

void uz_nn_layer_matrix_export(uz_matrix_t const *const self, char *fname)
{
    FILE *f = fopen(fname, "w");
    for (uint32_t i = 0; i < self->length_of_data; i++)
    {
        fprintf(f, "%.6f,", (double)self->data[i]);
    }
    fclose(f);
}