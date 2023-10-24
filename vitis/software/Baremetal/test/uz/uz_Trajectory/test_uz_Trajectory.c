#ifdef TEST

#include "unity.h"

#include "uz_Trajectory.h"
#include "test_assert_with_exception.h"

struct uz_Trajectory_config config = {0};
void setUp(void){
    config.selection_interpolation = Linear;
    config.selection_XAxis = ISR_Ticks;
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
	config.Sample_Amplitude_Y[19] = 0.0f;
	config.Sample_Duration_X[0]  = 5.0f;
	config.Sample_Duration_X[1]  = 5.0f;
	config.Sample_Duration_X[2]  = 5.0f;
	config.Sample_Duration_X[3]  = 5.0f;
	config.Sample_Duration_X[4]  = 5.0f;
	config.Sample_Duration_X[5]  = 5.0f;
	config.Sample_Duration_X[6]  = 5.0f;
	config.Sample_Duration_X[7]  = 5.0f;
	config.Sample_Duration_X[8]  = 5.0f;
	config.Sample_Duration_X[9]  = 5.0f;
	config.Sample_Duration_X[10] = 5.0f;
	config.Sample_Duration_X[11] = 5.0f;
	config.Sample_Duration_X[12] = 5.0f;
	config.Sample_Duration_X[13] = 5.0f;
	config.Sample_Duration_X[14] = 5.0f;
	config.Sample_Duration_X[15] = 5.0f;
	config.Sample_Duration_X[16] = 5.0f;
	config.Sample_Duration_X[17] = 5.0f;
	config.Sample_Duration_X[18] = 5.0f;
	config.Sample_Duration_X[19] = 5.0f;
	config.Repeats = 2U;
    config.Stepwidth_ISR = (1.0f / 10000.0f)*(1.0f);
}

void tearDown(void)
{
}

// Testing Init-routines and basic calls -----------------------------------------------------------------------------------
void test_uz_Trajectory_init_Pass(void){
    TEST_ASSERT_PASS_ASSERT(uz_Trajectory_init(config));
}

void test_uz_Trajectory_init_WrongDurations_Zero(void){
    config.Sample_Duration_X[5] = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
}

void test_uz_Trajectory_init_WrongDurations_Negative(void){
    config.Sample_Duration_X[5] = -1000.0f;
	TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
}

