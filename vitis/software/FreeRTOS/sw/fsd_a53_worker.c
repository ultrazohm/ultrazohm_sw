#include "../include/fsd_a53_worker.h"

#if UZ_FSD_A53_BENCHMARK_ENABLE
#include "../uz/uz_fsd_mpc/uz_fsd_mpc.h"
#include "xtime_l.h"
#include <math.h>
#include <stdbool.h>
#include <stddef.h>

/* Protocol errors are separate from uz_fsd_mpc_status_t (0..4). */
#define FSD_A53_BAD_REQUEST 100U
#define FSD_A53_BAD_SEQUENCE 101U

static uz_fsd_mpc_t *controller;
static uint32_t last_sequence;
static uint32_t selected_variant;
static bool initialized;

static struct uz_fsd_mpc_config config_for_variant(uint32_t variant) {
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
    if (variant >= 3U && variant < 6U) {
        config.selector = UZ_FSD_MPC_DEADBEAT;
    }
    if (variant >= 6U) {
        config.selector = UZ_FSD_MPC_YANG_EXPERIMENTAL;
    }
    if ((variant % 3U) == 1U) {
        config.modulation = UZ_FSD_MPC_IFT;
    } else if ((variant % 3U) == 2U) {
        config.modulation = UZ_FSD_MPC_VFT;
    }
    return config;
}

static struct uz_fsd_mpc_input copy_input(
    const volatile struct RPU_to_APU_user_data_t *request) {
    struct uz_fsd_mpc_input input = {
        .ia = request->fsd_input[0], .ib = request->fsd_input[1],
        .ic = request->fsd_input[2], .theta_e = request->fsd_input[3],
        .omega_e = request->fsd_input[4], .v_dc = request->fsd_input[5],
        .id_ref = request->fsd_input[6], .iq_ref = request->fsd_input[7]
    };
    return input;
}

void fsd_a53_worker_process(
    const volatile struct RPU_to_APU_user_data_t *request,
    volatile struct APU_to_RPU_user_data_t *response) {
    struct uz_fsd_mpc_input input;
    struct uz_fsd_mpc_output output = {0};
    uz_fsd_mpc_status_t status = UZ_FSD_MPC_INPUT_INVALID;
    XTime start = 0;
    XTime end = 0;
    uint32_t kind = request->fsd_kind;
    uint32_t sequence = request->fsd_sequence;
    uint32_t variant = request->fsd_variant;

    if (kind == UZ_FSD_A53_REQUEST_NONE) {
        response->fsd_kind = UZ_FSD_A53_REQUEST_NONE;
        return;
    }
    response->fsd_kind = kind;
    response->fsd_sequence = sequence;
    response->fsd_status = FSD_A53_BAD_REQUEST;
    response->fsd_update_count = 0U;
    response->fsd_duty[0] = NAN;
    response->fsd_duty[1] = NAN;
    response->fsd_duty[2] = NAN;
    response->fsd_compute_ticks = 0U;
    response->fsd_timer_hz = COUNTS_PER_SECOND;
    response->fsd_suitable_mask = 0U;
    response->fsd_formulation_count = 0U;
    response->fsd_qp_solve_count = 0U;
    if (variant != UZ_FSD_A53_BENCHMARK_VARIANT || variant > 8U) {
        return;
    }
    if (kind == UZ_FSD_A53_REQUEST_INIT) {
        if (sequence != 0U) {
            response->fsd_status = FSD_A53_BAD_SEQUENCE;
            return;
        }
        input = copy_input(request);
        XTime_GetTime(&start);
        if (controller == NULL) {
            controller = uz_fsd_mpc_init(config_for_variant(variant),
                &input, &output);
            status = controller == NULL ? UZ_FSD_MPC_FAULTED : output.status;
        } else if (selected_variant == variant) {
            status = uz_fsd_mpc_reset(controller, &input, &output);
        } else {
            response->fsd_status = FSD_A53_BAD_REQUEST;
            return;
        }
        XTime_GetTime(&end);
        initialized = status == UZ_FSD_MPC_OK;
        selected_variant = variant;
        last_sequence = 0U;
    } else if (kind == UZ_FSD_A53_REQUEST_STEP) {
        if (!initialized || controller == NULL ||
            sequence != last_sequence + 1U) {
            response->fsd_status = FSD_A53_BAD_SEQUENCE;
            return;
        }
        input = copy_input(request);
        XTime_GetTime(&start);
        status = uz_fsd_mpc_step(controller, &input, &output, NULL);
        XTime_GetTime(&end);
        if (status == UZ_FSD_MPC_OK) {
            last_sequence = sequence;
        } else {
            initialized = false;
        }
    } else {
        return;
    }
    response->fsd_compute_ticks = (uint64_t)(end - start);
    response->fsd_status = (uint32_t)status;
    response->fsd_update_count = output.update_count;
    response->fsd_duty[0] = output.duty_a;
    response->fsd_duty[1] = output.duty_b;
    response->fsd_duty[2] = output.duty_c;
    response->fsd_suitable_mask = output.work.suitable_mask;
    response->fsd_formulation_count = output.work.formulation_count;
    response->fsd_qp_solve_count = output.work.qp_solve_count;
}
#endif
