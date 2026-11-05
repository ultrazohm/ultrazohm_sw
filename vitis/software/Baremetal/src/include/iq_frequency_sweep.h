#pragma once
#include <stdbool.h>
#include <stdint.h>

#define IQ_SWEEP_OFFSET_A          2.0f
#define IQ_SWEEP_AMPLITUDE_A       0.5f
#define IQ_SWEEP_SETTLE_CYCLES     5U
#define IQ_SWEEP_MEASURE_CYCLES   10U
#define IQ_SWEEP_RAMP_MS          20U
#define IQ_SWEEP_MIN_SAMPLES_PER_PERIOD 5U
#define IQ_SWEEP_NUM_FREQUENCIES  16U
#define IQ_SWEEP_FREQUENCIES_HZ {20.0f,30.0f,45.0f,70.0f,100.0f,150.0f,220.0f,330.0f,470.0f,680.0f,820.0f,1000.0f,1200.0f,1400.0f,1600.0f,1800.0f}
/* 1200/1500 Hz require a separately reviewed sampling/logging configuration. */
typedef enum {
    IQ_SWEEP_IDLE, IQ_SWEEP_PREPARE, IQ_SWEEP_SETTLE, IQ_SWEEP_MEASURE,
    IQ_SWEEP_NEXT_FREQUENCY, IQ_SWEEP_DONE, IQ_SWEEP_ABORTED, IQ_SWEEP_ERROR,
    IQ_SWEEP_RETURN_ZERO
} iq_sweep_state_t;

typedef struct {
    iq_sweep_state_t state;
    bool configured;
    double phase_turns;
    double increments[IQ_SWEEP_NUM_FREQUENCIES];
    uint32_t completed_cycles, frequency_index, sample_count, ramp_samples, ramp_tick;
    float reference, phase_rad, frequency_hz, entry_reference;
} iq_frequency_sweep_t;

bool iq_frequency_sweep_init(iq_frequency_sweep_t *self, float period_s);
bool iq_frequency_sweep_start(iq_frequency_sweep_t *self, float current_reference);
void iq_frequency_sweep_update(iq_frequency_sweep_t *self);
void iq_frequency_sweep_abort(iq_frequency_sweep_t *self);
bool iq_frequency_sweep_is_running(const iq_frequency_sweep_t *self);
