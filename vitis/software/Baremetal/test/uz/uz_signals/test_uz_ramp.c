#ifdef TEST

#include "unity.h"
#include "uz_signals.h"
#include "test_assert_with_exception.h"

TEST_FILE("uz_signals_ramp.c")

static struct uz_ramp_config config = {0};

void setUp(void)
{
	config.maximum_slope_per_second = 2.0f;
	config.sample_time_seconds = 0.5f;
	config.initial_value = 0.0f;
}

void tearDown(void)
{
}

void test_uz_ramp_init_asserts_on_negative_slope(void)
{
	config.maximum_slope_per_second = -1.0f;
	TEST_ASSERT_FAIL_ASSERT(uz_ramp_init(config));
}

void test_uz_ramp_init_asserts_on_non_positive_sample_time(void)
{
	config.sample_time_seconds = 0.0f;
	TEST_ASSERT_FAIL_ASSERT(uz_ramp_init(config));
	config.sample_time_seconds = -1.0f;
	TEST_ASSERT_FAIL_ASSERT(uz_ramp_init(config));
}

void test_uz_ramp_asserts_on_null_pointer(void)
{
	TEST_ASSERT_FAIL_ASSERT(uz_ramp(NULL, 1.0f));
}

void test_uz_ramp_increases_with_limited_slope(void)
{
	uz_ramp_t *self = uz_ramp_init(config);

	TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_ramp(self, 3.0f));
	TEST_ASSERT_EQUAL_FLOAT(2.0f, uz_ramp(self, 3.0f));
	TEST_ASSERT_EQUAL_FLOAT(3.0f, uz_ramp(self, 3.0f));
	TEST_ASSERT_EQUAL_FLOAT(3.0f, uz_ramp(self, 3.0f));
}

void test_uz_ramp_decreases_with_limited_slope(void)
{
	config.initial_value = 3.0f;
	uz_ramp_t *self = uz_ramp_init(config);

	TEST_ASSERT_EQUAL_FLOAT(2.0f, uz_ramp(self, -1.0f));
	TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_ramp(self, -1.0f));
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_ramp(self, -1.0f));
	TEST_ASSERT_EQUAL_FLOAT(-1.0f, uz_ramp(self, -1.0f));
}

void test_uz_ramp_passes_reference_if_inside_maximum_step(void)
{
	uz_ramp_t *self = uz_ramp_init(config);

	TEST_ASSERT_EQUAL_FLOAT(0.4f, uz_ramp(self, 0.4f));
	TEST_ASSERT_EQUAL_FLOAT(0.8f, uz_ramp(self, 0.8f));
}

void test_uz_ramp_reset_sets_current_output(void)
{
	uz_ramp_t *self = uz_ramp_init(config);

	TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_ramp(self, 3.0f));
	uz_ramp_reset(self, -2.0f);
	TEST_ASSERT_EQUAL_FLOAT(-1.0f, uz_ramp(self, 3.0f));
}

void test_uz_ramp_with_zero_slope_keeps_output_constant(void)
{
	config.maximum_slope_per_second = 0.0f;
	config.initial_value = 1.5f;
	uz_ramp_t *self = uz_ramp_init(config);

	TEST_ASSERT_EQUAL_FLOAT(1.5f, uz_ramp(self, 5.0f));
	TEST_ASSERT_EQUAL_FLOAT(1.5f, uz_ramp(self, -3.0f));
}

#endif // TEST
