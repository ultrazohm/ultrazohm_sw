#ifdef TEST

#include "unity.h"

#include "uz_d_gan_inverter.h"
#include "test_assert_with_exception.h"
#include "uz_d_gan_inverter.h"
#include "uz_d_gan_inverter_hwAddresses.h"
#include "mock_uz_d_gan_inverter_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include <stdbool.h>
#include "uz_d_gan_test_vectors.h"

#define TEST_BASE_ADDRESS 0x0000000F
#define TEST_IP_CORE_FRQ 100000000U

    struct uz_d_gan_inverter_config_t test_config = {
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
    };

    struct uz_d_gan_inverter_outputs_t test_outputs = {
        .PWMdutyCycPerCent_H1 = 0.0,
        .PWMdutyCycPerCent_L1 = 0.0,
        .PWMdutyCycPerCent_H2 = 0.0,
        .PWMdutyCycPerCent_L2 = 0.0,
        .PWMdutyCycPerCent_H3 = 0.0,
        .PWMdutyCycPerCent_L3 = 0.0,
        .GaN_ChipTempDegreesCelsius_H1 = 0.0,
        .GaN_ChipTempDegreesCelsius_L1 = 0.0,
        .GaN_ChipTempDegreesCelsius_H2 = 0.0,
        .GaN_ChipTempDegreesCelsius_L2 = 0.0,
        .GaN_ChipTempDegreesCelsius_H3 = 0.0,
        .GaN_ChipTempDegreesCelsius_L3 = 0.0,
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

    struct uz_d_gan_inverter_t {
        bool is_ready;
        struct uz_d_gan_inverter_config_t config;
        struct uz_d_gan_inverter_outputs_t outputs;
    };   

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_d_gan_inverter_successful_init(void)
{
    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(test_config, test_outputs);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_d_gan_inverter_get_temperature_degrees_celsius(void)
{
    float dutycycle_percent = 6.5;
    float temperature_degrees_celsius = 30.6597;
    float temperature_degrees_celsius_readback = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(dutycycle_percent);
    TEST_ASSERT_EQUAL_FLOAT(temperature_degrees_celsius,temperature_degrees_celsius_readback);
}

void test_uz_d_gan_inverter_I_DC_DIAG_results(void)
{
    //create test instance
    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(test_config, test_outputs); 

    uz_d_gan_inverter_get_PWMdutyCycPerCent_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H3);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L3);
    
    uz_d_gan_inverter_get_OC_GaN_IgnoreAndReturn(test_instance->outputs.OC);
    uz_d_gan_inverter_get_FAULT_GaN_IgnoreAndReturn(test_instance->outputs.FAULT);

    int i=0;
    uint32_t I_DC_DIAG_result[16] = {0};
    
    for (i=0;i<=15;i++) {
        test_instance->outputs.I_DIAG = I_DIAG_test[i];
        uz_d_gan_inverter_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);
        uz_d_gan_inverter_update_states(test_instance);
        I_DC_DIAG_result[i] = test_instance->outputs.I_DC_DIAG;
        // printf("I_DC_DIAG_result: %i, expected: %i, error: %i\n", I_DC_DIAG_result[i],I_DC_DIAG_ref_result[i],I_DC_DIAG_ref_result[i]-I_DC_DIAG_result[i]);
        TEST_ASSERT_EQUAL_INT(I_DC_DIAG_ref_result[i],I_DC_DIAG_result[i]);
    }
}

void test_uz_d_gan_inverter_I1_DIAG_results(void)
{
    //create test instance
    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(test_config, test_outputs); 

    uz_d_gan_inverter_get_PWMdutyCycPerCent_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H3);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L3);
    
    uz_d_gan_inverter_get_OC_GaN_IgnoreAndReturn(test_instance->outputs.OC);
    uz_d_gan_inverter_get_FAULT_GaN_IgnoreAndReturn(test_instance->outputs.FAULT);

    int i=0;
    uint32_t I1_DIAG_result[16] = {0};
    
    for (i=0;i<=15;i++) {
        test_instance->outputs.I_DIAG = I_DIAG_test[i];
        uz_d_gan_inverter_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);
        uz_d_gan_inverter_update_states(test_instance);
        I1_DIAG_result[i] = test_instance->outputs.I1_DIAG;
        // printf("I1_DIAG_result: %i, expected: %i, error: %i\n", I1_DIAG_result[i],I1_DIAG_ref_result[i],I1_DIAG_ref_result[i]-I1_DIAG_result[i]);
        TEST_ASSERT_EQUAL_INT(I1_DIAG_ref_result[i],I1_DIAG_result[i]);
    }
}

