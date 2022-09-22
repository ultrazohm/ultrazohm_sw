#ifdef TEST

#include "unity.h"

#include "uz_resonant_controller.h"
#include "../../../src/uz/uz_ResonantController/Resonant_Controller_ert_rtw/Resonant_Controller.h"


// /workspaces/ultrazohm_sw/vitis/software/Baremetal/src/uz/uz_ResonantController/Resonant_Controller_ert_rtw/Resonant_Controller.h
// /workspaces/ultrazohm_sw/vitis/software/Baremetal/test/uz/uz_ResonantController/test_uz_resonant_controller.c

uz_resonantController test_R_controller;


void setUp(void)
{
		test_R_controller.input.T_sw = 0.0001;
		test_R_controller.input.VR = 160;
		test_R_controller.input.h = 2.0;
		test_R_controller.input.omega_el = 10;
		test_R_controller.input.lower_limit = -2.0;
		test_R_controller.input.upper_limit = 2.0;
		test_R_controller.input.Klim = 1.0;
		test_R_controller.input.in_ref = 3;
		test_R_controller.input.in_m = 3;
        test_R_controller.input.Reset = 0;
}


void test_uz_resonant_controller_Init(void)
{
    uz_resonantController_init(&test_R_controller);
}

void test_uz_resonant_controller_Step(void)
{
    uz_resonantController_step(&test_R_controller);
}

void test_uz_resonant_controller_Reset(void)
{
    uz_resonantController_reset(&test_R_controller);
    TEST_ASSERT_EQUAL_FLOAT(0.0f,test_R_controller.input.in_m);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, test_R_controller.input.in_ref);
}

void test_uz_resonant_controller_Step2(void)
{
    	test_R_controller.input.T_sw = 0.0001;
		test_R_controller.input.VR = 160;
		test_R_controller.input.h = 2.0;
		test_R_controller.input.omega_el = 10;
		test_R_controller.input.lower_limit = -2.0;
		test_R_controller.input.upper_limit = 2.0;
		test_R_controller.input.Klim = 1.0;
		test_R_controller.input.in_ref = 3;
		test_R_controller.input.in_m = 3;
        test_R_controller.input.Reset = 0;
    uz_resonantController_step(&test_R_controller);

    TEST_ASSERT_FLOAT_WITHIN (-1e-06, 1e-06, test_R_controller.output.out);
}

// Test multiple consecutive Steps with reset inbetween
void test_uz_resonant_controller_StepAndReset(void)
{
    	test_R_controller.input.T_sw = 0.0001;
		test_R_controller.input.VR = 160;
		test_R_controller.input.h = 2.0;
		test_R_controller.input.omega_el = 10;
		test_R_controller.input.lower_limit = -2.0;
		test_R_controller.input.upper_limit = 2.0;
		test_R_controller.input.Klim = 1.0;
		test_R_controller.input.in_ref = 3;
		test_R_controller.input.in_m = 2;
        test_R_controller.input.Reset = 0;
    uz_resonantController_step(&test_R_controller);

    TEST_ASSERT_FLOAT_WITHIN (0.01-1e-06, 0.01+ 1e-06, test_R_controller.output.out);

    uz_resonantController_step(&test_R_controller);

    TEST_ASSERT_FLOAT_WITHIN (0.02-1e-06, 0.02+ 1e-06, test_R_controller.output.out);

    uz_resonantController_step(&test_R_controller);

    TEST_ASSERT_FLOAT_WITHIN (0.03-1e-06, 0.03+ 1e-06, test_R_controller.output.out);

    uz_resonantController_reset(&test_R_controller);

    test_R_controller.input.in_ref = 3;
	test_R_controller.input.in_m = 2;

    TEST_ASSERT_FLOAT_WITHIN (-1e-06,  1e-06, test_R_controller.output.out);

    uz_resonantController_step(&test_R_controller);

    TEST_ASSERT_FLOAT_WITHIN (0.01-1e-06, 0.01+ 1e-06, test_R_controller.output.out);

    uz_resonantController_step(&test_R_controller);

    TEST_ASSERT_FLOAT_WITHIN (0.02-1e-06, 0.02+ 1e-06, test_R_controller.output.out);

    uz_resonantController_step(&test_R_controller);

    TEST_ASSERT_FLOAT_WITHIN (0.03-1e-06, 0.03+ 1e-06, test_R_controller.output.out);
}

#endif // TEST
