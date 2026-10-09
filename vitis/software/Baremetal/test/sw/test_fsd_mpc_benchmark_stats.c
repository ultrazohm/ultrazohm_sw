#ifdef TEST
#include "unity.h"
#include "fsd_mpc_benchmark_stats.h"
#include "uz_global_configuration.h"
#include <stdint.h>

void setUp(void) {}
void tearDown(void) {}

void test_benchmark_mode_is_disabled_by_default(void) {
	TEST_ASSERT_EQUAL_UINT32(0U, UZ_FSD_BENCHMARK_ENABLE);
	TEST_ASSERT_EQUAL_UINT32(0U, UZ_FSD_BENCHMARK_VARIANT);
}

void test_raw_ticks_mean_histogram_and_percentiles(void) {
	struct fsd_mpc_benchmark_stats stats;
	fsd_mpc_benchmark_stats_init(&stats, 100000000U);
	stats.read_pair_overhead_ticks = 20U;
	fsd_mpc_benchmark_stats_add(&stats, 100U, 600U);   /* 5 us */
	fsd_mpc_benchmark_stats_add(&stats, 100U, 1100U);  /* 10 us */
	fsd_mpc_benchmark_stats_add(&stats, 100U, 12100U); /* 120 us */
	TEST_ASSERT_EQUAL_UINT32(3U, stats.valid_samples);
	TEST_ASSERT_EQUAL_UINT32(1U, stats.over_100us_samples);
	TEST_ASSERT_EQUAL_UINT64(500U, stats.min_ticks);
	TEST_ASSERT_EQUAL_UINT64(12000U, stats.max_ticks);
	TEST_ASSERT_EQUAL_UINT64(4500U, fsd_mpc_benchmark_mean_ticks(&stats));
	TEST_ASSERT_EQUAL_UINT32(11U,
		fsd_mpc_benchmark_percentile_upper_us(&stats, 50U));
	TEST_ASSERT_EQUAL_UINT32(100U,
		fsd_mpc_benchmark_percentile_upper_us(&stats, 95U));
}

void test_unsigned_delta_covers_timer_wrap(void) {
	struct fsd_mpc_benchmark_stats stats;
	fsd_mpc_benchmark_stats_init(&stats, 100000000U);
	fsd_mpc_benchmark_stats_add(&stats, UINT64_MAX - 4U, 5U);
	TEST_ASSERT_EQUAL_UINT64(10U, stats.max_ticks);
	TEST_ASSERT_EQUAL_UINT32(1U, stats.valid_samples);
}

void test_empty_statistics_have_zero_mean_and_percentiles(void) {
	struct fsd_mpc_benchmark_stats stats;
	fsd_mpc_benchmark_stats_init(&stats, 100000000U);
	TEST_ASSERT_EQUAL_UINT64(0U, fsd_mpc_benchmark_mean_ticks(&stats));
	TEST_ASSERT_EQUAL_UINT32(0U,
		fsd_mpc_benchmark_percentile_upper_us(&stats, 99U));
}

void test_reinitialization_clears_samples_and_failure(void) {
	struct fsd_mpc_benchmark_stats stats;
	fsd_mpc_benchmark_stats_init(&stats, 100000000U);
	fsd_mpc_benchmark_stats_add(&stats, 0U, 500U);
	stats.failed = true;
	stats.failure_status = -7;
	fsd_mpc_benchmark_stats_init(&stats, 50000000U);
	TEST_ASSERT_EQUAL_UINT32(0U, stats.valid_samples);
	TEST_ASSERT_EQUAL_UINT32(0U, stats.histogram[5]);
	TEST_ASSERT_EQUAL_UINT32(0U, stats.failed);
	TEST_ASSERT_EQUAL_UINT32(0U, stats.failure_status);
	TEST_ASSERT_EQUAL_UINT64(50000000U, stats.timer_frequency_hz);
}

void test_accumulator_overflow_sets_failure(void) {
	struct fsd_mpc_benchmark_stats stats;
	fsd_mpc_benchmark_stats_init(&stats, 100000000U);
	stats.sum_ticks = UINT64_MAX;
	fsd_mpc_benchmark_stats_add(&stats, 0U, 1U);
	TEST_ASSERT_EQUAL_UINT32(1U, stats.failed);
	TEST_ASSERT_EQUAL_UINT32(0U, stats.valid_samples);
}
#endif
