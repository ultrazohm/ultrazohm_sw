#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_inverter_adapter.h"
#include "uz_inverter_adapter_hwAddresses.h"
#include "mock_uz_inverter_adapter_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include <stdbool.h>
#include "test_uz_inverter_adapter_test_vectors.h"

#define TEST_BASE_ADDRESS 0x0000000F
#define TEST_IP_CORE_FRQ 100000000U

// true = enables printf executions that output every result of the test vectors
bool debug_output = false;

   struct uz_inverter_adapter_config_t test_config = {
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
        .linear_interpolation_params.a = 162.35f,
        .linear_interpolation_params.b = 20.107f      
    };

    struct uz_inverter_adapter_outputs_t test_outputs = {
        .PWMdutyCycNormalized_H1 = 0.0,
        .PWMdutyCycNormalized_L1 = 0.0,
        .PWMdutyCycNormalized_H2 = 0.0,
        .PWMdutyCycNormalized_L2 = 0.0,
        .PWMdutyCycNormalized_H3 = 0.0,
        .PWMdutyCycNormalized_L3 = 0.0,
        .ChipTempDegreesCelsius_H1 = 0.0,
        .ChipTempDegreesCelsius_L1 = 0.0,
        .ChipTempDegreesCelsius_H2 = 0.0,
        .ChipTempDegreesCelsius_L2 = 0.0,
        .ChipTempDegreesCelsius_H3 = 0.0,
        .ChipTempDegreesCelsius_L3 = 0.0,
        .OC = 0,
        .OC_H1 = 0,
        .OC_L1 = 0,
        .OC_H2 = 0,
        .OC_L2 = 0,
        .OC_H3 = 0,
        .OC_L3 = 0,
        .FAULT = 0,
        .FAULT_H1 = 0,
        .FAULT_L1 = 0,
        .FAULT_H2 = 0,
        .FAULT_L2 = 0,
        .FAULT_H3 = 0,
        .FAULT_L3 = 0,
        .I_DIAG = 0,
        .I_DC_DIAG = 0,
        .I1_DIAG = 0,
        .I2_DIAG = 0,
        .I3_DIAG = 0,
    };

    struct uz_inverter_adapter_t {
        bool is_ready;
        struct uz_inverter_adapter_config_t config;
        struct uz_inverter_adapter_outputs_t outputs;
    };   

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_inverter_adapter_successful_init(void)
{
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_inverter_adapter_get_temperature_degrees_celsius(void)
{
    //create test instance
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs); 

    float dutycycle_Normalized = 0.065f;
    float temperature_degrees_celsius = 30.6597f;
    float temperature_degrees_celsius_readback = uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(test_instance, dutycycle_Normalized);
    TEST_ASSERT_EQUAL_FLOAT(temperature_degrees_celsius,temperature_degrees_celsius_readback);
}

void test_uz_inverter_adapter_I_DC_DIAG_results(void)
{
    //create test instance
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs); 

    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H3);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L3);
    
    uz_inverter_adapter_hw_get_OC_IgnoreAndReturn(test_instance->outputs.OC);
    uz_inverter_adapter_hw_get_FAULT_IgnoreAndReturn(test_instance->outputs.FAULT);

    int i=0;
    uint32_t I_DC_DIAG_result[16] = {0};
    
    for (i=0;i<=15;i++) {
        test_instance->outputs.I_DIAG = I_DIAG_test[i];
        uz_inverter_adapter_hw_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);
        uz_inverter_adapter_update_states(test_instance);
        I_DC_DIAG_result[i] = test_instance->outputs.I_DC_DIAG;
        if(debug_output == true) {
        printf("I_DC_DIAG_result: %i, expected: %i, error: %i\n", I_DC_DIAG_result[i],I_DC_DIAG_ref_result[i],I_DC_DIAG_ref_result[i]-I_DC_DIAG_result[i]);
        };
        TEST_ASSERT_EQUAL_INT(I_DC_DIAG_ref_result[i],I_DC_DIAG_result[i]);
    }
}

