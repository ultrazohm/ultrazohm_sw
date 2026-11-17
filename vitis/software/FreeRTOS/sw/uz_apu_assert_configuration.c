#include <stdbool.h>

#include "../include/uz_apu_assert_configuration.h"
#include "xil_assert.h"
#include "FreeRTOS.h"
#include "task.h"

#include "../uz/uz_HAL.h"

/* The A53 FreeRTOS port of Vitis 2022.2 does not define portMEMORY_BARRIER(),
 * so FreeRTOS.h defines it empty and xTaskResumeAll() can hang the A53 with
 * all interrupts masked when two tasks wake up at once (e.g. under network
 * load). tcl_scripts/vitis_patch_UltraZohm_freertos_bsp.tcl adds the define to
 * the generated FreeRTOSConfig.h, but every regeneration of the BSP (also from
 * the Vitis GUI) drops it again. Refuse to build against such a BSP. */
#define UZ_APU_STRINGIFY_(x) #x
#define UZ_APU_STRINGIFY(x) UZ_APU_STRINGIFY_(x)
_Static_assert(sizeof(UZ_APU_STRINGIFY(portMEMORY_BARRIER())) > 1u,
               "FreeRTOS BSP without portMEMORY_BARRIER (A53 freezes under load): "
               "patch and rebuild the platform, see tcl_scripts/vitis_patch_UltraZohm_freertos_bsp.tcl");

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
