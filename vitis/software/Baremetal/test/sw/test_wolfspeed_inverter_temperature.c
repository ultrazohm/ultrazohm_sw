#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "wolfspeed_inverter_temperature.h"
#include <math.h>

void setUp(void) {}
void tearDown(void) {}

void test_wolfspeed_inverter_temperature_polynomial(void)
{
	TEST_ASSERT_FLOAT_WITHIN(1.0e-3f, 102.966875f, wolfspeed_inverter_temperature_from_duty_ratio(0.5f));
	TEST_ASSERT_TRUE(isfinite(wolfspeed_inverter_temperature_from_duty_ratio(0.05f)));
	TEST_ASSERT_TRUE(isfinite(wolfspeed_inverter_temperature_from_duty_ratio(0.95f)));
}

void test_wolfspeed_inverter_temperature_rejects_invalid_ratio(void)
{
	TEST_ASSERT_TRUE(isnan(wolfspeed_inverter_temperature_from_duty_ratio(0.049f)));
	TEST_ASSERT_TRUE(isnan(wolfspeed_inverter_temperature_from_duty_ratio(0.951f)));
	TEST_ASSERT_TRUE(isnan(wolfspeed_inverter_temperature_from_duty_ratio(NAN)));
}

#endif