void test_uz_Trajectory_init_WrongDurations_TooSmall(void){
    config.Sample_Duration_X[5] = 0.0001f;
	config.selection_XAxis = MilliSeconds;
    TEST_ASSERT_FAIL_ASSERT(uz_Trajectory_init(config));
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

// Tests to generate some trajectories -------------------------------------------------------------------------------------
void test_uz_Trajectory_Step_Calls_without_start(void){
	config.selection_interpolation = Zero_Order_Hold;
	// Create Instance
    uz_Trajectory_t* MUT = uz_Trajectory_init(config);

	uint32_t samplecounter = 0U;
	float Traj_1_output	= 0.0f;

	// stepping through the trajectory
	for (uint32_t i = 0U; i<MAX_TRAJECTORY_SAMPLES; i++){	// Stepping trough all samples
		for (float i = 0.0f; i<5.0f; i++){	// Stepping trough the tikz
			Traj_1_output = uz_Trajectory_Step(MUT);
			TEST_ASSERT_EQUAL_FLOAT(0.0f,Traj_1_output);     // no output should be generated
		}
		samplecounter++;
	}
}

void test_uz_Trajectory_Step_Calls_ZeroOrderHold(void){
	config.selection_interpolation = Zero_Order_Hold;
	// Create Instance
    uz_Trajectory_t* MUT = uz_Trajectory_init(config);

	float reference_Values_Amplitude[MAX_TRAJECTORY_SAMPLES] = {0.0f,4.0f,6.0f,7.0f,7.5f,9.0f,20.0f,20.0f,-20.0f,20.0f,20.0f,0.0f,4.0f,6.0f,7.0f,7.5f,9.0f,20.0f,20.0f,0.0f};
	uint32_t samplecounter = 0U;
	float Traj_1_output	= 0.0f;

	// Start the trajectory module
	uz_Trajectory_Start(MUT);

	// stepping through the trajectory
	for (uint32_t i = 0U; i<MAX_TRAJECTORY_SAMPLES; i++){	// Stepping trough all samples
		for (float i = 0.0f; i<5.0f; i++){	// Stepping trough the tikz
			Traj_1_output = uz_Trajectory_Step(MUT);
			TEST_ASSERT_EQUAL_FLOAT(reference_Values_Amplitude[samplecounter],Traj_1_output);     
		}
		samplecounter++;
	}
}

void test_uz_Trajectory_Step_Calls_LinearInterpolation(void){
	config.selection_interpolation = Linear;
	// Create Instance
    uz_Trajectory_t* MUT = uz_Trajectory_init(config);

	float reference_Values_Amplitude[MAX_TRAJECTORY_SAMPLES] = {0.0f,4.0f,6.0f,7.0f,7.5f,9.0f,20.0f,20.0f,-20.0f,20.0f,20.0f,0.0f,4.0f,6.0f,7.0f,7.5f,9.0f,20.0f,20.0f,0.0f};
	float reference_Values_Duration[MAX_TRAJECTORY_SAMPLES] = {5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f};
	uint32_t samplecounter = 0U;
	uint32_t trajcounter = 0U;
	float Traj_1_output	= 0.0f;
	float Ref_Traj	= 0.0f;

	float Interpolation_Coefficients[4][MAX_TRAJECTORY_SAMPLES-1];
	float Sum_Timeaxis = 0.0f;

	for(uint32_t i = 0; i < (MAX_TRAJECTORY_SAMPLES-1);i++){
		Sum_Timeaxis = Sum_Timeaxis + reference_Values_Duration[i];
    	Interpolation_Coefficients[3][i] = 0.0f;	// not needed
    	Interpolation_Coefficients[2][i] = 0.0f;	// not needed
    	Interpolation_Coefficients[1][i] = (reference_Values_Amplitude[i+1] - reference_Values_Amplitude[i])/(reference_Values_Duration[i]);
    	Interpolation_Coefficients[0][i] = reference_Values_Amplitude[i+1] - Interpolation_Coefficients[1][i]*Sum_Timeaxis;	
    }

	// Start the trajectory module
	uz_Trajectory_Start(MUT);

	// stepping through the trajectory
	for (uint32_t i = 0U; i<MAX_TRAJECTORY_SAMPLES; i++){		// Stepping trough all linear equations
		for (float j = 0.0f; j<5.0f; j++){						// Stepping trough the tikz			
			Traj_1_output = uz_Trajectory_Step(MUT);
			Ref_Traj = (Interpolation_Coefficients[1][samplecounter] * (float)trajcounter + reference_Values_Amplitude[samplecounter]);
			TEST_ASSERT_EQUAL_FLOAT(Ref_Traj,Traj_1_output); 
			trajcounter++;    
		}
		samplecounter++;
		trajcounter = 0U;
	}
}

void test_uz_Trajectory_StartStopStart_with_Hold(void){
	// Create Instance
    uz_Trajectory_t* MUT = uz_Trajectory_init(config);

	float reference_Values_Amplitude[MAX_TRAJECTORY_SAMPLES] = {0.0f,4.0f,6.0f,7.0f,7.5f,9.0f,20.0f,20.0f,-20.0f,20.0f,20.0f,0.0f,4.0f,6.0f,7.0f,7.5f,9.0f,20.0f,20.0f,0.0f};
	float reference_Values_Duration[MAX_TRAJECTORY_SAMPLES] = {5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f};
	float Traj_1_output	= 0.0f;
	float Ref_Traj	= 0.0f;

	float Interpolation_Coefficients[4][MAX_TRAJECTORY_SAMPLES-1];
	float Sum_Timeaxis = 0.0f;

	for(uint32_t i = 0; i < (MAX_TRAJECTORY_SAMPLES-1);i++){
		Sum_Timeaxis = Sum_Timeaxis + reference_Values_Duration[i];
    	Interpolation_Coefficients[3][i] = 0.0f;	// not needed
    	Interpolation_Coefficients[2][i] = 0.0f;	// not needed
    	Interpolation_Coefficients[1][i] = (reference_Values_Amplitude[i+1] - reference_Values_Amplitude[i])/(reference_Values_Duration[i]);
    	Interpolation_Coefficients[0][i] = reference_Values_Amplitude[i+1] - Interpolation_Coefficients[1][i]*Sum_Timeaxis;	
    }

	// Start the trajectory module
	uz_Trajectory_Start(MUT);

	// stepping through the trajectory	
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);

	// Stop the trajectory module
	uz_Trajectory_Stop(MUT);

	// Compare
	Ref_Traj = (Interpolation_Coefficients[1][0] * (float)2.0f + reference_Values_Amplitude[0]);
	TEST_ASSERT_EQUAL_FLOAT(Ref_Traj,Traj_1_output); 

	// stepping through the trajectory	
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);

	// Compare, Output must nut change! ATTENTION! increase the calculation counter by 1 since one step will be calculated after stop. this is due to the internal counter structure.
	Ref_Traj = (Interpolation_Coefficients[1][0] * (float)(2.0f+1.0f) + reference_Values_Amplitude[0]);
	TEST_ASSERT_EQUAL_FLOAT(Ref_Traj,Traj_1_output); 

	// Start the trajectory module
	uz_Trajectory_Start(MUT);

	// stepping through the trajectory	
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);

	// Compare
	Ref_Traj = (Interpolation_Coefficients[1][0] * (float)5.0f + reference_Values_Amplitude[0]);
	TEST_ASSERT_EQUAL_FLOAT(Ref_Traj,Traj_1_output); 

}

