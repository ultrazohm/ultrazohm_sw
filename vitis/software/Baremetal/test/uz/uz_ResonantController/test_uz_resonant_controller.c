#ifdef TEST

#include "unity.h"

#include "uz_resonant_controller.h"
#include "../../../src/uz/uz_ResonantController/Resonant_Controller_ert_rtw/Resonant_Controller.h"
#include "../uz_global_configuration.h"

#include <stdio.h>



struct uz_resonantController_config config = {0};
void setUp(void)
{
	config.sampling_time = 0.0001f;			/**< SamplingTime of the PI-Controller in seconds. Must be greater than 0.0f */
	config.gain = 160.0f;					/**< Gain of the resonant Controller*/
	config.harmonic_order = 2.0f;			/**< Order of harmonic to be controlled*/
	config.fundamental_frequency = 10.0f;	/**< Fundamental Frequency in rad/s */
	config.lower_limit = -2.0f;				/**< Lower limit for the output limitation */
	config.upper_limit = 2.0f;				/**< Upper limit for the output limitation. Must be greater than lower limit */
	config.antiwindup_gain = 1.0f;			/**< Gain of anti-windup feedback*/
	config.in_reference_value = 3.0f;		/**< Input reference value*/
	config.in_measured_value = 3.0f;		/**< Input measured value*/


}



void test_uz_resonant_controller_Reset(void)
{
	uz_resonantController_t* test_R_controller;
	test_R_controller = uz_resonantController_init(config);

	float in_ref = 3.0f;
	float in_m = 3.5f;
	float omega_el = 10.0f;
	float output = 0.0f;
	

	output = uz_resonantController_step(test_R_controller, in_ref, in_m, omega_el);
	TEST_ASSERT_EQUAL_FLOAT(-0.008f,output);
    uz_resonantController_reset(test_R_controller);
	output = uz_resonantController_get_output(test_R_controller);
    TEST_ASSERT_EQUAL_FLOAT(0.0f,output);
}






// Test multiple consecutive Steps with reset inbetween
void test_uz_resonant_controller_StepAndReset(void)
{
	uz_resonantController_t* test_R_controller;
	test_R_controller = uz_resonantController_init(config);

	float in_ref = 3.0f;
	float in_m = 2.0f;
	float omega_el = 10.0f;
	float output = 0.0f;

    output = uz_resonantController_step(test_R_controller, in_ref, in_m, omega_el);

    TEST_ASSERT_FLOAT_WITHIN (0.01f-1e-06f, 0.01f+ 1e-06f, output);

    output = uz_resonantController_step(test_R_controller, in_ref, in_m, omega_el);

    TEST_ASSERT_FLOAT_WITHIN (0.02f-1e-06f, 0.02f+ 1e-06f, output);

    output = uz_resonantController_step(test_R_controller, in_ref, in_m, omega_el);

    TEST_ASSERT_FLOAT_WITHIN (0.03f-1e-06f, 0.03f+ 1e-06f, output);

    uz_resonantController_reset(test_R_controller);

	output = uz_resonantController_get_output(test_R_controller);
	in_ref = 3.0f;
	in_m = 2.0f;

    TEST_ASSERT_FLOAT_WITHIN (-1e-06f,  1e-06f, output);

    output = uz_resonantController_step(test_R_controller, in_ref, in_m, omega_el);

    TEST_ASSERT_FLOAT_WITHIN (0.01f-1e-06f, 0.01f+ 1e-06f, output);

    output = uz_resonantController_step(test_R_controller, in_ref, in_m, omega_el);

    TEST_ASSERT_FLOAT_WITHIN (0.02f-1e-06f, 0.02f+ 1e-06f, output);

    output = uz_resonantController_step(test_R_controller, in_ref, in_m, omega_el);

    TEST_ASSERT_FLOAT_WITHIN (0.03f-1e-06f, 0.03f+ 1e-06f, output);
}




void test_uz_resonantController_set_config(void)
{
	
	uz_resonantController_t* test_R_controller_config;
	test_R_controller_config = uz_resonantController_init(config);

	config.harmonic_order = 7.0f;

	uz_resonantController_set_config(test_R_controller_config, config);

}


#endif // TEST
