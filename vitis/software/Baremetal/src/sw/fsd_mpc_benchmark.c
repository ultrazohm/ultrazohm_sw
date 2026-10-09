#include "../include/fsd_mpc_benchmark.h"
#include "../uz/uz_global_configuration.h"

#if UZ_FSD_BENCHMARK_ENABLE
#include "../uz/uz_SystemTime/uz_AxiTimer64Bit.h"
#include "../uz/uz_HAL.h"
#include <limits.h>
#include <math.h>
#include <stddef.h>

#define FSD_BENCHMARK_WARMUP_STEPS 12U
#define FSD_BENCHMARK_MEASURED_STEPS 6000U
#define FSD_BENCHMARK_INPUT_COUNT 6U

/* Frozen JSON SHA-256: 78f4870515e6af85204f02269a25dc927b76ab14a1d1a136a06b489d9bb7ff45.
 * First SI/exhaustive/SVM/SimplexFace record. These are synthetic samples. */
static const struct uz_fsd_mpc_input samples[FSD_BENCHMARK_INPUT_COUNT] = {
	{0.0f, 0.0f, 0.0f, 0.0f, 335.103216f, 48.0f, 0.0f, 11.3137085f},
	{2.1f, -1.05f, -1.05f, 1.04719745f, 335.103216f, 48.0f,
		0.0f, 11.3137085f},
	{4.5f, -2.1f, -2.4f, 6.28318521f, 900.0f, 36.0f, -4.0f, 7.0f},
	{-3.2f, 1.7f, 1.5f, 0.13f, -335.103216f, 48.0f, -2.0f, -5.0f},
	{1.1f, -0.2f, -0.9f, 1.07f, 1800.0f, 25.0f, -6.0f, 6.0f},
	{0.00133354962f, 0.000567176862f, -0.00190072648f,
		3.14159265f, 0.0f, 48.0f, 0.0f, 0.0f}
};

static struct fsd_mpc_benchmark_stats timing;
static uint32_t next_input = 0U;
static uint32_t completed_steps = 0U;
static bool report_done = false;
static volatile bool report_ready = false;

static bool valid_input(const struct uz_fsd_mpc_input *input) {
	return isfinite(input->ia) && isfinite(input->ib) &&
		isfinite(input->ic) && isfinite(input->theta_e) &&
		isfinite(input->omega_e) && isfinite(input->v_dc) &&
		input->v_dc > 0.0f && isfinite(input->id_ref) &&
		isfinite(input->iq_ref);
}

static bool valid_output(const struct uz_fsd_mpc_output *output,
	float period_s) {
	struct uz_fsd_mpc_schedule schedule;
	return output->status == UZ_FSD_MPC_OK &&
		isfinite(output->duty_a) && output->duty_a >= 0.0f &&
		output->duty_a <= 1.0f && isfinite(output->duty_b) &&
		output->duty_b >= 0.0f && output->duty_b <= 1.0f &&
		isfinite(output->duty_c) && output->duty_c >= 0.0f &&
		output->duty_c <= 1.0f &&
		uz_fsd_mpc_schedule(&output->calculated, period_s, &schedule) ==
		UZ_FSD_MPC_OK;
}

static struct uz_fsd_mpc_config selected_config(void) {
	struct uz_fsd_mpc_config config = {
		.resistance_ohm = 0.51f,
		.inductance_d_h = 0.002f,
		.inductance_q_h = 0.002f,
		.flux_pm_wb = 0.042f,
		.period_s = 0.0001f,
		.lambda = 10.0f,
		.coordinates = UZ_FSD_MPC_SI,
		.selector = UZ_FSD_MPC_EXHAUSTIVE,
		.modulation = UZ_FSD_MPC_SVM,
		.solver = UZ_FSD_MPC_SIMPLEX_FACE
	};
#if UZ_FSD_BENCHMARK_VARIANT >= 3U
	config.selector = UZ_FSD_MPC_DEADBEAT;
#endif
#if (UZ_FSD_BENCHMARK_VARIANT % 3U) == 1U
	config.modulation = UZ_FSD_MPC_IFT;
#elif (UZ_FSD_BENCHMARK_VARIANT % 3U) == 2U
	config.modulation = UZ_FSD_MPC_VFT;
#endif
	return config;
}

static uint32_t qp_solves_per_step(void) {
	uint32_t paths = UZ_FSD_BENCHMARK_VARIANT < 3U ? 6U : 1U;
	return (UZ_FSD_BENCHMARK_VARIANT % 3U) == 2U ? 2U * paths : paths;
}

static uint32_t narrow_ticks(uint64_t ticks) {
	return ticks > UINT32_MAX ? UINT32_MAX : (uint32_t)ticks;
}

