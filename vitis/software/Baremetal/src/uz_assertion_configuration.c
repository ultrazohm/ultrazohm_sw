#include "uz_platform_state_machine.h"
#include <stdbool.h>
#include "uz/uz_HAL.h"

#include "xil_assert.h"


static void uz_assertCallback(const char8 *file, s32 line);


void uz_assert_configuration(void){
    Xil_AssertSetCallback((Xil_AssertCallback)uz_assertCallback);
}

static void uz_assertCallback(const char8 *file, s32 line)
{
    uz_printf("\r\n RPU: Assertion in file %s on line %d\r\n", file, line);
    ultrazohm_state_machine_set_error(true);
}