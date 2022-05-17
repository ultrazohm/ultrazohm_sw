#ifdef TEST

#include "unity.h"

#include "test_assert_with_exception.h"
#include "uz_dac_interface.h"
#include "mock_uz_dac_interface_hw.h"
#include <stdint.h>
#include "uz_array.h"

#define TEST_BASE_ADDRESS 0x0000000Fu
#define TEST_IP_CORE_FRQ 100000000u

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_dac_interface_set_values(void)
{
    struct uz_dac_interface_config_t config={
        .base_address=TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };

    uz_dac_interface_t* test=uz_dac_interface_init(config);
    int32_t output[8]={1,2,3,4,5,6,7,8};
    uz_array_int32_t output_values={
        .data=&output[0],
        .length=8
    };

    uz_dac_interface_hw_write_dac1_Expect(TEST_BASE_ADDRESS,output[0]);
    uz_dac_interface_hw_write_dac2_Expect(TEST_BASE_ADDRESS,output[1]);
    uz_dac_interface_hw_write_dac3_Expect(TEST_BASE_ADDRESS,output[2]);
    uz_dac_interface_hw_write_dac4_Expect(TEST_BASE_ADDRESS,output[3]);
    uz_dac_interface_hw_write_dac5_Expect(TEST_BASE_ADDRESS,output[4]);
    uz_dac_interface_hw_write_dac6_Expect(TEST_BASE_ADDRESS,output[5]);
    uz_dac_interface_hw_write_dac7_Expect(TEST_BASE_ADDRESS,output[6]);
    uz_dac_interface_hw_write_dac8_Expect(TEST_BASE_ADDRESS,output[7]);

    uz_dac_interface_hw_write_trigger_Expect(TEST_BASE_ADDRESS,true);
    uz_dac_interface_hw_write_trigger_Expect(TEST_BASE_ADDRESS,false);

    uz_dac_interface_set_ouput_values(test,&output_values);

}

#endif // TEST