uz_fsd_mpc_t *fsd_mpc_benchmark_init(void) {
	struct uz_fsd_mpc_output preload;
	struct uz_fsd_mpc_config config = selected_config();
	uz_fsd_mpc_t *controller;
	uint64_t start_tick;
	uint64_t end_tick;
	uint64_t overhead = UINT64_MAX;
	fsd_mpc_benchmark_stats_init(&timing, UZ_AXI_TIMER_CLOCK_FREQ);
	timing.qp_solves_per_step = qp_solves_per_step();
	if (timing.timer_frequency_hz == 0U) {
		timing.failed = true;
		timing.failure_status = -1;
		report_ready = true;
		return NULL;
	}
	for (uint32_t index = 0U; index < FSD_BENCHMARK_INPUT_COUNT; ++index) {
		if (!valid_input(&samples[index])) {
			timing.failed = true;
			timing.failure_status = -2;
			report_ready = true;
			return NULL;
		}
	}
	for (uint32_t index = 0U; index < 64U; ++index) {
		start_tick = uz_AxiTimer64Bit_ReadValue64Bit();
		end_tick = uz_AxiTimer64Bit_ReadValue64Bit();
		if (end_tick - start_tick < overhead) {
			overhead = end_tick - start_tick;
		}
	}
	timing.read_pair_overhead_ticks = overhead;
	start_tick = uz_AxiTimer64Bit_ReadValue64Bit();
	controller = uz_fsd_mpc_init(config, &samples[0], &preload);
	end_tick = uz_AxiTimer64Bit_ReadValue64Bit();
	timing.preload_ticks = end_tick - start_tick;
	if (controller == NULL || !valid_output(&preload, config.period_s)) {
		timing.failed = true;
		timing.failure_status = controller == NULL ? -3 : (int32_t)preload.status;
		report_ready = true;
		return NULL;
	}
	next_input = 0U;
	completed_steps = 0U;
	report_done = false;
	report_ready = false;
	return controller;
}

void fsd_mpc_benchmark_step(uz_fsd_mpc_t *controller) {
	struct uz_fsd_mpc_output output;
	const struct uz_fsd_mpc_input *input;
	uz_fsd_mpc_status_t status;
	uint64_t start_tick;
	uint64_t end_tick;
	if (controller == NULL || timing.failed || timing.finished) {
		return;
	}
	input = &samples[next_input];
	if (!valid_input(input)) {
		timing.failed = true;
		timing.failure_status = -2;
		timing.failed_sample_index = completed_steps;
		report_ready = true;
		return;
	}
	start_tick = uz_AxiTimer64Bit_ReadValue64Bit();
	status = uz_fsd_mpc_step(controller, input, &output, NULL);
	end_tick = uz_AxiTimer64Bit_ReadValue64Bit();
	if (status != UZ_FSD_MPC_OK ||
		!valid_output(&output, 0.0001f)) {
		timing.failed = true;
		timing.failure_status = status == UZ_FSD_MPC_OK ?
			-4 : (int32_t)status;
		timing.failed_sample_index = completed_steps;
		report_ready = true;
		return;
	}
	if (completed_steps >= FSD_BENCHMARK_WARMUP_STEPS) {
		fsd_mpc_benchmark_stats_add(&timing, start_tick, end_tick);
	}
	completed_steps++;
	next_input = (next_input + 1U) % FSD_BENCHMARK_INPUT_COUNT;
	if (completed_steps >= FSD_BENCHMARK_WARMUP_STEPS +
		FSD_BENCHMARK_MEASURED_STEPS || timing.failed) {
		timing.finished = !timing.failed;
		report_ready = true;
	}
}

const struct fsd_mpc_benchmark_stats *fsd_mpc_benchmark_get_stats(void) {
	return &timing;
}

void fsd_mpc_benchmark_report_once(void) {
	if (report_done || !report_ready) {
		return;
	}
	report_done = true;
	uz_printf("FSD benchmark variant=%lu status=%ld samples=%lu failed_step=%lu\r\n",
		(unsigned long)UZ_FSD_BENCHMARK_VARIANT,
		(long)timing.failure_status, (unsigned long)timing.valid_samples,
		(unsigned long)timing.failed_sample_index);
	uz_printf("timer_hz=%lu init_ticks=%lu read_pair_ticks=%lu qp_solves=%lu\r\n",
		(unsigned long)narrow_ticks(timing.timer_frequency_hz),
		(unsigned long)narrow_ticks(timing.preload_ticks),
		(unsigned long)narrow_ticks(timing.read_pair_overhead_ticks),
		(unsigned long)timing.qp_solves_per_step);
	if (timing.valid_samples > 0U) {
		uz_printf("raw_ticks min=%lu max=%lu mean=%lu over_100us=%lu\r\n",
			(unsigned long)narrow_ticks(timing.min_ticks),
			(unsigned long)narrow_ticks(timing.max_ticks),
			(unsigned long)narrow_ticks(fsd_mpc_benchmark_mean_ticks(&timing)),
			(unsigned long)timing.over_100us_samples);
		uz_printf("histogram_p95_bin_us=%lu p99_bin_us=%lu (100=overflow)\r\n",
			(unsigned long)fsd_mpc_benchmark_percentile_upper_us(&timing, 95U),
			(unsigned long)fsd_mpc_benchmark_percentile_upper_us(&timing, 99U));
	}
}
#endif
