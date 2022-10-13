#ifdef TEST

#include "unity.h"

#include "uz_resonant_controller.h"
#include "../../../src/uz/uz_ResonantController/Resonant_Controller_ert_rtw/Resonant_Controller.h"
#include "../uz_global_configuration.h"

uz_resonantController* test_R_controller;




void setUp(void)
{
		test_R_controller = uz_resonantController_init();
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
}


void test_uz_resonant_controller_Reset(void)
{
	test_R_controller->input.in_m = 3.5f;
	uz_resonantController_step(test_R_controller);
    uz_resonantController_reset(test_R_controller);
    TEST_ASSERT_EQUAL_FLOAT(0.0f,test_R_controller->input.in_m);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, test_R_controller->input.in_ref);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, test_R_controller->output.out);
}

void test_uz_resonant_controller_Step(void)
{
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

#endif // TEST