void test_uz_inverter_adapter_I1_DIAG_results(void)
{
    //create test instance
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs); 

    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H3);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L3);
    
    uz_inverter_adapter_hw_get_OC_IgnoreAndReturn(test_instance->outputs.OC);
    uz_inverter_adapter_hw_get_FAULT_IgnoreAndReturn(test_instance->outputs.FAULT);

    int i=0;
    uint32_t I1_DIAG_result[16] = {0};
    
    for (i=0;i<=15;i++) {
        test_instance->outputs.I_DIAG = I_DIAG_test[i];
        uz_inverter_adapter_hw_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);
        uz_inverter_adapter_update_states(test_instance);
        I1_DIAG_result[i] = test_instance->outputs.I1_DIAG;
        if(debug_output == true) {
        printf("I1_DIAG_result: %i, expected: %i, error: %i\n", I1_DIAG_result[i],I1_DIAG_ref_result[i],I1_DIAG_ref_result[i]-I1_DIAG_result[i]);
        };
        TEST_ASSERT_EQUAL_INT(I1_DIAG_ref_result[i],I1_DIAG_result[i]);
    }
}

void test_uz_inverter_adapter_I2_DIAG_results(void)
{
    //create test instance
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs); 

    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H3);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L3);
    
    uz_inverter_adapter_hw_get_OC_IgnoreAndReturn(test_instance->outputs.OC);
    uz_inverter_adapter_hw_get_FAULT_IgnoreAndReturn(test_instance->outputs.FAULT);

    int i=0;
    uint32_t I2_DIAG_result[16] = {0};
    
    for (i=0;i<=15;i++) {
        test_instance->outputs.I_DIAG = I_DIAG_test[i];
        uz_inverter_adapter_hw_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);
        uz_inverter_adapter_update_states(test_instance);
        I2_DIAG_result[i] = test_instance->outputs.I2_DIAG;
        if(debug_output == true) {
        printf("I2_DIAG_result: %i, expected: %i, error: %i\n", I2_DIAG_result[i],I2_DIAG_ref_result[i],I2_DIAG_ref_result[i]-I2_DIAG_result[i]);
        };
        TEST_ASSERT_EQUAL_INT(I2_DIAG_ref_result[i],I2_DIAG_result[i]);
    }
}

void test_uz_inverter_adapter_I3_DIAG_results(void)
{
    //create test instance
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs); 

    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H3);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L3);
    
    uz_inverter_adapter_hw_get_OC_IgnoreAndReturn(test_instance->outputs.OC);
    uz_inverter_adapter_hw_get_FAULT_IgnoreAndReturn(test_instance->outputs.FAULT);

    int i=0;
    uint32_t I3_DIAG_result[16] = {0};
    
    for (i=0;i<=15;i++) {
        test_instance->outputs.I_DIAG = I_DIAG_test[i];
        uz_inverter_adapter_hw_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);
        uz_inverter_adapter_update_states(test_instance);
        I3_DIAG_result[i] = test_instance->outputs.I3_DIAG;
        if(debug_output == true) {
        printf("I3_DIAG_result: %i, expected: %i, error: %i\n", I3_DIAG_result[i],I3_DIAG_ref_result[i],I3_DIAG_ref_result[i]-I3_DIAG_result[i]);
        };
        TEST_ASSERT_EQUAL_INT(I3_DIAG_ref_result[i],I3_DIAG_result[i]);
    }
}

