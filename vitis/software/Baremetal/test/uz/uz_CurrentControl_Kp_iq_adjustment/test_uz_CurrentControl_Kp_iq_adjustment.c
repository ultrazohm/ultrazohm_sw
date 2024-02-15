#ifdef TEST

#include "unity.h"
#include "uz_CurrentControl_Kp_iq_adjustment.h"
#include "../../../src/uz/uz_CurrentControl_Kp_iq_adjustment/CurrentControl_Kp_iq_adjustment_ert_rtw/CurrentControl_Kp_iq_adjustment.h"
#include "../uz_global_configuration.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "test_assert_with_exception.h"

uz_3ph_dq_t i_reference_Ampere = {0};
uz_3ph_dq_t i_actual_Ampere = {0};
void setUp(void)
{
}


void test_uz_CurrentControl_Kp_iq_adjustment_step(void){
    float dead_time_reciprocal = 10.0e3f; //for Controller Frequency of 20kHz and factor 2
    float psiq_ref = 0.002f;
    float psiq_actual = 0.0f;
    uz_CurrentControl_Kp_iq_adjustment_t* test_instance = uz_CurrentControl_Kp_iq_adjustment_init(dead_time_reciprocal);
    i_reference_Ampere.q = 1.0f;
    i_actual_Ampere.q = 0.0f;
    float result = uz_CurrentControl_Kp_iq_adjustment_step(test_instance,i_reference_Ampere, i_actual_Ampere, psiq_ref, psiq_actual);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f,10.0f,result);
} 

#endif // TEST
