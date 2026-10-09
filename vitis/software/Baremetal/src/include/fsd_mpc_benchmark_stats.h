#ifndef FSD_MPC_BENCHMARK_STATS_H
#define FSD_MPC_BENCHMARK_STATS_H

#include <stdbool.h>
#include <stdint.h>

#define FSD_MPC_BENCHMARK_HISTOGRAM_BINS 101U

struct fsd_mpc_benchmark_stats {
	uint64_t timer_frequency_hz;
	uint64_t preload_ticks;
	uint64_t read_pair_overhead_ticks;
	uint64_t min_ticks;
	uint64_t max_ticks;
	uint64_t sum_ticks;
	uint32_t histogram[FSD_MPC_BENCHMARK_HISTOGRAM_BINS];
	uint32_t valid_samples;
	uint32_t over_100us_samples;
	bool failed;
	bool finished;
	int32_t failure_status;
	uint32_t failed_sample_index;
	uint32_t qp_solves_per_step;
};

void fsd_mpc_benchmark_stats_init(struct fsd_mpc_benchmark_stats *stats,
	uint64_t timer_frequency_hz);
void fsd_mpc_benchmark_stats_add(struct fsd_mpc_benchmark_stats *stats,
	uint64_t start_tick, uint64_t end_tick);
uint64_t fsd_mpc_benchmark_mean_ticks(
	const struct fsd_mpc_benchmark_stats *stats);
/* Bins 0..99 return their upper us edge; 100 means >=100 us, not an upper bound. */
uint32_t fsd_mpc_benchmark_percentile_upper_us(
	const struct fsd_mpc_benchmark_stats *stats, uint32_t percentile);

#endif