void test_uz_inverter_adapter_OC_results(void)
{
    //create test instance
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs); 

    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H3);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L3);
    
    
    uz_inverter_adapter_hw_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);
    uz_inverter_adapter_hw_get_FAULT_IgnoreAndReturn(test_instance->outputs.FAULT);

    int i=0;
    uint32_t OC_H1_result[64] = {0};
    uint32_t OC_L1_result[64] = {0};
    uint32_t OC_H2_result[64] = {0};
    uint32_t OC_L2_result[64] = {0};
    uint32_t OC_H3_result[64] = {0};
    uint32_t OC_L3_result[64] = {0};

    for (i=0;i<=63;i++) {
        test_instance->outputs.OC = OC_test[i];
        uz_inverter_adapter_hw_get_OC_IgnoreAndReturn(test_instance->outputs.OC);
        uz_inverter_adapter_update_states(test_instance);
        OC_H1_result[i] = test_instance->outputs.OC_H1;
        OC_L1_result[i] = test_instance->outputs.OC_L1;
        OC_H2_result[i] = test_instance->outputs.OC_H2;
        OC_L2_result[i] = test_instance->outputs.OC_L2;
        OC_H3_result[i] = test_instance->outputs.OC_H3;
        OC_L3_result[i] = test_instance->outputs.OC_L3;
        if(debug_output == true) {
         printf("OC_H1_result: %i, expected: %i, error: %i\n", OC_H1_result[i],OC_H1_ref_result[i],OC_H1_ref_result[i]-OC_H1_result[i]);
         printf("OC_L1_result: %i, expected: %i, error: %i\n", OC_L1_result[i],OC_L1_ref_result[i],OC_L1_ref_result[i]-OC_L1_result[i]);
         printf("OC_H2_result: %i, expected: %i, error: %i\n", OC_H2_result[i],OC_H2_ref_result[i],OC_H2_ref_result[i]-OC_H2_result[i]);
         printf("OC_L2_result: %i, expected: %i, error: %i\n", OC_L2_result[i],OC_L2_ref_result[i],OC_L2_ref_result[i]-OC_L2_result[i]);
         printf("OC_H3_result: %i, expected: %i, error: %i\n", OC_H3_result[i],OC_H3_ref_result[i],OC_H3_ref_result[i]-OC_H3_result[i]);
         printf("OC_L3_result: %i, expected: %i, error: %i\n", OC_L3_result[i],OC_L3_ref_result[i],OC_L3_ref_result[i]-OC_L3_result[i]);
        };
        TEST_ASSERT_EQUAL_INT(OC_H1_ref_result[i],OC_H1_result[i]);
        TEST_ASSERT_EQUAL_INT(OC_L1_ref_result[i],OC_L1_result[i]);
        TEST_ASSERT_EQUAL_INT(OC_H2_ref_result[i],OC_H2_result[i]);
        TEST_ASSERT_EQUAL_INT(OC_L2_ref_result[i],OC_L2_result[i]);
        TEST_ASSERT_EQUAL_INT(OC_H3_ref_result[i],OC_H3_result[i]);
        TEST_ASSERT_EQUAL_INT(OC_L3_ref_result[i],OC_L3_result[i]);
    }
}

void test_uz_inverter_adapter_FAULT_H1_results(void)
{
    //create test instance
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs); 

    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H3);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L3);
    
    uz_inverter_adapter_hw_get_OC_IgnoreAndReturn(test_instance->outputs.OC);
    uz_inverter_adapter_hw_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);

    int i=0;
    uint32_t FAULT_H1_result[64] = {0};
    
    for (i=0;i<=63;i++) {
        test_instance->outputs.FAULT = FAULT_test[i];
        uz_inverter_adapter_hw_get_FAULT_IgnoreAndReturn(test_instance->outputs.FAULT);
        uz_inverter_adapter_update_states(test_instance);
        FAULT_H1_result[i] = test_instance->outputs.FAULT_H1;
        if(debug_output == true) {
         printf("FAULT_H1_result: %i, expected: %i, error: %i\n", FAULT_H1_result[i],FAULT_H1_ref_result[i],FAULT_H1_ref_result[i]-FAULT_H1_result[i]);
        };
        TEST_ASSERT_EQUAL_INT(FAULT_H1_ref_result[i],FAULT_H1_result[i]);
    }
}

void test_uz_inverter_adapter_FAULT_L1_results(void)
{
    //create test instance
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs); 

    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H3);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L3);
    
    uz_inverter_adapter_hw_get_OC_IgnoreAndReturn(test_instance->outputs.OC);
    uz_inverter_adapter_hw_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);

    int i=0;
    uint32_t FAULT_L1_result[64] = {0};
    
    for (i=0;i<=63;i++) {
        test_instance->outputs.FAULT = FAULT_test[i];
        uz_inverter_adapter_hw_get_FAULT_IgnoreAndReturn(test_instance->outputs.FAULT);
        uz_inverter_adapter_update_states(test_instance);
        FAULT_L1_result[i] = test_instance->outputs.FAULT_L1;
        if(debug_output == true) {
         printf("FAULT_L1_result: %i, expected: %i, error: %i\n", FAULT_L1_result[i],FAULT_L1_ref_result[i],FAULT_L1_ref_result[i]-FAULT_L1_result[i]);
        };
        TEST_ASSERT_EQUAL_INT(FAULT_L1_ref_result[i],FAULT_L1_result[i]);
    }
}

