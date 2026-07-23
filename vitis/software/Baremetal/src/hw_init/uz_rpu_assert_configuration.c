#include <stdbool.h>

#include "../include/uz_rpu_assert_configuration.h"
#include "xil_assert.h"

#include "../uz/uz_HAL.h"
#include "../include/uz_platform_state_machine.h"
#include "../globalData.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"

extern DS_Data Global_Data;


static void uz_rpu_assert_callback(const char8 *file, s32 line);

void uz_rpu_assert_configuration(void)
{
    Xil_AssertSetCallback((Xil_AssertCallback)uz_rpu_assert_callback);
}

static void uz_rpu_assert_callback(const char8 *file, s32 line)
{
    uz_printf("\r\n RPU: Assertion in file %s on line %d\r\n", file, line);
    uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0, true, true, true);
    uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_1, true, true, true);

    ultrazohm_state_machine_set_error(true);
}
