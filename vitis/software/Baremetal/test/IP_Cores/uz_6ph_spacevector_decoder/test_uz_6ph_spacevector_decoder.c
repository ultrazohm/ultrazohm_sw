#ifdef TEST

#include "unity.h"

#include "uz_6ph_spacevector_decoder.h"

#include "mock_uz_6ph_spacevector_decoder_hw.h" // Mock the _hw functions to isolate testing

#include "test_assert_with_exception.h"
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

void setUp(void)
{
}

void tearDown(void)
{
}


void test_uz_6ph_spacevector_decoder(void)
{
        struct uz_6ph_spacevector_decoder_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    uz_6ph_spacevector_decoder_t *instance = uz_6ph_spacevector_decoder_init(config);


    uint32_t a1 = 101;
    uint32_t a2 = 102;
    uint32_t a3 = 103;
    uint32_t a4 = 104;
    uint32_t a5 = 105;
    uint32_t a6 = 106;
    uint32_t a7 = 107;
    uint32_t a8 = 108;
    uint32_t a9 = 109;
    uint32_t a10 = 110;
    uint32_t a11 = 111;
    uint32_t a12 = 112;
    uint32_t a13 = 113;
    uint32_t a14 = 114;

    uint32_t b = 0;

    uz_6ph_spacevector_decoder_hw_read_out1_ExpectAndReturn(TEST_BASE_ADDRESS, a1);
    uz_6ph_spacevector_decoder_hw_read_out2_ExpectAndReturn(TEST_BASE_ADDRESS, a2);
    uz_6ph_spacevector_decoder_hw_read_out3_ExpectAndReturn(TEST_BASE_ADDRESS, a3);
    uz_6ph_spacevector_decoder_hw_read_out4_ExpectAndReturn(TEST_BASE_ADDRESS, a4);
    uz_6ph_spacevector_decoder_hw_read_out5_ExpectAndReturn(TEST_BASE_ADDRESS, a5);
    uz_6ph_spacevector_decoder_hw_read_out6_ExpectAndReturn(TEST_BASE_ADDRESS, a6);
    uz_6ph_spacevector_decoder_hw_read_out7_ExpectAndReturn(TEST_BASE_ADDRESS, a7);
    uz_6ph_spacevector_decoder_hw_read_out8_ExpectAndReturn(TEST_BASE_ADDRESS, a8);
    uz_6ph_spacevector_decoder_hw_read_out9_ExpectAndReturn(TEST_BASE_ADDRESS, a9);
    uz_6ph_spacevector_decoder_hw_read_out10_ExpectAndReturn(TEST_BASE_ADDRESS, a10);
    uz_6ph_spacevector_decoder_hw_read_out11_ExpectAndReturn(TEST_BASE_ADDRESS, a11);
    uz_6ph_spacevector_decoder_hw_read_out12_ExpectAndReturn(TEST_BASE_ADDRESS, a12);
    uz_6ph_spacevector_decoder_hw_read_out13_ExpectAndReturn(TEST_BASE_ADDRESS, a13);
    uz_6ph_spacevector_decoder_hw_read_out14_ExpectAndReturn(TEST_BASE_ADDRESS, a14);

    b = uz_6ph_spacevector_decoder_get_spacevector_num(instance, 1);
    TEST_ASSERT_EQUAL_UINT32(a1, b);

    b = uz_6ph_spacevector_decoder_get_spacevector_num(instance, 2);
    TEST_ASSERT_EQUAL_UINT32(a2, b);

    b = uz_6ph_spacevector_decoder_get_spacevector_num(instance, 3);
    TEST_ASSERT_EQUAL_UINT32(a3, b);

    b = uz_6ph_spacevector_decoder_get_spacevector_num(instance, 4);
    TEST_ASSERT_EQUAL_UINT32(a4, b);

    b = uz_6ph_spacevector_decoder_get_spacevector_num(instance, 5);
    TEST_ASSERT_EQUAL_UINT32(a5, b);

    b = uz_6ph_spacevector_decoder_get_spacevector_num(instance, 6);
    TEST_ASSERT_EQUAL_UINT32(a6, b);

    b = uz_6ph_spacevector_decoder_get_spacevector_num(instance, 7);
    TEST_ASSERT_EQUAL_UINT32(a7, b);

    b = uz_6ph_spacevector_decoder_get_spacevector_num(instance, 8);
    TEST_ASSERT_EQUAL_UINT32(a8, b);

    b = uz_6ph_spacevector_decoder_get_spacevector_num(instance, 9);
    TEST_ASSERT_EQUAL_UINT32(a9, b);

    b = uz_6ph_spacevector_decoder_get_spacevector_num(instance, 10);
    TEST_ASSERT_EQUAL_UINT32(a10, b);

    b = uz_6ph_spacevector_decoder_get_spacevector_num(instance, 11);
    TEST_ASSERT_EQUAL_UINT32(a11, b);

    b = uz_6ph_spacevector_decoder_get_spacevector_num(instance, 12);
    TEST_ASSERT_EQUAL_UINT32(a12, b);

    b = uz_6ph_spacevector_decoder_get_spacevector_num(instance, 13);
    TEST_ASSERT_EQUAL_UINT32(a13, b);

    b = uz_6ph_spacevector_decoder_get_spacevector_num(instance, 14);
    TEST_ASSERT_EQUAL_UINT32(a14, b);

   

    uz_6ph_spacevector_decoder_hw_read_out1_ExpectAndReturn(TEST_BASE_ADDRESS, a1);
    uz_6ph_spacevector_decoder_hw_read_out2_ExpectAndReturn(TEST_BASE_ADDRESS, a2);
    uz_6ph_spacevector_decoder_hw_read_out3_ExpectAndReturn(TEST_BASE_ADDRESS, a3);
    uz_6ph_spacevector_decoder_hw_read_out4_ExpectAndReturn(TEST_BASE_ADDRESS, a4);
    uz_6ph_spacevector_decoder_hw_read_out5_ExpectAndReturn(TEST_BASE_ADDRESS, a5);
    uz_6ph_spacevector_decoder_hw_read_out6_ExpectAndReturn(TEST_BASE_ADDRESS, a6);
    uz_6ph_spacevector_decoder_hw_read_out7_ExpectAndReturn(TEST_BASE_ADDRESS, a7);
    uz_6ph_spacevector_decoder_hw_read_out8_ExpectAndReturn(TEST_BASE_ADDRESS, a8);
    uz_6ph_spacevector_decoder_hw_read_out9_ExpectAndReturn(TEST_BASE_ADDRESS, a9);
    uz_6ph_spacevector_decoder_hw_read_out10_ExpectAndReturn(TEST_BASE_ADDRESS, a10);
    uz_6ph_spacevector_decoder_hw_read_out11_ExpectAndReturn(TEST_BASE_ADDRESS, a11);
    uz_6ph_spacevector_decoder_hw_read_out12_ExpectAndReturn(TEST_BASE_ADDRESS, a12);
    uz_6ph_spacevector_decoder_hw_read_out13_ExpectAndReturn(TEST_BASE_ADDRESS, a13);
    uz_6ph_spacevector_decoder_hw_read_out14_ExpectAndReturn(TEST_BASE_ADDRESS, a14);

    spacevector_decoder_output testoutput;

    testoutput = uz_6ph_spacevector_decoder_get_all_spacevectors(instance);

    TEST_ASSERT_EQUAL_UINT32(a1, testoutput.sv1);
    TEST_ASSERT_EQUAL_UINT32(a2, testoutput.sv2);
    TEST_ASSERT_EQUAL_UINT32(a3, testoutput.sv3);
    TEST_ASSERT_EQUAL_UINT32(a4, testoutput.sv4);
    TEST_ASSERT_EQUAL_UINT32(a5, testoutput.sv5);
    TEST_ASSERT_EQUAL_UINT32(a6, testoutput.sv6);
    TEST_ASSERT_EQUAL_UINT32(a7, testoutput.sv7);
    TEST_ASSERT_EQUAL_UINT32(a8, testoutput.sv8);
    TEST_ASSERT_EQUAL_UINT32(a9, testoutput.sv9);
    TEST_ASSERT_EQUAL_UINT32(a10, testoutput.sv10);
    TEST_ASSERT_EQUAL_UINT32(a11, testoutput.sv11);
    TEST_ASSERT_EQUAL_UINT32(a12, testoutput.sv12);
    TEST_ASSERT_EQUAL_UINT32(a13, testoutput.sv13);
    TEST_ASSERT_EQUAL_UINT32(a14, testoutput.sv14);

}



#endif // TEST
