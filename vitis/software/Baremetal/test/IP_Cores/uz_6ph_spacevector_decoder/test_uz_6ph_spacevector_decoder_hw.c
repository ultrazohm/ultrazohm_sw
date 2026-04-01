#ifdef TEST

#include "unity.h"

#include "uz_6ph_spacevector_decoder_hw.h"
#include <stdint.h>
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_6ph_spacevector_decoder_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_6ph_spacevector_decoder_hw_read_out1(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+out1_Data_uz_6ph_sv_decode_ip,expect_val);
    uint32_t val_read=uz_6ph_spacevector_decoder_hw_read_out1(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_6ph_spacevector_decoder_hw_read_out2(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+out2_Data_uz_6ph_sv_decode_ip,expect_val);
    uint32_t val_read=uz_6ph_spacevector_decoder_hw_read_out2(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_6ph_spacevector_decoder_hw_read_out3(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+out3_Data_uz_6ph_sv_decode_ip,expect_val);
    uint32_t val_read=uz_6ph_spacevector_decoder_hw_read_out3(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_6ph_spacevector_decoder_hw_read_out4(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+out4_Data_uz_6ph_sv_decode_ip,expect_val);
    uint32_t val_read=uz_6ph_spacevector_decoder_hw_read_out4(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_6ph_spacevector_decoder_hw_read_out5(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+out5_Data_uz_6ph_sv_decode_ip,expect_val);
    uint32_t val_read=uz_6ph_spacevector_decoder_hw_read_out5(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_6ph_spacevector_decoder_hw_read_out6(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+out6_Data_uz_6ph_sv_decode_ip,expect_val);
    uint32_t val_read=uz_6ph_spacevector_decoder_hw_read_out6(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_6ph_spacevector_decoder_hw_read_out7(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+out7_Data_uz_6ph_sv_decode_ip,expect_val);
    uint32_t val_read=uz_6ph_spacevector_decoder_hw_read_out7(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_6ph_spacevector_decoder_hw_read_out8(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+out8_Data_uz_6ph_sv_decode_ip,expect_val);
    uint32_t val_read=uz_6ph_spacevector_decoder_hw_read_out8(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_6ph_spacevector_decoder_hw_read_out9(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+out9_Data_uz_6ph_sv_decode_ip,expect_val);
    uint32_t val_read=uz_6ph_spacevector_decoder_hw_read_out9(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_6ph_spacevector_decoder_hw_read_out10(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+out10_Data_uz_6ph_sv_decode_ip,expect_val);
    uint32_t val_read=uz_6ph_spacevector_decoder_hw_read_out10(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_6ph_spacevector_decoder_hw_read_out11(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+out11_Data_uz_6ph_sv_decode_ip,expect_val);
    uint32_t val_read=uz_6ph_spacevector_decoder_hw_read_out11(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_6ph_spacevector_decoder_hw_read_out12(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+out12_Data_uz_6ph_sv_decode_ip,expect_val);
    uint32_t val_read=uz_6ph_spacevector_decoder_hw_read_out12(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_6ph_spacevector_decoder_hw_read_out13(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+out13_Data_uz_6ph_sv_decode_ip,expect_val);
    uint32_t val_read=uz_6ph_spacevector_decoder_hw_read_out13(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_6ph_spacevector_decoder_hw_read_out14(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+out14_Data_uz_6ph_sv_decode_ip,expect_val);
    uint32_t val_read=uz_6ph_spacevector_decoder_hw_read_out14(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}




#endif // TEST
