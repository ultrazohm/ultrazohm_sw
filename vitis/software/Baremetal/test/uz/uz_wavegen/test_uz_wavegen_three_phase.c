#ifdef TEST

#include "unity.h"
#include "uz_wavegen.h"
#include <math.h>
#include "mock_uz_SystemTime.h"
#include "test_assert_with_exception.h"

void setUp(void)
{
}

void tearDown(void)
{
}

// struct uz_wavegen_three_phase_config config_three = {
//         .amplitude = 2.0f,
//         .frequency_Hz = 1.0f,
//         .offset = 1.0f
// };

// void test_uz_wavegen_three_phase_init_max_instances(void){    
//     struct uz_wavegen_three_phase_config config2 = config_three;
//     struct uz_wavegen_three_phase_config config3 = config_three;
//     TEST_ASSERT_PASS_ASSERT(uz_wavegen_three_phase_init(config_three));
//     TEST_ASSERT_PASS_ASSERT(uz_wavegen_three_phase_init(config2));
//     TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_init(config3));
// }

// void test_uz_wavegen_three_phase_init_zero_amplitude(void){ 
//     config_three.amplitude = 0.0f;
//     TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_init(config_three));
//     config_three.amplitude = 1.0f;
// }

// void test_uz_wavegen_three_phase_init_negative_start_frequency(void){ 
//     config_three.frequency_Hz = -10.0f;
//     TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_init(config_three));
// }

// void test_uz_wavegen_three_phase_init_zero_start_frequency(void){ 
//     config_three.frequency_Hz = 0.0f;
//     TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_init(config_three));
//     config_three.frequency_Hz = 5.0f;
// }

// void test_uz_wavegen_three_phase_NULL(void){
//     TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase(NULL));
// }

// void test_uz_wavegen_three_phase_get_phaseU_NULL(void){
//     TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_get_phaseU(NULL));
// }

// void test_uz_wavegen_three_phase_get_phaseV_NULL(void){
//     TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_get_phaseV(NULL));
// }

// void test_uz_wavegen_three_phase_get_phaseW_NULL(void){
//     TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_get_phaseW(NULL));
// }

#endif