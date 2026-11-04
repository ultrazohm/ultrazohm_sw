#include "../include/iq_step_response.h"
#include <math.h>

static const float kp_values[] = IQ_STEP_KP_VALUES;
typedef char gain_count_must_match[(sizeof(kp_values) / sizeof(kp_values[0]) == IQ_STEP_NUM_KP_VALUES && IQ_STEP_NUM_KP_VALUES > 0U) ? 1 : -1];

bool iq_step_response_is_running(const iq_step_response_t *self)
{
    return self->state >= IQ_STEP_BASELINE && self->state <= IQ_STEP_INTER_TEST;
}

bool iq_step_response_init(iq_step_response_t *self, uz_pmsm_control_t *dut, float period_s)
{
    const uint32_t ms[] = {IQ_STEP_BASELINE_MS, IQ_STEP_HOLD_MS,
        IQ_STEP_RECOVERY_MS, IQ_STEP_INTER_TEST_MS};
    *self = (iq_step_response_t){.dut = dut};
    if (!dut || !isfinite(period_s) || period_s <= 0.0f ||
        !isfinite(IQ_STEP_BASE_CURRENT_A) || !isfinite(IQ_STEP_TARGET_CURRENT_A))
        return false;
    for (unsigned i = 0; i < 4U; ++i) {
        /* Round to nearest cycle; nonzero intervals occupy at least one cycle.
         * Conversion is done once, never in the control-loop state transitions. */
        double cycles = (double)ms[i] / (1000.0 * (double)period_s);
        if (cycles > (double)UINT32_MAX - 1.0) return false;
        self->durations[i] = (uint32_t)(cycles + 0.5);
        if (ms[i] && self->durations[i] == 0U) self->durations[i] = 1U;
    }
    if (!self->durations[0] || !self->durations[1] || !self->durations[2]) return false;
    for (unsigned i = 0; i < IQ_STEP_NUM_KP_VALUES; ++i)
        if (!isfinite(kp_values[i]) || kp_values[i] < 0.0f) return false;
    self->configured = true;
    return true;
}

static void baseline(iq_step_response_t *self)
{
    self->reference = IQ_STEP_BASE_CURRENT_A;
    (void)dut_set_Kp_iq(self->dut, kp_values[self->gain_index]);
    self->state = IQ_STEP_BASELINE;
    self->remaining = self->durations[0];
}

bool iq_step_response_start(iq_step_response_t *self)
{
    if (!self->configured || iq_step_response_is_running(self)) return false;
    self->saved_kp = dut_get_Kp_iq();
    self->gain_index = 0U;
    self->sample_count = 0U;
    baseline(self);
    return true;
}

static void finish(iq_step_response_t *self, iq_step_state_t state)
{
    self->reference = 0.0f;
    (void)dut_set_Kp_iq(self->dut, self->saved_kp);
    self->state = state;
}

void iq_step_response_abort(iq_step_response_t *self)
{
    if (iq_step_response_is_running(self)) finish(self, IQ_STEP_ABORTED);
}

void iq_step_response_update(iq_step_response_t *self)
{
    if (!iq_step_response_is_running(self)) return;
    if (self->remaining == 0U) {
        switch (self->state) {
        case IQ_STEP_BASELINE:
            self->state = IQ_STEP_HOLD;
            self->reference = IQ_STEP_TARGET_CURRENT_A;
            self->remaining = self->durations[1];
            break;
        case IQ_STEP_HOLD:
            self->state = IQ_STEP_RECOVERY;
            self->reference = IQ_STEP_BASE_CURRENT_A;
            self->remaining = self->durations[2];
            break;
        case IQ_STEP_RECOVERY:
            if (self->gain_index + 1U == IQ_STEP_NUM_KP_VALUES) {
                finish(self, IQ_STEP_DONE);
                return;
            }
            if (self->durations[3]) {
                self->state = IQ_STEP_INTER_TEST;
                self->remaining = self->durations[3];
                break;
            }
            ++self->gain_index;
            baseline(self);
            break;
        case IQ_STEP_INTER_TEST:
            ++self->gain_index;
            baseline(self);
            break;
        default: return;
        }
    }
    --self->remaining;
    ++self->sample_count;
}
