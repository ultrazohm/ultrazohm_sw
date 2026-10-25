#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include "export_array.h"
#include "unity.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Use a unique sibling so readers only see complete files, even when exports
 * and documentation builds run concurrently. */
static FILE *open_export(const char *filepath, char **temporary_path)
{
    TEST_ASSERT_NOT_NULL(filepath);
    const size_t size = strlen(filepath) + sizeof(".tmp.XXXXXX");
    *temporary_path = malloc(size);
    TEST_ASSERT_NOT_NULL(*temporary_path);
    snprintf(*temporary_path, size, "%s.tmp.XXXXXX", filepath);
    const int fd = mkstemp(*temporary_path);
    if (fd < 0)
    {
        free(*temporary_path);
        TEST_FAIL_MESSAGE("Could not create temporary CSV export");
        return NULL;
    }
    FILE *file = fdopen(fd, "w");
    if (file == NULL)
    {
        close(fd);
        remove(*temporary_path);
        free(*temporary_path);
        TEST_FAIL_MESSAGE("Could not open CSV export stream");
    }
    return file;
}

static void finish_export(FILE *file, char *temporary_path, const char *filepath, int write_ok)
{
    const int close_result = fclose(file);
    const int complete = write_ok && close_result == 0;
    const int published = complete && rename(temporary_path, filepath) == 0;
    if (!published)
    {
        remove(temporary_path);
    }
    free(temporary_path);
    TEST_ASSERT_TRUE_MESSAGE(complete, "Could not write or close CSV export");
    TEST_ASSERT_TRUE_MESSAGE(published, "Could not publish CSV export");
}

void export_array_float(uz_array_float_t exported_array, char filepath[])
{
    char *temporary_path;
    FILE *file = open_export(filepath, &temporary_path);
    int write_ok = 1;
    for (uint32_t i = 0; i < exported_array.length; i++)
    {
        if (fprintf(file, "%u,%.4f\n", i, (double)exported_array.data[i]) < 0)
        {
            write_ok = 0;
            break;
        }
    }
    finish_export(file, temporary_path, filepath, write_ok);
}

void export_array_uint32(uz_array_uint32_t exported_array, char filepath[])
{
    char *temporary_path;
    FILE *file = open_export(filepath, &temporary_path);
    int write_ok = 1;
    for (uint32_t i = 0; i < exported_array.length; i++)
    {
        if (fprintf(file, "%u,%u\n", i, exported_array.data[i]) < 0)
        {
            write_ok = 0;
            break;
        }
    }
    finish_export(file, temporary_path, filepath, write_ok);
}
