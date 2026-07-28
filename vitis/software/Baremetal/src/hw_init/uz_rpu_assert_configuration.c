#include <stdbool.h>

#include "../include/uz_rpu_assert_configuration.h"
#include "xil_assert.h"

#include "../uz/uz_HAL.h"
#include "../include/uz_platform_state_machine.h"
#include "../include/deskbench_control.h"
#include "../globalData.h"

extern DS_Data Global_Data;

static void uz_rpu_assert_callback(const char8 *file, s32 line);

void uz_rpu_assert_configuration(void)
{
    Xil_AssertSetCallback((Xil_AssertCallback)uz_rpu_assert_callback);
}

static void uz_rpu_assert_callback(const char8 *file, s32 line)
{
    uz_printf("\r\n RPU: Assertion in file %s on line %d\r\n", file, line);
    ultrazohm_state_machine_set_error(true);
    disable_dut(&Global_Data);
    disable_prime_mover(&Global_Data);
}
