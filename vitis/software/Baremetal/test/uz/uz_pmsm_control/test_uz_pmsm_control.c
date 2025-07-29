#ifdef TEST

#include "unity.h"

#include "uz_pmsm_control.h"
#include "uz_HAL.h"
#include "uz_pmsm_control.h"
#include "uz_math_constants.h"
#include "uz_signals/uz_signals.h"
#include "uz_piController/uz_piController.h"
#include "uz_Transformation/uz_Transformation.h"
#include "uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "uz_SpeedControl/uz_speedcontrol.h"
#include "uz_CurrentControl/uz_CurrentControl.h"
#include "uz_setpoint/uz_setpoint.h"
#include "uz_controller_setpoint_filter/uz_controller_setpoint_filter.h"

#include "test_assert_with_exception.h"
#include "uz_CurrentControl.h"
#include "uz_piController/uz_piController.h"
#include "uz_signals/uz_signals.h"
#include "uz_linear_decoupling.h"
#include "uz_static_nonlinear_decoupling.h"
#include "uz_Transformation/uz_Transformation.h"
#include "uz_space_vector_limitation.h"
#include <math.h>

TEST_FILE("uz_signals_iir_filter.c")
TEST_FILE("uz_newton_raphson.c")

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_pmsm_control_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement uz_pmsm_control");
}

#endif // TEST
