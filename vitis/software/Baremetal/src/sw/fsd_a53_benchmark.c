#include "../include/fsd_a53_benchmark.h"

#if UZ_FSD_A53_BENCHMARK_ENABLE
#include "../uz/uz_global_configuration.h"
#include "../include/fsd_mpc_benchmark_stats.h"
#include "../include/uz_platform_state_machine.h"
#include "../uz/uz_SystemTime/uz_AxiTimer64Bit.h"
#include "../uz/uz_HAL.h"
#include <limits.h>
#include <math.h>
#include <stdint.h>

#define FSD_A53_WARMUP 12U
#define FSD_A53_MEASURED 6000U
#define FSD_A53_INPUTS 6U

/* Exact float32 literals used by the qualified R5 timing benchmark. */
static const float samples[FSD_A53_INPUTS][8] = {
    {0.0f, 0.0f, 0.0f, 0.0f, 335.103216f, 48.0f, 0.0f, 11.3137085f},
    {2.1f, -1.05f, -1.05f, 1.04719745f, 335.103216f, 48.0f, 0.0f, 11.3137085f},
    {4.5f, -2.1f, -2.4f, 6.28318521f, 900.0f, 36.0f, -4.0f, 7.0f},
    {-3.2f, 1.7f, 1.5f, 0.13f, -335.103216f, 48.0f, -2.0f, -5.0f},
    {1.1f, -0.2f, -0.9f, 1.07f, 1800.0f, 25.0f, -6.0f, 6.0f},
    {0.00133354962f, 0.000567176862f, -0.00190072648f,
        3.14159265f, 0.0f, 48.0f, 0.0f, 0.0f}
};

static struct fsd_mpc_benchmark_stats roundtrip;
static struct fsd_mpc_benchmark_stats a53_compute;
static uint32_t completed_steps;
static uint64_t pending_start;
static uint64_t init_roundtrip_ticks;
static uint64_t init_a53_ticks;
static bool initialized;
static bool pending;
static bool failed;
static uint32_t failed_calls;
static volatile bool report_ready;
static bool report_done;
static int32_t failure_code;
static uint32_t yang_path_histogram[7];
static uint32_t yang_qp_histogram[13];
static uint64_t yang_qp_sum;

static uint32_t qp_solves(void) {
    uint32_t paths = UZ_FSD_A53_BENCHMARK_VARIANT < 3U ? 6U : 1U;
    if (UZ_FSD_A53_BENCHMARK_VARIANT >= 6U) {
        return 0U; /* Per-step variable. */
    }
    return (UZ_FSD_A53_BENCHMARK_VARIANT % 3U) == 2U ? 2U * paths : paths;
}

static uint32_t narrow(uint64_t value) {
    return value > UINT32_MAX ? UINT32_MAX : (uint32_t)value;
}

static void stop_with_error(int32_t code) {
    if (!failed) {
        failed_calls++;
    }
    failed = true;
    pending = false;
    failure_code = code;
    report_ready = true;
}

bool fsd_a53_benchmark_prepare(volatile struct RPU_to_APU_user_data_t *request) {
    uint32_t index;
    request->fsd_kind = UZ_FSD_A53_REQUEST_NONE;
    if (failed || report_ready || pending ||
        ultrazohm_state_machine_get_state() != idle_state) {
        return false;
    }
    if (roundtrip.timer_frequency_hz == 0U) {
        fsd_mpc_benchmark_stats_init(&roundtrip, UZ_AXI_TIMER_CLOCK_FREQ);
        roundtrip.qp_solves_per_step = qp_solves();
        if (roundtrip.timer_frequency_hz == 0U) {
            stop_with_error(-1);
            return false;
        }
    }
    index = initialized ? completed_steps % FSD_A53_INPUTS : 0U;
    for (uint32_t i = 0U; i < 8U; ++i) {
        if (!isfinite(samples[index][i])) {
            stop_with_error(-2);
            return false;
        }
        request->fsd_input[i] = samples[index][i];
    }
    request->fsd_variant = UZ_FSD_A53_BENCHMARK_VARIANT;
    request->fsd_sequence = initialized ? completed_steps + 1U : 0U;
    request->fsd_kind = initialized ? UZ_FSD_A53_REQUEST_STEP :
        UZ_FSD_A53_REQUEST_INIT;
    pending_start = uz_AxiTimer64Bit_ReadValue64Bit();
    pending = true;
    return true;
}

