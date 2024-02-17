#ifdef TEST

#include "unity.h"
#include "uz_approximate_flux_q.h"
#include "../../../src/uz/uz_approximate_flux_q/approximate_flux_q_ert_rtw/approximate_flux_q.h"
#include "../uz_global_configuration.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "test_assert_with_exception.h"

uz_3ph_dq_t i_reference_Ampere = {0};
uz_3ph_dq_t i_actual_Ampere = {0};
uz_PMSM_flux_fitting_parameter_config_t fitting_config = {0};
void setUp(void)
{
	fitting_config.ad1_parameter = 0.030483840951002f;
	fitting_config.ad2_parameter = 0.040244227373267f;
	fitting_config.ad3_parameter = -16.481195185733903f;
	fitting_config.ad4_parameter = 1.296438633344970f;
	fitting_config.ad5_parameter = 6.183163374457993e-04f;
	fitting_config.ad6_parameter = -12.275586044862504f;
	fitting_config.aq1_parameter = 0.004816670542863f;
	fitting_config.aq2_parameter = 0.171595254784258f;
	fitting_config.aq3_parameter = 9.262938633610718e-04f;
	fitting_config.aq4_parameter = 0.005001870975338f;
	fitting_config.aq5_parameter = 0.170521235710151f;
	fitting_config.aq6_parameter = 9.186084507499523e-04f;
	fitting_config.F1G1_parameter = -0.001356794026337f;
	fitting_config.F2G2_parameter = 0.078813850391713f;
}

void test_uz_approximate_flux_q_step(void){
    uz_approximate_flux_q_t* test_instance = uz_approximate_flux_q_init(fitting_config);
    i_actual_Ampere.d = -3.0f;
    i_actual_Ampere.q = 3.0f;
    float result = uz_approximate_flux_q_step(test_instance,i_actual_Ampere);
    TEST_ASSERT_FLOAT_WITHIN(1e-02f,0.0050f,result);
} 

void test_uz_approximate_flux_q_set_step(void){
    uz_approximate_flux_q_t* test_instance = uz_approximate_flux_q_init(fitting_config);
    i_actual_Ampere.d = -3.0f;
    i_reference_Ampere.q = 3.0f;
    float result = uz_approximate_flux_q_set_step(test_instance,i_reference_Ampere,i_actual_Ampere);
    TEST_ASSERT_FLOAT_WITHIN(1e-02f,0.0050f,result);
} 

#endif // TEST
