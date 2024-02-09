#ifdef TEST

#include "unity.h"
#include "uz_approximate_flux_d.h"
#include "../../../src/uz/uz_approximate_flux_d/approximate_flux_d_ert_rtw/approximate_flux_d.h"
#include "../uz_global_configuration.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "test_assert_with_exception.h"

uz_3ph_dq_t i_Ampere = {0};
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

void test_uz_approximate_flux_d_step(void){
    uz_approximate_flux_d_t* test_instance = uz_approximate_flux_d_init(fitting_config);
    i_Ampere.d = 3.0f;
    i_Ampere.q = 3.0f;
    float result = uz_approximate_flux_d_step(test_instance,i_Ampere);
    TEST_ASSERT_FLOAT_WITHIN(0.020f,0.019f,result);
} 

#endif // TEST
