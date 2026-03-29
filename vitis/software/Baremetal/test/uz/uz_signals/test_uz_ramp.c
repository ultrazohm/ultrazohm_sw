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

void test_uz_ramp_step_asserts_on_null_pointer(void)
{
	TEST_ASSERT_FAIL_ASSERT(uz_ramp_step(NULL, 1.0f));
}

void test_uz_ramp_reset_asserts_on_null_pointer(void)
{
	TEST_ASSERT_FAIL_ASSERT(uz_ramp_reset(NULL));
}

void test_uz_ramp_set_to_value_instant_asserts_on_null_pointer(void)
{
	TEST_ASSERT_FAIL_ASSERT(uz_ramp_set_to_value_instant(NULL, 1.0f));
}

void test_uz_ramp_init_sets_initial_value(void)
{
	config.initial_value = 1.5f;
	uz_ramp_t *self = uz_ramp_init(config);

	TEST_ASSERT_EQUAL_FLOAT(1.5f, uz_ramp_step(self, 1.5f));
}

void test_uz_ramp_step_increases_with_limited_slope(void)
{
	uz_ramp_t *self = uz_ramp_init(config);

	TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_ramp_step(self, 3.0f));
	TEST_ASSERT_EQUAL_FLOAT(2.0f, uz_ramp_step(self, 3.0f));
	TEST_ASSERT_EQUAL_FLOAT(3.0f, uz_ramp_step(self, 3.0f));
	TEST_ASSERT_EQUAL_FLOAT(3.0f, uz_ramp_step(self, 3.0f));
}

void test_uz_ramp_step_decreases_with_limited_slope(void)
{
	config.initial_value = 3.0f;
	uz_ramp_t *self = uz_ramp_init(config);

	TEST_ASSERT_EQUAL_FLOAT(2.0f, uz_ramp_step(self, -1.0f));
	TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_ramp_step(self, -1.0f));
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_ramp_step(self, -1.0f));
	TEST_ASSERT_EQUAL_FLOAT(-1.0f, uz_ramp_step(self, -1.0f));
}

void test_uz_ramp_step_passes_reference_if_inside_maximum_step(void)
{
	uz_ramp_t *self = uz_ramp_init(config);

	TEST_ASSERT_EQUAL_FLOAT(0.4f, uz_ramp_step(self, 0.4f));
	TEST_ASSERT_EQUAL_FLOAT(0.8f, uz_ramp_step(self, 0.8f));
}

void test_uz_ramp_sets_current_output(void)
{
	uz_ramp_t *self = uz_ramp_init(config);

	TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_ramp_step(self, 3.0f));
	uz_ramp_set_to_value_instant(self, -2.0f);
	TEST_ASSERT_EQUAL_FLOAT(-1.0f, uz_ramp_step(self, 3.0f));
}

void test_uz_ramp_reset_sets_current_output_to_zero(void)
{
	config.initial_value = 3.0f;
	uz_ramp_t *self = uz_ramp_init(config);

	TEST_ASSERT_EQUAL_FLOAT(2.0f, uz_ramp_step(self, -1.0f));
	uz_ramp_reset(self);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_ramp_step(self, 0.0f));
}

void test_uz_ramp_step_with_zero_slope_keeps_output_constant(void)
{
	config.maximum_slope_per_second = 0.0f;
	config.initial_value = 1.5f;
	uz_ramp_t *self = uz_ramp_init(config);

	TEST_ASSERT_EQUAL_FLOAT(1.5f, uz_ramp_step(self, 5.0f));
	TEST_ASSERT_EQUAL_FLOAT(1.5f, uz_ramp_step(self, -3.0f));
}

#endif // TEST