void test_uz_inverter_adapter_FAULT_H2_results(void)
{
    //create test instance
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs); 

    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H3);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L3);
    
    uz_inverter_adapter_hw_get_OC_IgnoreAndReturn(test_instance->outputs.OC);
    uz_inverter_adapter_hw_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);

    int i=0;
    uint32_t FAULT_H2_result[64] = {0};
    
    for (i=0;i<=63;i++) {
        test_instance->outputs.FAULT = FAULT_test[i];
        uz_inverter_adapter_hw_get_FAULT_IgnoreAndReturn(test_instance->outputs.FAULT);
        uz_inverter_adapter_update_states(test_instance);
        FAULT_H2_result[i] = test_instance->outputs.FAULT_H2;
        if(debug_output == true) {
         printf("FAULT_H2_result: %i, expected: %i, error: %i\n", FAULT_H2_result[i],FAULT_H2_ref_result[i],FAULT_H2_ref_result[i]-FAULT_H2_result[i]);
        };
        TEST_ASSERT_EQUAL_INT(FAULT_H2_ref_result[i],FAULT_H2_result[i]);
    }
}

void test_uz_inverter_adapter_FAULT_L2_results(void)
{
    //create test instance
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs); 

    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H3);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L3);
    
    uz_inverter_adapter_hw_get_OC_IgnoreAndReturn(test_instance->outputs.OC);
    uz_inverter_adapter_hw_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);

    int i=0;
    uint32_t FAULT_L2_result[64] = {0};
    
    for (i=0;i<=63;i++) {
        test_instance->outputs.FAULT = FAULT_test[i];
        uz_inverter_adapter_hw_get_FAULT_IgnoreAndReturn(test_instance->outputs.FAULT);
        uz_inverter_adapter_update_states(test_instance);
        FAULT_L2_result[i] = test_instance->outputs.FAULT_L2;
        if(debug_output == true) {
         printf("FAULT_L2_result: %i, expected: %i, error: %i\n", FAULT_L2_result[i],FAULT_L2_ref_result[i],FAULT_L2_ref_result[i]-FAULT_L2_result[i]);
        };
        TEST_ASSERT_EQUAL_INT(FAULT_L2_ref_result[i],FAULT_L2_result[i]);
    }
}

void test_uz_inverter_adapter_FAULT_H3_results(void)
{
    //create test instance
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs); 

    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H3);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L3);
    
    uz_inverter_adapter_hw_get_OC_IgnoreAndReturn(test_instance->outputs.OC);
    uz_inverter_adapter_hw_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);

    int i=0;
    uint32_t FAULT_H3_result[64] = {0};
    
    for (i=0;i<=63;i++) {
        test_instance->outputs.FAULT = FAULT_test[i];
        uz_inverter_adapter_hw_get_FAULT_IgnoreAndReturn(test_instance->outputs.FAULT);
        uz_inverter_adapter_update_states(test_instance);
        FAULT_H3_result[i] = test_instance->outputs.FAULT_H3;
        if(debug_output == true) {
         printf("FAULT_H3_result: %i, expected: %i, error: %i\n", FAULT_H3_result[i],FAULT_H3_ref_result[i],FAULT_H3_ref_result[i]-FAULT_H3_result[i]);
        };
        TEST_ASSERT_EQUAL_INT(FAULT_H3_ref_result[i],FAULT_H3_result[i]);
    }
}

void test_uz_inverter_adapter_FAULT_L3_results(void)
{
    //create test instance
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs); 

    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L1);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L2);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H3);
    uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L3);
    
    uz_inverter_adapter_hw_get_OC_IgnoreAndReturn(test_instance->outputs.OC);
    uz_inverter_adapter_hw_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);

    int i=0;
    uint32_t FAULT_L3_result[64] = {0};
    
    for (i=0;i<=63;i++) {
        test_instance->outputs.FAULT = FAULT_test[i];
        uz_inverter_adapter_hw_get_FAULT_IgnoreAndReturn(test_instance->outputs.FAULT);
        uz_inverter_adapter_update_states(test_instance);
        FAULT_L3_result[i] = test_instance->outputs.FAULT_L3;
        if(debug_output == true) {
         printf("FAULT_L3_result: %i, expected: %i, error: %i\n", FAULT_L3_result[i],FAULT_L3_ref_result[i],FAULT_L3_ref_result[i]-FAULT_L3_result[i]);
        };
        TEST_ASSERT_EQUAL_INT(FAULT_L3_ref_result[i],FAULT_L3_result[i]);
    }
}

