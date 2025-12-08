#ifdef TEST

#include "unity.h"
#include "../uz_buck_control/uz_buck_control.h"
#include "test_assert_with_exception.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_signals/uz_signals.h"
#include <math.h>
#include <stdbool.h>

struct buck_control_config config = {0};


void setUp(void)
{
    config.max_duty_cycle = 1.0f;
    config.min_duty_cycle = 0.0f;
    config.u_BUS_V_nominal = 48.0f;
    config.i_dcdc_upper_lim_A = 10.0f;
    config.i_dcdc_lower_lim_A = -10.0f;
    config.i_HS_control = false;
    config.u_UC_control = false;
    config.i_UC_control = true;
}

void test_uz_buck_control_init(void){
    uz_buck_control_t* instance = uz_buck_control_init(config);
    TEST_ASSERT_NOT_NULL(instance);
}

void test_uz_buck_control_sample(void){
    uz_buck_control_t* instance = uz_buck_control_init(config);
    float duty_cycle = 0.0f;
    duty_cycle = uz_buck_control_sample(instance, i_UC_control);
    TEST_ASSERT(duty_cycle==0.0f);
}


#endif 