void test_uz_d_gan_inverter_I2_DIAG_results(void)
{
    //create test instance
    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(test_config, test_outputs); 

    uz_d_gan_inverter_get_PWMdutyCycPerCent_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H3);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L3);
    
    uz_d_gan_inverter_get_OC_GaN_IgnoreAndReturn(test_instance->outputs.OC);
    uz_d_gan_inverter_get_FAULT_GaN_IgnoreAndReturn(test_instance->outputs.FAULT);

    int i=0;
    uint32_t I2_DIAG_result[16] = {0};
    
    for (i=0;i<=15;i++) {
        test_instance->outputs.I_DIAG = I_DIAG_test[i];
        uz_d_gan_inverter_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);
        uz_d_gan_inverter_update_states(test_instance);
        I2_DIAG_result[i] = test_instance->outputs.I2_DIAG;
        // printf("I2_DIAG_result: %i, expected: %i, error: %i\n", I2_DIAG_result[i],I2_DIAG_ref_result[i],I2_DIAG_ref_result[i]-I2_DIAG_result[i]);
        TEST_ASSERT_EQUAL_INT(I2_DIAG_ref_result[i],I2_DIAG_result[i]);
    }
}

void test_uz_d_gan_inverter_I3_DIAG_results(void)
{
    //create test instance
    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(test_config, test_outputs); 

    uz_d_gan_inverter_get_PWMdutyCycPerCent_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H3);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L3);
    
    uz_d_gan_inverter_get_OC_GaN_IgnoreAndReturn(test_instance->outputs.OC);
    uz_d_gan_inverter_get_FAULT_GaN_IgnoreAndReturn(test_instance->outputs.FAULT);

    int i=0;
    uint32_t I3_DIAG_result[16] = {0};
    
    for (i=0;i<=15;i++) {
        test_instance->outputs.I_DIAG = I_DIAG_test[i];
        uz_d_gan_inverter_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);
        uz_d_gan_inverter_update_states(test_instance);
        I3_DIAG_result[i] = test_instance->outputs.I3_DIAG;
        // printf("I3_DIAG_result: %i, expected: %i, error: %i\n", I3_DIAG_result[i],I3_DIAG_ref_result[i],I3_DIAG_ref_result[i]-I3_DIAG_result[i]);
        TEST_ASSERT_EQUAL_INT(I3_DIAG_ref_result[i],I3_DIAG_result[i]);
    }
}

void test_uz_d_gan_inverter_OC_results(void)
{
    //create test instance
    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(test_config, test_outputs); 

    uz_d_gan_inverter_get_PWMdutyCycPerCent_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H3);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L3);
    
    
    uz_d_gan_inverter_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);
    uz_d_gan_inverter_get_FAULT_GaN_IgnoreAndReturn(test_instance->outputs.FAULT);

    int i=0;
    uint32_t OC_H1_result[64] = {0};
    uint32_t OC_L1_result[64] = {0};
    uint32_t OC_H2_result[64] = {0};
    uint32_t OC_L2_result[64] = {0};
    uint32_t OC_H3_result[64] = {0};
    uint32_t OC_L3_result[64] = {0};

    for (i=0;i<=63;i++) {
        test_instance->outputs.OC = OC_test[i];
        uz_d_gan_inverter_get_OC_GaN_IgnoreAndReturn(test_instance->outputs.OC);
        uz_d_gan_inverter_update_states(test_instance);
        OC_H1_result[i] = test_instance->outputs.OC_H1;
        OC_L1_result[i] = test_instance->outputs.OC_L1;
        OC_H2_result[i] = test_instance->outputs.OC_H2;
        OC_L2_result[i] = test_instance->outputs.OC_L2;
        OC_H3_result[i] = test_instance->outputs.OC_H3;
        OC_L3_result[i] = test_instance->outputs.OC_L3;
        // printf("OC_H1_result: %i, expected: %i, error: %i\n", OC_H1_result[i],OC_H1_ref_result[i],OC_H1_ref_result[i]-OC_H1_result[i]);
        // printf("OC_L1_result: %i, expected: %i, error: %i\n", OC_L1_result[i],OC_L1_ref_result[i],OC_L1_ref_result[i]-OC_L1_result[i]);
        // printf("OC_H2_result: %i, expected: %i, error: %i\n", OC_H2_result[i],OC_H2_ref_result[i],OC_H2_ref_result[i]-OC_H2_result[i]);
        // printf("OC_L2_result: %i, expected: %i, error: %i\n", OC_L2_result[i],OC_L2_ref_result[i],OC_L2_ref_result[i]-OC_L2_result[i]);
        // printf("OC_H3_result: %i, expected: %i, error: %i\n", OC_H3_result[i],OC_H3_ref_result[i],OC_H3_ref_result[i]-OC_H3_result[i]);
        // printf("OC_L3_result: %i, expected: %i, error: %i\n", OC_L3_result[i],OC_L3_ref_result[i],OC_L3_ref_result[i]-OC_L3_result[i]);
        TEST_ASSERT_EQUAL_INT(OC_H1_ref_result[i],OC_H1_result[i]);
        TEST_ASSERT_EQUAL_INT(OC_L1_ref_result[i],OC_L1_result[i]);
        TEST_ASSERT_EQUAL_INT(OC_H2_ref_result[i],OC_H2_result[i]);
        TEST_ASSERT_EQUAL_INT(OC_L2_ref_result[i],OC_L2_result[i]);
        TEST_ASSERT_EQUAL_INT(OC_H3_ref_result[i],OC_H3_result[i]);
        TEST_ASSERT_EQUAL_INT(OC_L3_ref_result[i],OC_L3_result[i]);
    }
}

