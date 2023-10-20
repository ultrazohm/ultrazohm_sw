#ifdef TEST

#include "unity.h"

#include "uz_Trajectory.h"
#include "test_assert_with_exception.h"

struct uz_Trajectory_config config = {0};

void setUp(void){
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

void test_uz_Trajectory_init_WrongDurations(void){
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
}

void test_uz_Trajectory_init_WrongRepeatAmount(void){
    config.Repeats = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
}

void test_uz_Trajectory_init_WrongInterpolationType(void){
    config.selection_interpolation = 20;
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
}
void test_uz_Trajectory_init_WrongXAxis(void){
    config.selection_XAxis = 20;
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
}
void test_uz_Trajectory_init_WrongStopStyle(void){
    config.StopStyle = 20;
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
}
void test_uz_Trajectory_init_WrongRepeatType(void){
    config.RepeatStyle = 20;
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
}

void test_uz_Trajectory_init_Pass(void){
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
    
    TEST_ASSERT_PASS_ASSERT(uz_Trajectory_init(config));
}

void test_uz_Trajectory_Start_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_Start(NULL));
}

void test_uz_Trajectory_Stop_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_Stop(NULL));
}

void test_uz_Trajectory_Reset_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_Reset(NULL));
}

void test_uz_Trajectory_Step_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_Step(NULL));
}

void test_uz_Trajectory_Step_Call(void){
    //uz_Trajectory_t* MUT = uz_Trajectory_init(config);
}


#endif // TEST
