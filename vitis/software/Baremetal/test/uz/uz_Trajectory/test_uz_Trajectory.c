/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2023 Robert Zipprich
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/

#ifdef TEST

#include "unity.h"

#include "uz_Trajectory.h"
#include "../../../src/uz/uz_Trajectory/uz_Trajectory.h"
#include "../uz_global_configuration.h"
#include "test_assert_with_exception.h"

#include <stdio.h>

struct uz_Trajectory_config config = {0};
void Setup (void){
	config.selection_interpolation = Linear;
    config.selection_XAxis = Seconds;
    config.StopStyle = HoldLast;
	config.RepeatStyle = Repeat_Times;
    config.Number_Sample_Points = MAX_TRAJECTORY_SAMPLES;
    config.Sample_Amplitude_Y[0]  = 0.0f;
	config.Sample_Amplitude_Y[1]  = 4.0f;
	config.Sample_Amplitude_Y[2]  = 6.0f;
	config.Sample_Amplitude_Y[3]  = 7.0f;
	config.Sample_Amplitude_Y[4]  = 7.5f;
	config.Sample_Amplitude_Y[5]  = 9.0f;
	config.Sample_Amplitude_Y[6]  = 20.0f;
	config.Sample_Amplitude_Y[7]  = 20.0f;
	config.Sample_Amplitude_Y[8]  = -20.0f;
	config.Sample_Amplitude_Y[9]  = 20.0f;
	config.Sample_Amplitude_Y[10] = 20.0f;
	config.Sample_Amplitude_Y[11] = 0.0f;
	config.Sample_Amplitude_Y[12] = 4.0f;
	config.Sample_Amplitude_Y[13] = 6.0f;
	config.Sample_Amplitude_Y[14] = 7.0f;
	config.Sample_Amplitude_Y[15] = 7.5f;
	config.Sample_Amplitude_Y[16] = 9.0f;
	config.Sample_Amplitude_Y[17] = 20.0f;
	config.Sample_Amplitude_Y[18] = 20.0f;
	config.Sample_Amplitude_Y[19] = -20.0f;
	config.Sample_Duration_X[0]  = 1000.0f;
	config.Sample_Duration_X[1]  = 1000.0f;
	config.Sample_Duration_X[2]  = 1000.0f;
	config.Sample_Duration_X[3]  = 1000.0f;
	config.Sample_Duration_X[4]  = 1000.0f;
	config.Sample_Duration_X[5]  = 1000.0f;
	config.Sample_Duration_X[6]  = 1000.0f;
	config.Sample_Duration_X[7]  = 1000.0f;
	config.Sample_Duration_X[8]  = 1000.0f;
	config.Sample_Duration_X[9]  = 1000.0f;
	config.Sample_Duration_X[10] = 1000.0f;
	config.Sample_Duration_X[11] = 1000.0f;
	config.Sample_Duration_X[12] = 1000.0f;
	config.Sample_Duration_X[13] = 1000.0f;
	config.Sample_Duration_X[14] = 1000.0f;
	config.Sample_Duration_X[15] = 1000.0f;
	config.Sample_Duration_X[16] = 1000.0f;
	config.Sample_Duration_X[17] = 1000.0f;
	config.Sample_Duration_X[18] = 1000.0f;
	config.Sample_Duration_X[19] = 1000.0f;
	config.Repeats = 2U;
    config.Stepwidth_ISR = (1.0f / 10000.0f)*(1.0f);
}

void tearDown(void)
{
}

void test_uz_Trajectory_init(void){
	TEST_ASSERT_PASS_ASSERT(uz_Trajectory_init(config));

	// tests asserts in init-function - first zero or negative durations
    config.Sample_Duration_X[5] = -1000.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
	config.Sample_Duration_X[5] = 0.0f;
	TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
    config.Sample_Duration_X[5] = 1000.0f;

	// tests asserts in init-function - second to short durations
    config.Sample_Duration_X[5] = 0.0001f;
	config.selection_XAxis = MilliSeconds;
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
	config.Sample_Duration_X[5] = 1000.0f;

	// tests asserts in init-function - wrong Repeat amount
    config.Repeats = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
	config.Repeats = 2U;

	// tests asserts in init-function - wrong interpolation type
    config.selection_interpolation = 20;
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
	config.selection_interpolation = Linear;

	// tests asserts in init-function - wrong X-Axis type
    config.selection_XAxis = 20;
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
	config.selection_XAxis = MilliSeconds;

	// tests asserts in init-function - wrong StopStyle type
    config.StopStyle = 20;
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
	config.StopStyle = HoldLast;

	// tests asserts in init-function - wrong Repeat type
    config.RepeatStyle = 20;
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
	config.RepeatStyle = Repeat_Times;

}

//void test_uz_Trajectory_step(void){
		//uz_Trajectory_t *test_Trajectory_Generator = uz_Trajectory_init(config);
	//float output = uz_Trajectory_Step(test_Trajectory_Generator);
//}


#endif // TEST