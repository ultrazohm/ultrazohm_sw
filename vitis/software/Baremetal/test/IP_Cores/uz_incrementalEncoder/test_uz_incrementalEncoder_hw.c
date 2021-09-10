#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "IncreEncoder_V24_ip_addr.h"
#define BASE_ADDRESS 0x00000000FU // random hex value that represents a fictional base address

#include "uz_incrementalEncoder_hw.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_incrementalEncoder_hw_set_timer_fpga_ms(void)
{
    uint32_t expected=10;
    uz_axi_write_uint32_Expect(BASE_ADDRESS+Timer_FPGA_ms_AXI4_Data_IncreEncoder_V24_ip,expected);
    uz_incrementalEncoder_hw_set_timer_fpga_ms(BASE_ADDRESS,expected);
}


void test_uz_incrementalEncoder_hw_set_pi2_inc(void)
{
    uint32_t expected=1123;
    uz_axi_write_uint32_Expect(BASE_ADDRESS+PI2_Inc_AXI4_Data_IncreEncoder_V24_ip,expected);
    uz_incrementalEncoder_hw_set_pi2_inc(BASE_ADDRESS,expected);
}

#endif // TEST