void test_uz_Trajectory_StartStopStart_with_ForceToZero(void){
	// Create Instance
	config.StopStyle = ForceToZero;
    uz_Trajectory_t* MUT = uz_Trajectory_init(config);

	float reference_Values_Amplitude[MAX_TRAJECTORY_SAMPLES] = {0.0f,4.0f,6.0f,7.0f,7.5f,9.0f,20.0f,20.0f,-20.0f,20.0f,20.0f,0.0f,4.0f,6.0f,7.0f,7.5f,9.0f,20.0f,20.0f,0.0f};
	float reference_Values_Duration[MAX_TRAJECTORY_SAMPLES] = {5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f};
	float Traj_1_output	= 0.0f;
	float Ref_Traj	= 0.0f;

	float Interpolation_Coefficients[4][MAX_TRAJECTORY_SAMPLES-1];
	float Sum_Timeaxis = 0.0f;

	for(uint32_t i = 0; i < (MAX_TRAJECTORY_SAMPLES-1);i++){
		Sum_Timeaxis = Sum_Timeaxis + reference_Values_Duration[i];
    	Interpolation_Coefficients[3][i] = 0.0f;	// not needed
    	Interpolation_Coefficients[2][i] = 0.0f;	// not needed
    	Interpolation_Coefficients[1][i] = (reference_Values_Amplitude[i+1] - reference_Values_Amplitude[i])/(reference_Values_Duration[i]);
    	Interpolation_Coefficients[0][i] = reference_Values_Amplitude[i+1] - Interpolation_Coefficients[1][i]*Sum_Timeaxis;	
    }

	// Start the trajectory module
	uz_Trajectory_Start(MUT);

	// stepping through the trajectory	
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);

	// Stop the trajectory module
	uz_Trajectory_Stop(MUT);

	// Compare
	Ref_Traj = (Interpolation_Coefficients[1][0] * (float)2.0f + reference_Values_Amplitude[0]);
	TEST_ASSERT_EQUAL_FLOAT(Ref_Traj,Traj_1_output); 

	// stepping through the trajectory	
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);

	// Compare, Output must be zero! ATTENTION! increase the calculation counter by 1 since one step will be calculated after stop. this is due to the internal counter structure.
	TEST_ASSERT_EQUAL_FLOAT(0.0f,Traj_1_output); 

	// Start the trajectory module
	uz_Trajectory_Start(MUT);

	// stepping through the trajectory	
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);

	// Compare
	Ref_Traj = (Interpolation_Coefficients[1][0] * (float)5.0f + reference_Values_Amplitude[0]);
	TEST_ASSERT_EQUAL_FLOAT(Ref_Traj,Traj_1_output);
}

