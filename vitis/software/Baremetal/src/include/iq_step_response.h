#pragma once
#include "dut.h"
#include <stdint.h>

#define IQ_STEP_NUM_KP_VALUES       5U
#define IQ_STEP_KP_VALUES           {2.0f, 5.0f, 8.8f, 12.0f, 15.0f}
#define IQ_STEP_BASE_CURRENT_A      0.0f
#define IQ_STEP_TARGET_CURRENT_A   1.0f
#define IQ_STEP_BASELINE_MS        50U
#define IQ_STEP_HOLD_MS           100U
#define IQ_STEP_RECOVERY_MS        50U
#define IQ_STEP_INTER_TEST_MS     300U

typedef enum {
    IQ_STEP_IDLE, IQ_STEP_BASELINE, IQ_STEP_HOLD, IQ_STEP_RECOVERY,
    IQ_STEP_INTER_TEST, IQ_STEP_DONE, IQ_STEP_ABORTED
} iq_step_state_t;

typedef struct {
    uz_pmsm_control_t *dut;
    iq_step_state_t state;
    uint32_t durations[4];
    uint32_t remaining, sample_count, gain_index;
    float saved_kp, reference;
    bool configured;
} iq_step_response_t;

bool iq_step_response_init(iq_step_response_t *self, uz_pmsm_control_t *dut, float period_s);
bool iq_step_response_start(iq_step_response_t *self);
void iq_step_response_update(iq_step_response_t *self);
void iq_step_response_abort(iq_step_response_t *self);
bool iq_step_response_is_running(const iq_step_response_t *self);