void test_uz_inverter_adapter_dutycyc_to_temperature_results(void)
{
    //create test instance
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs); 

    int i=0;
    float temperature_degrees_celsius_H1_result[11] = {0};
    float temperature_degrees_celsius_L1_result[11] = {0};
    float temperature_degrees_celsius_H2_result[11] = {0};
    float temperature_degrees_celsius_L2_result[11] = {0};
    float temperature_degrees_celsius_H3_result[11] = {0};
    float temperature_degrees_celsius_L3_result[11] = {0};

    for (i=0;i<=10;i++) {
        uz_inverter_adapter_hw_get_OC_IgnoreAndReturn(test_instance->outputs.OC);
        uz_inverter_adapter_hw_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);
        uz_inverter_adapter_hw_get_FAULT_IgnoreAndReturn(test_instance->outputs.FAULT);
        test_instance->outputs.PWMdutyCycNormalized_H1 = dutycyc_test[i];
        test_instance->outputs.PWMdutyCycNormalized_L1 = dutycyc_test[i];
        test_instance->outputs.PWMdutyCycNormalized_H2 = dutycyc_test[i];
        test_instance->outputs.PWMdutyCycNormalized_L2 = dutycyc_test[i];
        test_instance->outputs.PWMdutyCycNormalized_H3 = dutycyc_test[i];
        test_instance->outputs.PWMdutyCycNormalized_L3 = dutycyc_test[i];
        uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H1);
        uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L1);
        uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H2);
        uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L2);
        uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H3);
        uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L3);
        uz_inverter_adapter_update_states(test_instance);
        temperature_degrees_celsius_H1_result[i] = test_instance->outputs.ChipTempDegreesCelsius_H1;
        temperature_degrees_celsius_L1_result[i] = test_instance->outputs.ChipTempDegreesCelsius_L1;
        temperature_degrees_celsius_H2_result[i] = test_instance->outputs.ChipTempDegreesCelsius_H2;
        temperature_degrees_celsius_L2_result[i] = test_instance->outputs.ChipTempDegreesCelsius_L2;
        temperature_degrees_celsius_H3_result[i] = test_instance->outputs.ChipTempDegreesCelsius_H3;
        temperature_degrees_celsius_L3_result[i] = test_instance->outputs.ChipTempDegreesCelsius_L3;
        if(debug_output == true) {
         //casting to double to get rid of compiler warnings. printf doesn't support floats
         printf("ChipTempDegreesCelsius_H1_result: %f, expected: %f, error: %f\n", (double)temperature_degrees_celsius_H1_result[i],(double)temp_ref_result[i],(double)temp_ref_result[i]-(double)temperature_degrees_celsius_H1_result[i]);
         printf("ChipTempDegreesCelsius_L1_result: %f, expected: %f, error: %f\n", (double)temperature_degrees_celsius_L1_result[i],(double)temp_ref_result[i],(double)temp_ref_result[i]-(double)temperature_degrees_celsius_L1_result[i]);
         printf("ChipTempDegreesCelsius_H2_result: %f, expected: %f, error: %f\n", (double)temperature_degrees_celsius_H2_result[i],(double)temp_ref_result[i],(double)temp_ref_result[i]-(double)temperature_degrees_celsius_H2_result[i]);
         printf("ChipTempDegreesCelsius_L2_result: %f, expected: %f, error: %f\n", (double)temperature_degrees_celsius_L2_result[i],(double)temp_ref_result[i],(double)temp_ref_result[i]-(double)temperature_degrees_celsius_L2_result[i]);
         printf("ChipTempDegreesCelsius_H3_result: %f, expected: %f, error: %f\n", (double)temperature_degrees_celsius_H3_result[i],(double)temp_ref_result[i],(double)temp_ref_result[i]-(double)temperature_degrees_celsius_H3_result[i]);
         printf("ChipTempDegreesCelsius_L3_result: %f, expected: %f, error: %f\n\n", (double)temperature_degrees_celsius_L3_result[i],(double)temp_ref_result[i],(double)temp_ref_result[i]-(double)temperature_degrees_celsius_L3_result[i]);
        };
        TEST_ASSERT_EQUAL_FLOAT(temp_ref_result[i],temperature_degrees_celsius_H1_result[i]);
        TEST_ASSERT_EQUAL_FLOAT(temp_ref_result[i],temperature_degrees_celsius_L1_result[i]);
        TEST_ASSERT_EQUAL_FLOAT(temp_ref_result[i],temperature_degrees_celsius_H2_result[i]);
        TEST_ASSERT_EQUAL_FLOAT(temp_ref_result[i],temperature_degrees_celsius_L2_result[i]);
        TEST_ASSERT_EQUAL_FLOAT(temp_ref_result[i],temperature_degrees_celsius_H3_result[i]);
        TEST_ASSERT_EQUAL_FLOAT(temp_ref_result[i],temperature_degrees_celsius_L3_result[i]);
    }
}

