#pragma once
#include "dut.h"

typedef enum { EXPERIMENT_NONE, EXPERIMENT_IQ_STEP, EXPERIMENT_IQ_SWEEP } experiment_id_t;
typedef enum { EXPERIMENT_IDLE, EXPERIMENT_RUNNING, EXPERIMENT_DONE,
    EXPERIMENT_ABORTED, EXPERIMENT_ERROR } experiment_status_t;

/* Float mirrors only: JavaScope requires float pointers. IDs/status persist
 * after completion; active distinguishes a running experiment from its result. */
typedef struct {
    float experiment_active, experiment_status, experiment_id;
    float iq_step_state, iq_step_measurement_id, iq_step_kp_active, iq_step_reference;
    float experiment_sample;
    float iq_sweep_state, iq_sweep_frequency_id, iq_sweep_frequency_hz;
    float iq_sweep_reference, iq_sweep_phase_rad, iq_sweep_measurement_active;
} experiment_scope_t;

void experiment_manager_init(uz_pmsm_control_t *dut, float period_s);
/* Call once per IPC poll, including zero/no-command polls, for edge detection. */
void experiment_manager_button3(bool asserted, bool allowed);
void experiment_manager_button4(bool asserted, bool allowed);
bool experiment_manager_is_running(void);
/* Also locks GUI iq/Kp writes between a button request and its first update. */
bool experiment_manager_owns_iq(void);
void experiment_manager_update(bool allowed, unsigned backend, float *iq_reference);
void experiment_manager_abort(float *iq_reference);
experiment_scope_t *experiment_manager_get_scope(void);
