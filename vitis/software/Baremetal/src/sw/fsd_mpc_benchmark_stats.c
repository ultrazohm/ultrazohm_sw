#include "../include/fsd_mpc_benchmark_stats.h"
#include <limits.h>
#include <stddef.h>
#include <string.h>

void fsd_mpc_benchmark_stats_init(struct fsd_mpc_benchmark_stats *stats,
	uint64_t timer_frequency_hz) {
	if (stats == NULL) {
		return;
	}
	memset(stats, 0, sizeof(*stats));
	stats->timer_frequency_hz = timer_frequency_hz;
	stats->min_ticks = UINT64_MAX;
}

void fsd_mpc_benchmark_stats_add(struct fsd_mpc_benchmark_stats *stats,
	uint64_t start_tick, uint64_t end_tick) {
	uint64_t ticks;
	uint64_t whole_us;
	uint32_t bin;
	if (stats == NULL || stats->timer_frequency_hz == 0U ||
		stats->valid_samples == UINT32_MAX) {
		return;
	}
	/* Unsigned subtraction also covers a 64-bit timer wrap. */
	ticks = end_tick - start_tick;
	if (ticks < stats->min_ticks) {
		stats->min_ticks = ticks;
	}
	if (ticks > stats->max_ticks) {
		stats->max_ticks = ticks;
	}
	if (UINT64_MAX - stats->sum_ticks < ticks) {
		stats->failed = true;
		stats->failure_status = -1;
		return;
	}
	stats->sum_ticks += ticks;
	stats->valid_samples++;
	/* Divide before multiplying so the conversion cannot overflow. */
	whole_us = (ticks / stats->timer_frequency_hz) * 1000000U;
	whole_us += ((ticks % stats->timer_frequency_hz) * 1000000U) /
		stats->timer_frequency_hz;
	if (whole_us >= 100U) {
		stats->over_100us_samples++;
		bin = 100U;
	} else {
		bin = (uint32_t)whole_us;
	}
	stats->histogram[bin]++;
}

uint64_t fsd_mpc_benchmark_mean_ticks(
	const struct fsd_mpc_benchmark_stats *stats) {
	return (stats == NULL || stats->valid_samples == 0U) ? 0U :
		stats->sum_ticks / stats->valid_samples;
}

uint32_t fsd_mpc_benchmark_percentile_upper_us(
	const struct fsd_mpc_benchmark_stats *stats, uint32_t percentile) {
	uint32_t cumulative = 0U;
	uint32_t rank;
	if (stats == NULL || stats->valid_samples == 0U ||
		percentile == 0U || percentile > 100U) {
		return 0U;
	}
	rank = (uint32_t)(((uint64_t)stats->valid_samples * percentile + 99U) /
		100U);
	for (uint32_t bin = 0U; bin < FSD_MPC_BENCHMARK_HISTOGRAM_BINS; ++bin) {
		cumulative += stats->histogram[bin];
		if (cumulative >= rank) {
			return bin == 100U ? 100U : bin + 1U;
		}
	}
	return 100U;
}
