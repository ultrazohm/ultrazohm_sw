#ifdef TEST

#include "unity.h"

#include "uz_resonant_controller.h"
#include "../../../src/uz/uz_ResonantController/Resonant_Controller_ert_rtw/Resonant_Controller.h"
#include "../uz_global_configuration.h"

#include <stdio.h>



struct uz_resonantController_config config = {0};
void setUp(void)
{
	config.T_sw = 0.0001f;	/**< SamplingTime of the PI-Controller in seconds. Must be greater than 0.0f */
	config.VR = 160.0f;		/**< Gain of the resonant Controller*/
	config.h = 2.0f;			/**< Order of harmonic to be controlled*/
	config.omega_el = 10.0f;	/**< Fundamental Frequency in rad/s */
	config.lower_limit = -2.0f;	/**< Lower limit for the output limitation */
	config.upper_limit = 2.0f;	/**< Upper limit for the output limitation. Must be greater than lower limit */
	config.Klim = 1.0f;			/**< Gain of anti-windup feedback*/
	config.in_ref = 3.0f;		/**< Input reference value*/
	config.in_m = 3.0f;			/**< Input measured value*/
	config.Reset = 0.0f;		/**< Reset input*/


}



void test_uz_resonant_controller_Reset(void)
{
	uz_resonantController_t* test_R_controller;
	test_R_controller = uz_resonantController_init(config);

	test_R_controller->input.in_m = 3.5f;
	uz_resonantController_step(test_R_controller);
    uz_resonantController_reset(test_R_controller);
    TEST_ASSERT_EQUAL_FLOAT(0.0f,test_R_controller->input.in_m);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, test_R_controller->input.in_ref);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, test_R_controller->output.out);
}

void test_uz_resonant_controller_Step(void)
{
	uz_resonantController_t* test_R_controller;
	test_R_controller = uz_resonantController_init(config);

    	test_R_controller->input.T_sw = 0.0001f;
		test_R_controller->input.VR = 160.0f;
		test_R_controller->input.h = 2.0f;
		test_R_controller->input.omega_el = 10.0f;
		test_R_controller->input.lower_limit = -2.0f;
		test_R_controller->input.upper_limit = 2.0f;
		test_R_controller->input.Klim = 1.0f;
		test_R_controller->input.in_ref = 3.0f;
		test_R_controller->input.in_m = 3.0f;
        test_R_controller->input.Reset = 0.0f;
    uz_resonantController_step(test_R_controller);

    TEST_ASSERT_FLOAT_WITHIN (-1e-06, 1e-06, test_R_controller->output.out);
}





// Test multiple consecutive Steps with reset inbetween
void test_uz_resonant_controller_StepAndReset(void)
{
	uz_resonantController_t* test_R_controller;
	test_R_controller = uz_resonantController_init(config);

    	test_R_controller->input.T_sw = 0.0001f;
		test_R_controller->input.VR = 160.0f;
		test_R_controller->input.h = 2.0f;
		test_R_controller->input.omega_el = 10.0f;
		test_R_controller->input.lower_limit = -2.0f;
		test_R_controller->input.upper_limit = 2.0f;
		test_R_controller->input.Klim = 1.0f;
		test_R_controller->input.in_ref = 3.0f;
		test_R_controller->input.in_m = 2.0f;
        test_R_controller->input.Reset = 0.0f;
    uz_resonantController_step(test_R_controller);

    TEST_ASSERT_FLOAT_WITHIN (0.01f-1e-06f, 0.01f+ 1e-06f, test_R_controller->output.out);

    uz_resonantController_step(test_R_controller);

    TEST_ASSERT_FLOAT_WITHIN (0.02f-1e-06f, 0.02f+ 1e-06f, test_R_controller->output.out);

    uz_resonantController_step(test_R_controller);

    TEST_ASSERT_FLOAT_WITHIN (0.03f-1e-06f, 0.03f+ 1e-06f, test_R_controller->output.out);

    uz_resonantController_reset(test_R_controller);

    test_R_controller->input.in_ref = 3.0f;
	test_R_controller->input.in_m = 2.0f;

    TEST_ASSERT_FLOAT_WITHIN (-1e-06f,  1e-06f, test_R_controller->output.out);

    uz_resonantController_step(test_R_controller);

    TEST_ASSERT_FLOAT_WITHIN (0.01f-1e-06f, 0.01f+ 1e-06f, test_R_controller->output.out);

    uz_resonantController_step(test_R_controller);

    TEST_ASSERT_FLOAT_WITHIN (0.02f-1e-06f, 0.02f+ 1e-06f, test_R_controller->output.out);

    uz_resonantController_step(test_R_controller);

    TEST_ASSERT_FLOAT_WITHIN (0.03f-1e-06f, 0.03f+ 1e-06f, test_R_controller->output.out);
}


void test_uz_resonant_controller_set_input(void){
	
	uz_resonantController_t* test_R_controller_set_input;
	test_R_controller_set_input = uz_resonantController_init(config);

	float a = 0.0f;
	float b = 3.0f;
	float c = 2.0f;
	
	uz_resonantController_set_input(test_R_controller_set_input, a, b, c);

	TEST_ASSERT_EQUAL_FLOAT(test_R_controller_set_input->input.in_ref, a);
	TEST_ASSERT_EQUAL_FLOAT(test_R_controller_set_input->input.in_m, b);
	TEST_ASSERT_EQUAL_FLOAT(test_R_controller_set_input->input.omega_el, c);
	
	
}


void test_uz_resonantController_get_output(void)
{
	
	uz_resonantController_t* test_R_controller_get_output;
	test_R_controller_get_output = uz_resonantController_init(config);

    uz_resonantController_step(test_R_controller_get_output);

	float output_get;
	float output_in;
	output_get = uz_resonantController_get_output(test_R_controller_get_output);
	output_in = test_R_controller_get_output->output.out;

	TEST_ASSERT_EQUAL_FLOAT(output_get,output_in);

	
}

void test_uz_resonantController_set_config(void)
{
	
	uz_resonantController_t* test_R_controller_config;
	test_R_controller_config = uz_resonantController_init(config);

	config.h = 7.0f;

	uz_resonantController_set_config(test_R_controller_config, config);

}


#endif // TEST