void test_uz_d_gan_inverter_FAULT_H1_results(void)
{
    //create test instance
    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(test_config, test_outputs); 

    uz_d_gan_inverter_get_PWMdutyCycPerCent_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H3);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L3);
    
    uz_d_gan_inverter_get_OC_GaN_IgnoreAndReturn(test_instance->outputs.OC);
    uz_d_gan_inverter_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);

    int i=0;
    uint32_t FAULT_H1_result[64] = {0};
    
    for (i=0;i<=63;i++) {
        test_instance->outputs.FAULT = FAULT_test[i];
        uz_d_gan_inverter_get_FAULT_GaN_IgnoreAndReturn(test_instance->outputs.FAULT);
        uz_d_gan_inverter_update_states(test_instance);
        FAULT_H1_result[i] = test_instance->outputs.FAULT_H1;
        // printf("FAULT_H1_result: %i, expected: %i, error: %i\n", FAULT_H1_result[i],FAULT_H1_ref_result[i],FAULT_H1_ref_result[i]-FAULT_H1_result[i]);
        TEST_ASSERT_EQUAL_INT(FAULT_H1_ref_result[i],FAULT_H1_result[i]);
    }
}

void test_uz_d_gan_inverter_FAULT_L1_results(void)
{
    //create test instance
    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(test_config, test_outputs); 

    uz_d_gan_inverter_get_PWMdutyCycPerCent_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H3);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L3);
    
    uz_d_gan_inverter_get_OC_GaN_IgnoreAndReturn(test_instance->outputs.OC);
    uz_d_gan_inverter_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);

    int i=0;
    uint32_t FAULT_L1_result[64] = {0};
    
    for (i=0;i<=63;i++) {
        test_instance->outputs.FAULT = FAULT_test[i];
        uz_d_gan_inverter_get_FAULT_GaN_IgnoreAndReturn(test_instance->outputs.FAULT);
        uz_d_gan_inverter_update_states(test_instance);
        FAULT_L1_result[i] = test_instance->outputs.FAULT_L1;
        // printf("FAULT_L1_result: %i, expected: %i, error: %i\n", FAULT_L1_result[i],FAULT_L1_ref_result[i],FAULT_L1_ref_result[i]-FAULT_L1_result[i]);
        TEST_ASSERT_EQUAL_INT(FAULT_L1_ref_result[i],FAULT_L1_result[i]);
    }
}

void test_uz_d_gan_inverter_FAULT_H2_results(void)
{
    //create test instance
    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(test_config, test_outputs); 

    uz_d_gan_inverter_get_PWMdutyCycPerCent_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H3);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L3);
    
    uz_d_gan_inverter_get_OC_GaN_IgnoreAndReturn(test_instance->outputs.OC);
    uz_d_gan_inverter_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);

    int i=0;
    uint32_t FAULT_H2_result[64] = {0};
    
    for (i=0;i<=63;i++) {
        test_instance->outputs.FAULT = FAULT_test[i];
        uz_d_gan_inverter_get_FAULT_GaN_IgnoreAndReturn(test_instance->outputs.FAULT);
        uz_d_gan_inverter_update_states(test_instance);
        FAULT_H2_result[i] = test_instance->outputs.FAULT_H2;
        // printf("FAULT_H2_result: %i, expected: %i, error: %i\n", FAULT_H2_result[i],FAULT_H2_ref_result[i],FAULT_H2_ref_result[i]-FAULT_H2_result[i]);
        TEST_ASSERT_EQUAL_INT(FAULT_H2_ref_result[i],FAULT_H2_result[i]);
    }
}

