#include <stdbool.h>
#include "xil_assert.h"

#include "../uz/uz_HAL.h"
#include "../include/uz_platform_state_machine.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../../globalData.h"
#include <stdbool.h>


static void uz_assertCallback(const char8 *file, s32 line);


void uz_assert_configuration(void){
    Xil_AssertSetCallback((Xil_AssertCallback)uz_assertCallback);
}

static void uz_assertCallback(const char8 *file, s32 line)
{
    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, true, true, true);
    uz_printf("\r\n RPU: Assertion in file %s on line %d\r\n", file, line);
    ultrazohm_state_machine_set_error(true);
}
