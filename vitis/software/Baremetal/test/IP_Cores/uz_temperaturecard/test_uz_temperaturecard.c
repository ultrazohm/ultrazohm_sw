#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_temperaturecard.h"
#include "mock_uz_temperaturecard_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

#include "uz_temperaturecard.h"

uz_temperaturecard_OneGroup test_channeldata;

void setUp(void)
{
    test_channeldata.temperature[0] = 1.0f;
    test_channeldata.temperature[1] = 2.0f;
    test_channeldata.temperature[2] = 3.0f;
    test_channeldata.temperature[3] = 4.0f;
    test_channeldata.temperature[4] = 5.0f;
    test_channeldata.temperature[5] = 6.0f;
    test_channeldata.temperature[6] = 7.0f;
    test_channeldata.temperature[7] = 8.0f;
    test_channeldata.Channels_Valid[0] = 1;
    test_channeldata.Channels_Valid[1] = 0;
    test_channeldata.Channels_Valid[2] = 0;
    test_channeldata.Channels_Valid[3] = 0;
    test_channeldata.Channels_Valid[4] = 0;
    test_channeldata.Channels_Valid[5] = 0;
    test_channeldata.Channels_Valid[6] = 1;
    test_channeldata.Channels_Valid[7] = 1;
}

void tearDown(void)
{
}

void test_uz_temperaturecard_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement uz_temperaturecard");
}

void test_uz_TempCard_IF_average_temperature_for_valid(void)
{
    float average = uz_TempCard_IF_average_temperature_for_valid(test_channeldata, 0U, 6U);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, average);
    average = uz_TempCard_IF_average_temperature_for_valid(test_channeldata, 1U, 5U);
    TEST_ASSERT_EQUAL_FLOAT(-333.3f, average);
}


#endif // TEST