void test_uz_d_gan_inverter_FAULT_L2_results(void)
{
    //create test instance
    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(test_config, test_outputs); 

    uz_d_gan_inverter_get_PWMdutyCycPerCent_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H3);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L3);
    
    uz_d_gan_inverter_get_OC_GaN_IgnoreAndReturn(test_instance->outputs.OC);
    uz_d_gan_inverter_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);

    int i=0;
    uint32_t FAULT_L2_result[64] = {0};
    
    for (i=0;i<=63;i++) {
        test_instance->outputs.FAULT = FAULT_test[i];
        uz_d_gan_inverter_get_FAULT_GaN_IgnoreAndReturn(test_instance->outputs.FAULT);
        uz_d_gan_inverter_update_states(test_instance);
        FAULT_L2_result[i] = test_instance->outputs.FAULT_L2;
        // printf("FAULT_L2_result: %i, expected: %i, error: %i\n", FAULT_L2_result[i],FAULT_L2_ref_result[i],FAULT_L2_ref_result[i]-FAULT_L2_result[i]);
        TEST_ASSERT_EQUAL_INT(FAULT_L2_ref_result[i],FAULT_L2_result[i]);
    }
}

void test_uz_d_gan_inverter_FAULT_H3_results(void)
{
    //create test instance
    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(test_config, test_outputs); 

    uz_d_gan_inverter_get_PWMdutyCycPerCent_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H3);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L3);
    
    uz_d_gan_inverter_get_OC_GaN_IgnoreAndReturn(test_instance->outputs.OC);
    uz_d_gan_inverter_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);

    int i=0;
    uint32_t FAULT_H3_result[64] = {0};
    
    for (i=0;i<=63;i++) {
        test_instance->outputs.FAULT = FAULT_test[i];
        uz_d_gan_inverter_get_FAULT_GaN_IgnoreAndReturn(test_instance->outputs.FAULT);
        uz_d_gan_inverter_update_states(test_instance);
        FAULT_H3_result[i] = test_instance->outputs.FAULT_H3;
        // printf("FAULT_H3_result: %i, expected: %i, error: %i\n", FAULT_H3_result[i],FAULT_H3_ref_result[i],FAULT_H3_ref_result[i]-FAULT_H3_result[i]);
        TEST_ASSERT_EQUAL_INT(FAULT_H3_ref_result[i],FAULT_H3_result[i]);
    }
}

void test_uz_d_gan_inverter_FAULT_L3_results(void)
{
    //create test instance
    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(test_config, test_outputs); 

    uz_d_gan_inverter_get_PWMdutyCycPerCent_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H3);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L3);
    
    uz_d_gan_inverter_get_OC_GaN_IgnoreAndReturn(test_instance->outputs.OC);
    uz_d_gan_inverter_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);

    int i=0;
    uint32_t FAULT_L3_result[64] = {0};
    
    for (i=0;i<=63;i++) {
        test_instance->outputs.FAULT = FAULT_test[i];
        uz_d_gan_inverter_get_FAULT_GaN_IgnoreAndReturn(test_instance->outputs.FAULT);
        uz_d_gan_inverter_update_states(test_instance);
        FAULT_L3_result[i] = test_instance->outputs.FAULT_L3;
        // printf("FAULT_L3_result: %i, expected: %i, error: %i\n", FAULT_L3_result[i],FAULT_L3_ref_result[i],FAULT_L3_ref_result[i]-FAULT_L3_result[i]);
        TEST_ASSERT_EQUAL_INT(FAULT_L3_ref_result[i],FAULT_L3_result[i]);
    }
}

