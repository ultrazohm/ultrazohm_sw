#include "fsd_a53_worker.h"
#include "uz_fsd_mpc.h"
#include "xtime_l.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static const float samples[6][8] = {
    {0.0f, 0.0f, 0.0f, 0.0f, 335.103216f, 48.0f, 0.0f, 11.3137085f},
    {2.1f, -1.05f, -1.05f, 1.04719745f, 335.103216f, 48.0f, 0.0f, 11.3137085f},
    {4.5f, -2.1f, -2.4f, 6.28318521f, 900.0f, 36.0f, -4.0f, 7.0f},
    {-3.2f, 1.7f, 1.5f, 0.13f, -335.103216f, 48.0f, -2.0f, -5.0f},
    {1.1f, -0.2f, -0.9f, 1.07f, 1800.0f, 25.0f, -6.0f, 6.0f},
    {0.00133354962f, 0.000567176862f, -0.00190072648f,
        3.14159265f, 0.0f, 48.0f, 0.0f, 0.0f}
};

static void check(int condition, const char *message) {
    if (!condition) { fprintf(stderr, "%s\n", message); exit(2); }
}

static struct uz_fsd_mpc_input input_from(const float sample[8]) {
    return (struct uz_fsd_mpc_input) {sample[0], sample[1], sample[2],
        sample[3], sample[4], sample[5], sample[6], sample[7]};
}

static struct uz_fsd_mpc_config config_for_variant(void) {
    struct uz_fsd_mpc_config config = {
        .resistance_ohm = .51f, .inductance_d_h = .002f,
        .inductance_q_h = .002f, .flux_pm_wb = .042f,
        .period_s = .0001f, .lambda = 10.0f,
        .coordinates = UZ_FSD_MPC_SI,
        .selector = UZ_FSD_A53_BENCHMARK_VARIANT >= 6U ?
            UZ_FSD_MPC_YANG_EXPERIMENTAL :
            (UZ_FSD_A53_BENCHMARK_VARIANT >= 3U ?
            UZ_FSD_MPC_DEADBEAT : UZ_FSD_MPC_EXHAUSTIVE),
        .modulation = UZ_FSD_A53_BENCHMARK_VARIANT % 3U == 0U ?
            UZ_FSD_MPC_SVM : (UZ_FSD_A53_BENCHMARK_VARIANT % 3U == 1U ?
                UZ_FSD_MPC_IFT : UZ_FSD_MPC_VFT),
        .solver = UZ_FSD_MPC_SIMPLEX_FACE
    };
    return config;
}

int main(void) {
    struct RPU_to_APU_user_data_t request = {0};
    struct APU_to_RPU_user_data_t response = {0};
    struct uz_fsd_mpc_output direct_output;
    struct uz_fsd_mpc_input first = input_from(samples[0]);
    uz_fsd_mpc_t *direct = uz_fsd_mpc_init(config_for_variant(),
        &first, &direct_output);
    check(direct != NULL && direct_output.status == UZ_FSD_MPC_OK,
        "direct preload failed");
    request.fsd_kind = UZ_FSD_A53_REQUEST_INIT;
    request.fsd_variant = UZ_FSD_A53_BENCHMARK_VARIANT;
    for (uint32_t j = 0U; j < 8U; ++j) request.fsd_input[j] = samples[0][j];
    fsd_a53_worker_process(&request, &response);
    check(response.fsd_status == 0U && response.fsd_sequence == 0U &&
        response.fsd_update_count == 0U, "worker preload failed");
    for (uint32_t i = 0U; i < 6012U; ++i) {
        struct uz_fsd_mpc_input input = input_from(samples[i % 6U]);
        request.fsd_kind = UZ_FSD_A53_REQUEST_STEP;
        request.fsd_sequence = i + 1U;
        for (uint32_t j = 0U; j < 8U; ++j) {
            request.fsd_input[j] = samples[i % 6U][j];
        }
        check(uz_fsd_mpc_step(direct, &input, &direct_output, NULL) ==
            UZ_FSD_MPC_OK, "direct step failed");
        fsd_a53_worker_process(&request, &response);
        check(response.fsd_status == 0U && response.fsd_sequence == i + 1U &&
            response.fsd_update_count == i + 1U &&
            response.fsd_timer_hz == COUNTS_PER_SECOND,
            "worker step status/sequence failed");
        check(fabsf(response.fsd_duty[0] - direct_output.duty_a) < 1e-6f &&
            fabsf(response.fsd_duty[1] - direct_output.duty_b) < 1e-6f &&
            fabsf(response.fsd_duty[2] - direct_output.duty_c) < 1e-6f,
            "worker duty mismatch");
		check(response.fsd_suitable_mask == direct_output.work.suitable_mask &&
			response.fsd_formulation_count == direct_output.work.formulation_count &&
			response.fsd_qp_solve_count == direct_output.work.qp_solve_count,
			"worker work-count mismatch");
        if (i == 0U) {
            fsd_a53_worker_process(&request, &response);
            check(response.fsd_status == 101U && isnan(response.fsd_duty[0]),
                "duplicate response was accepted");
        }
    }
    printf("variant %u: 6012 matching stateful steps; duplicate rejected\n",
        (unsigned)UZ_FSD_A53_BENCHMARK_VARIANT);
    return 0;
}
