#include "../include/experiment_manager.h"
#include "../include/iq_step_response.h"

static iq_step_response_t step;
static experiment_scope_t scope;
static experiment_status_t status;
static experiment_id_t selected;
static bool pending, button3_was_asserted, configured;
static unsigned start_backend;

bool experiment_manager_is_running(void) { return status == EXPERIMENT_RUNNING; }
bool experiment_manager_owns_iq(void) { return pending || experiment_manager_is_running(); }
experiment_scope_t *experiment_manager_get_scope(void) { return &scope; }

static void publish(void)
{
    scope.experiment_active = experiment_manager_is_running() ? 1.0f : 0.0f;
    scope.experiment_status = (float)status;
    scope.experiment_id = (float)selected;
    scope.iq_step_state = (float)step.state;
    scope.iq_step_measurement_id = step.state == IQ_STEP_IDLE ? 0.0f : (float)(step.gain_index + 1U);
    scope.iq_step_kp_active = dut_get_Kp_iq();
    scope.iq_step_reference = step.reference;
    scope.experiment_sample = (float)step.sample_count;
}

void experiment_manager_init(uz_pmsm_control_t *dut, float period_s)
{
    configured = iq_step_response_init(&step, dut, period_s);
    status = configured ? EXPERIMENT_IDLE : EXPERIMENT_ERROR;
    selected = EXPERIMENT_NONE;
    pending = false;
    button3_was_asserted = false;
    publish();
}

void experiment_manager_button3(bool asserted, bool allowed)
{
    if (asserted && !button3_was_asserted && !experiment_manager_owns_iq()) {
        /* Invalid requests are consumed, never deferred until system enable. */
        if (allowed && configured) pending = true;
        else { status = EXPERIMENT_ERROR; publish(); }
    }
    button3_was_asserted = asserted;
}

void experiment_manager_abort(float *iq_reference)
{
    if (experiment_manager_owns_iq()) {
        switch (selected) {
        case EXPERIMENT_IQ_STEP: iq_step_response_abort(&step); break;
        default: break;
        }
        pending = false;
        *iq_reference = 0.0f;
        status = EXPERIMENT_ABORTED;
        publish();
    }
}

void experiment_manager_update(bool allowed, unsigned backend, float *iq_reference)
{
    if (!allowed || (experiment_manager_is_running() && backend != start_backend)) {
        experiment_manager_abort(iq_reference);
        publish();
        return;
    }
    if (pending) {
        pending = false;
        selected = EXPERIMENT_IQ_STEP;
        start_backend = backend;
        switch (selected) {
        case EXPERIMENT_IQ_STEP:
            status = iq_step_response_start(&step) ? EXPERIMENT_RUNNING : EXPERIMENT_ERROR;
            break;
        default: status = EXPERIMENT_ERROR; break;
        }
    }
    if (experiment_manager_is_running()) {
        switch (selected) {
        case EXPERIMENT_IQ_STEP:
            iq_step_response_update(&step);
            *iq_reference = step.reference;
            if (!iq_step_response_is_running(&step)) status = EXPERIMENT_DONE;
            break;
        default: experiment_manager_abort(iq_reference); break;
        }
    }
    publish();
}