void test_uz_inverter_adapter_get_outputs(void) {
    //create test instance
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs); 

    static int i=0;

        struct uz_inverter_adapter_outputs_t return_outputs = {
        .PWMdutyCycNormalized_H1 = 0.0,
        .PWMdutyCycNormalized_L1 = 0.0,
        .PWMdutyCycNormalized_H2 = 0.0,
        .PWMdutyCycNormalized_L2 = 0.0,
        .PWMdutyCycNormalized_H3 = 0.0,
        .PWMdutyCycNormalized_L3 = 0.0,
        .ChipTempDegreesCelsius_H1 = 0.0,
        .ChipTempDegreesCelsius_L1 = 0.0,
        .ChipTempDegreesCelsius_H2 = 0.0,
        .ChipTempDegreesCelsius_L2 = 0.0,
        .ChipTempDegreesCelsius_H3 = 0.0,
        .ChipTempDegreesCelsius_L3 = 0.0,
        .OC = 0,
        .OC_H1 = 0,
        .OC_L1 = 0,
        .OC_H2 = 0,
        .OC_L2 = 0,
        .OC_H3 = 0,
        .OC_L3 = 0,
        .FAULT = 0,
        .FAULT_H1 = 0,
        .FAULT_L1 = 0,
        .FAULT_H2 = 0,
        .FAULT_L2 = 0,
        .FAULT_H3 = 0,
        .FAULT_L3 = 0,
        .I_DIAG = 0,
        .I_DC_DIAG = 0,
        .I1_DIAG = 0,
        .I2_DIAG = 0,
        .I3_DIAG = 0,
    };

    for (i=0;i<=10;i++) {
        uz_inverter_adapter_hw_get_OC_IgnoreAndReturn(test_instance->outputs.OC);
        uz_inverter_adapter_hw_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);
        uz_inverter_adapter_hw_get_FAULT_IgnoreAndReturn(test_instance->outputs.FAULT);
        test_instance->outputs.PWMdutyCycNormalized_H1 = dutycyc_test[i];
        test_instance->outputs.PWMdutyCycNormalized_L1 = dutycyc_test[i];
        test_instance->outputs.PWMdutyCycNormalized_H2 = dutycyc_test[i];
        test_instance->outputs.PWMdutyCycNormalized_L2 = dutycyc_test[i];
        test_instance->outputs.PWMdutyCycNormalized_H3 = dutycyc_test[i];
        test_instance->outputs.PWMdutyCycNormalized_L3 = dutycyc_test[i];
        uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H1);
        uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L1);
        uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H2);
        uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L2);
        uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_H3);
        uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized_L3);
        
        return_outputs = uz_inverter_adapter_get_outputs(test_instance);

        TEST_ASSERT_EQUAL_FLOAT(return_outputs.ChipTempDegreesCelsius_H1,test_instance->outputs.ChipTempDegreesCelsius_H1);
        TEST_ASSERT_EQUAL_FLOAT(return_outputs.ChipTempDegreesCelsius_L1,test_instance->outputs.ChipTempDegreesCelsius_L1);
        TEST_ASSERT_EQUAL_FLOAT(return_outputs.ChipTempDegreesCelsius_H2,test_instance->outputs.ChipTempDegreesCelsius_H2);
        TEST_ASSERT_EQUAL_FLOAT(return_outputs.ChipTempDegreesCelsius_L2,test_instance->outputs.ChipTempDegreesCelsius_L2);
        TEST_ASSERT_EQUAL_FLOAT(return_outputs.ChipTempDegreesCelsius_H3,test_instance->outputs.ChipTempDegreesCelsius_H3);
        TEST_ASSERT_EQUAL_FLOAT(return_outputs.ChipTempDegreesCelsius_L3,test_instance->outputs.ChipTempDegreesCelsius_L3);
    }


}

void test_uz_inverter_adapter_set_PWM_EN(void) {

    //create test instance
    uz_inverter_adapter_t *test_instance = uz_inverter_adapter_init(test_config, test_outputs); 

    bool pwm_en = true;
    uz_inverter_adapter_hw_set_PWM_EN_Expect(test_instance->config.base_address, pwm_en);
    uz_inverter_adapter_set_PWM_EN(test_instance, pwm_en);
}
#endif // TEST