void test_uz_Trajectory_Reset_Trajectory(void){
	config.selection_interpolation = Linear;
	// Create Instance
    uz_Trajectory_t* MUT = uz_Trajectory_init(config);

	float reference_Values_Amplitude[MAX_TRAJECTORY_SAMPLES] = {0.0f,4.0f,6.0f,7.0f,7.5f,9.0f,20.0f,20.0f,-20.0f,20.0f,20.0f,0.0f,4.0f,6.0f,7.0f,7.5f,9.0f,20.0f,20.0f,0.0f};
	float reference_Values_Duration[MAX_TRAJECTORY_SAMPLES] = {5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,5.0f};
	uint32_t samplecounter = 0U;
	uint32_t trajcounter = 0U;
	float Traj_1_output	= 0.0f;
	float Ref_Traj	= 0.0f;

	float Interpolation_Coefficients[4][MAX_TRAJECTORY_SAMPLES-1];
	float Sum_Timeaxis = 0.0f;

	for(uint32_t i = 0; i < (MAX_TRAJECTORY_SAMPLES-1);i++){
		Sum_Timeaxis = Sum_Timeaxis + reference_Values_Duration[i];
    	Interpolation_Coefficients[3][i] = 0.0f;	// not needed
    	Interpolation_Coefficients[2][i] = 0.0f;	// not needed
    	Interpolation_Coefficients[1][i] = (reference_Values_Amplitude[i+1] - reference_Values_Amplitude[i])/(reference_Values_Duration[i]);
    	Interpolation_Coefficients[0][i] = reference_Values_Amplitude[i+1] - Interpolation_Coefficients[1][i]*Sum_Timeaxis;	
    }

	// Start the trajectory module
	uz_Trajectory_Start(MUT);

	// stepping through the trajectory
	for (uint32_t k = 0U; k<2U; k++){								// Two repeats
		for (uint32_t i = 0U; i<MAX_TRAJECTORY_SAMPLES; i++){		// Stepping trough all linear equations
			for (float j = 0.0f; j<5.0f; j++){						// Stepping trough the tikz			
				Traj_1_output = uz_Trajectory_Step(MUT);
				Ref_Traj = (Interpolation_Coefficients[1][samplecounter] * (float)trajcounter + reference_Values_Amplitude[samplecounter]);
				TEST_ASSERT_EQUAL_FLOAT(Ref_Traj,Traj_1_output); 
				trajcounter++;    
			}
			samplecounter++;
			trajcounter = 0U;
		}
		Traj_1_output = uz_Trajectory_Step(MUT);		// Workaround to get the loops aligned to the checks
		samplecounter=0U;
	}

	// stepping through the trajectory with the finished-flag active. No trajectory must be calculated.
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);
	Traj_1_output = uz_Trajectory_Step(MUT);

	TEST_ASSERT_EQUAL_FLOAT(0.0f,Traj_1_output); 

	// Reset the trajectory module
	uz_Trajectory_Reset(MUT);
	
	// Start the trajectory module after the Reset
	uz_Trajectory_Start(MUT);

	// stepping through the trajectory
	for (uint32_t k = 0U; k<2U; k++){								// Two repeats
		for (uint32_t i = 0U; i<MAX_TRAJECTORY_SAMPLES; i++){		// Stepping trough all linear equations
			for (float j = 0.0f; j<5.0f; j++){						// Stepping trough the tikz			
				Traj_1_output = uz_Trajectory_Step(MUT);
				Ref_Traj = (Interpolation_Coefficients[1][samplecounter] * (float)trajcounter + reference_Values_Amplitude[samplecounter]);
				TEST_ASSERT_EQUAL_FLOAT(Ref_Traj,Traj_1_output); 
				trajcounter++;    
			}
			samplecounter++;
			trajcounter = 0U;
		}
		Traj_1_output = uz_Trajectory_Step(MUT);		// Workaround to get the loops aligned to the checks
		samplecounter=0U;
	}
}

#endif // TEST