void fsd_a53_benchmark_complete(
    const volatile struct APU_to_RPU_user_data_t *response,
    int acknowledgment_status) {
    uint64_t end_tick;
    uint32_t expected_kind;
    uint32_t expected_sequence;
    if (!pending) {
        return;
    }
    end_tick = uz_AxiTimer64Bit_ReadValue64Bit();
    expected_kind = initialized ? UZ_FSD_A53_REQUEST_STEP :
        UZ_FSD_A53_REQUEST_INIT;
    expected_sequence = initialized ? completed_steps + 1U : 0U;
    if (acknowledgment_status != 0) {
        stop_with_error(-3);
        return;
    }
    if (response->fsd_kind != expected_kind ||
        response->fsd_sequence != expected_sequence) {
        stop_with_error(-4);
        return;
    }
    if (response->fsd_status != 0U || response->fsd_timer_hz == 0U ||
        response->fsd_update_count != expected_sequence) {
        stop_with_error(-5);
        return;
    }
    for (uint32_t i = 0U; i < 3U; ++i) {
        float duty = response->fsd_duty[i];
        if (!isfinite(duty) || duty < 0.0f || duty > 1.0f) {
            stop_with_error(-6);
            return;
        }
    }
    if (!initialized) {
        initialized = true;
        init_roundtrip_ticks = end_tick - pending_start;
        init_a53_ticks = response->fsd_compute_ticks;
        fsd_mpc_benchmark_stats_init(&a53_compute, response->fsd_timer_hz);
    } else {
        if (a53_compute.timer_frequency_hz != response->fsd_timer_hz) {
            stop_with_error(-7);
            return;
        }
        if (completed_steps >= FSD_A53_WARMUP) {
			if (UZ_FSD_A53_BENCHMARK_VARIANT >= 6U) {
				uint32_t paths = 0U;
				for (uint32_t path = 0U; path < 6U; ++path) {
					paths += (response->fsd_suitable_mask >> path) & 1U;
				}
				if (response->fsd_formulation_count != 6U || paths == 0U ||
					response->fsd_qp_solve_count > 12U) {
					stop_with_error(-9);
					return;
				}
				yang_path_histogram[paths]++;
				yang_qp_histogram[response->fsd_qp_solve_count]++;
				yang_qp_sum += response->fsd_qp_solve_count;
			}
            fsd_mpc_benchmark_stats_add(&roundtrip, pending_start, end_tick);
            fsd_mpc_benchmark_stats_add(&a53_compute, 0U,
                response->fsd_compute_ticks);
            if (roundtrip.failed || a53_compute.failed) {
                stop_with_error(-8);
                return;
            }
        }
        completed_steps++;
        if (completed_steps == FSD_A53_WARMUP + FSD_A53_MEASURED) {
            report_ready = true;
        }
    }
    pending = false;
}

void fsd_a53_benchmark_report_once(void) {
    if (!report_ready || report_done) {
        return;
    }
    report_done = true;
    uz_printf("FSD A53 variant=%lu qp=%lu status=%ld measured=%lu failed_calls=%lu\r\n",
        (unsigned long)UZ_FSD_A53_BENCHMARK_VARIANT,
        (unsigned long)qp_solves(), (long)failure_code,
        (unsigned long)roundtrip.valid_samples,
        (unsigned long)failed_calls);
    uz_printf("R5_timer_hz=%lu A53_timer_hz=%lu init_roundtrip_ticks=%lu init_A53_ticks=%lu\r\n",
        (unsigned long)narrow(roundtrip.timer_frequency_hz),
        (unsigned long)narrow(a53_compute.timer_frequency_hz),
        (unsigned long)narrow(init_roundtrip_ticks),
        (unsigned long)narrow(init_a53_ticks));
    if (roundtrip.valid_samples == 0U) {
        return;
    }
    uz_printf("R5_roundtrip_ticks min=%lu mean=%lu max=%lu p95_us=%lu p99_us=%lu over100=%lu\r\n",
        (unsigned long)narrow(roundtrip.min_ticks),
        (unsigned long)narrow(fsd_mpc_benchmark_mean_ticks(&roundtrip)),
        (unsigned long)narrow(roundtrip.max_ticks),
        (unsigned long)fsd_mpc_benchmark_percentile_upper_us(&roundtrip, 95U),
        (unsigned long)fsd_mpc_benchmark_percentile_upper_us(&roundtrip, 99U),
        (unsigned long)roundtrip.over_100us_samples);
    uz_printf("A53_compute_ticks min=%lu mean=%lu max=%lu p95_us=%lu p99_us=%lu\r\n",
        (unsigned long)narrow(a53_compute.min_ticks),
        (unsigned long)narrow(fsd_mpc_benchmark_mean_ticks(&a53_compute)),
        (unsigned long)narrow(a53_compute.max_ticks),
        (unsigned long)fsd_mpc_benchmark_percentile_upper_us(&a53_compute, 95U),
        (unsigned long)fsd_mpc_benchmark_percentile_upper_us(&a53_compute, 99U));
	if (UZ_FSD_A53_BENCHMARK_VARIANT >= 6U) {
		uz_printf("Yang formulations=6 qp_sum=%lu paths_0_to_6:",
			(unsigned long)narrow(yang_qp_sum));
		for (uint32_t i = 0U; i < 7U; ++i) {
			uz_printf(" %lu", (unsigned long)yang_path_histogram[i]);
		}
		uz_printf("\r\nYang qp_0_to_12:");
		for (uint32_t i = 0U; i < 13U; ++i) {
			uz_printf(" %lu", (unsigned long)yang_qp_histogram[i]);
		}
		uz_printf("\r\n");
	}
}
#endif
