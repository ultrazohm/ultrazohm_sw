#include <stdbool.h>

#include "../include/uz_apu_assert_configuration.h"
#include "xil_assert.h"
#include "FreeRTOS.h"
#include "task.h"

#include "../uz/uz_HAL.h"

static void uz_apu_assert_callback(const char8 *file, s32 line);

void uz_apu_assert_configuration(void)
{
    Xil_AssertSetCallback((Xil_AssertCallback)uz_apu_assert_callback);
}

static void uz_apu_assert_callback(const char8 *file, s32 line)
{
    uz_printf("\r\nAPU: Assertion in file %s on line %ld\r\n", file, (long)line);
    taskDISABLE_INTERRUPTS();
}
