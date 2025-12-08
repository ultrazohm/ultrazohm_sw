#ifdef TEST

#include "unity.h"
#include "../uz_buck_control/uz_buck_control.h"
#include "test_assert_with_exception.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_signals/uz_signals.h"
#include <math.h>
#include <stdbool.h>

struct buck_control_config config = {0};
struct buck_control_ref_val ref_val = {0};
struct buck_control_act_val act_val = {0};  

void setUp(void)
{
    config.max_duty_cycle = 1.0f;
    config.min_duty_cycle = 0.0f;
    config.u_BUS_V_nominal = 48.0f;
    config.i_dcdc_upper_lim_A = 50.0f;
    config.i_dcdc_lower_lim_A = 0.0f;
    config.control_mode = i_HS_control;
    ref_val.i_HS_A_ref = 10.0f; 
}

void test_uz_buck_control_init(void){
    uz_buck_control_t* instance = uz_buck_control_init(config);
    TEST_ASSERT_NOT_NULL(instance);
}

void test_uz_buck_control_sample(void){
    uz_buck_control_t* instance = uz_buck_control_init(config);
    float duty_cycle = 0.0f;
    duty_cycle = uz_buck_control_sample(instance, ref_val, act_val);
    duty_cycle = uz_buck_control_sample(instance, ref_val, act_val);
    duty_cycle = uz_buck_control_sample(instance, ref_val, act_val);
    TEST_ASSERT(duty_cycle==1.0f);
}


#endif 