void test_uz_d_gan_inverter_dutycyc_to_temperature_results(void)
{
    //create test instance
    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(test_config, test_outputs); 

    int i=0;
    float temperature_degrees_celsius_H1_result[1001] = {0};
    float temperature_degrees_celsius_L1_result[1001] = {0};
    float temperature_degrees_celsius_H2_result[1001] = {0};
    float temperature_degrees_celsius_L2_result[1001] = {0};
    float temperature_degrees_celsius_H3_result[1001] = {0};
    float temperature_degrees_celsius_L3_result[1001] = {0};

    for (i=0;i<=1000;i++) {
        uz_d_gan_inverter_get_OC_GaN_IgnoreAndReturn(test_instance->outputs.OC);
        uz_d_gan_inverter_get_I_DIAG_IgnoreAndReturn(test_instance->outputs.I_DIAG);
        uz_d_gan_inverter_get_FAULT_GaN_IgnoreAndReturn(test_instance->outputs.FAULT);
        test_instance->outputs.PWMdutyCycPerCent_H1 = dutycyc_test[i];
        test_instance->outputs.PWMdutyCycPerCent_L1 = dutycyc_test[i];
        test_instance->outputs.PWMdutyCycPerCent_H2 = dutycyc_test[i];
        test_instance->outputs.PWMdutyCycPerCent_L2 = dutycyc_test[i];
        test_instance->outputs.PWMdutyCycPerCent_H3 = dutycyc_test[i];
        test_instance->outputs.PWMdutyCycPerCent_L3 = dutycyc_test[i];
        uz_d_gan_inverter_get_PWMdutyCycPerCent_H1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H1);
        uz_d_gan_inverter_get_PWMdutyCycPerCent_L1_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L1);
        uz_d_gan_inverter_get_PWMdutyCycPerCent_H2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H2);
        uz_d_gan_inverter_get_PWMdutyCycPerCent_L2_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L2);
        uz_d_gan_inverter_get_PWMdutyCycPerCent_H3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_H3);
        uz_d_gan_inverter_get_PWMdutyCycPerCent_L3_IgnoreAndReturn(test_instance->outputs.PWMdutyCycPerCent_L3);
        uz_d_gan_inverter_update_states(test_instance);
        temperature_degrees_celsius_H1_result[i] = test_instance->outputs.GaN_ChipTempDegreesCelsius_H1;
        temperature_degrees_celsius_L1_result[i] = test_instance->outputs.GaN_ChipTempDegreesCelsius_L1;
        temperature_degrees_celsius_H2_result[i] = test_instance->outputs.GaN_ChipTempDegreesCelsius_H2;
        temperature_degrees_celsius_L2_result[i] = test_instance->outputs.GaN_ChipTempDegreesCelsius_L2;
        temperature_degrees_celsius_H3_result[i] = test_instance->outputs.GaN_ChipTempDegreesCelsius_H3;
        temperature_degrees_celsius_L3_result[i] = test_instance->outputs.GaN_ChipTempDegreesCelsius_L3;
        // printf("GaN_ChipTempDegreesCelsius_H1_result: %f, expected: %f, error: %f\n", temperature_degrees_celsius_H1_result[i],temp_ref_result[i],temp_ref_result[i]-temperature_degrees_celsius_H1_result[i]);
        // printf("GaN_ChipTempDegreesCelsius_L1_result: %f, expected: %f, error: %f\n", temperature_degrees_celsius_L1_result[i],temp_ref_result[i],temp_ref_result[i]-temperature_degrees_celsius_L1_result[i]);
        // printf("GaN_ChipTempDegreesCelsius_H2_result: %f, expected: %f, error: %f\n", temperature_degrees_celsius_H2_result[i],temp_ref_result[i],temp_ref_result[i]-temperature_degrees_celsius_H2_result[i]);
        // printf("GaN_ChipTempDegreesCelsius_L2_result: %f, expected: %f, error: %f\n", temperature_degrees_celsius_L2_result[i],temp_ref_result[i],temp_ref_result[i]-temperature_degrees_celsius_L2_result[i]);
        // printf("GaN_ChipTempDegreesCelsius_H3_result: %f, expected: %f, error: %f\n", temperature_degrees_celsius_H3_result[i],temp_ref_result[i],temp_ref_result[i]-temperature_degrees_celsius_H3_result[i]);
        // printf("GaN_ChipTempDegreesCelsius_L3_result: %f, expected: %f, error: %f\n", temperature_degrees_celsius_L3_result[i],temp_ref_result[i],temp_ref_result[i]-temperature_degrees_celsius_L3_result[i]);
        TEST_ASSERT_EQUAL_FLOAT(temp_ref_result[i],temperature_degrees_celsius_H1_result[i]);
        TEST_ASSERT_EQUAL_FLOAT(temp_ref_result[i],temperature_degrees_celsius_L1_result[i]);
        TEST_ASSERT_EQUAL_FLOAT(temp_ref_result[i],temperature_degrees_celsius_H2_result[i]);
        TEST_ASSERT_EQUAL_FLOAT(temp_ref_result[i],temperature_degrees_celsius_L2_result[i]);
        TEST_ASSERT_EQUAL_FLOAT(temp_ref_result[i],temperature_degrees_celsius_H3_result[i]);
        TEST_ASSERT_EQUAL_FLOAT(temp_ref_result[i],temperature_degrees_celsius_L3_result[i]);
        resetTest(); // 1001 loops are too much for the memory. Therefore resetTest() clears memory BUT also all information about the test so far.
    }
}
#endif // TEST
