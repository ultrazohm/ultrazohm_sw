#include "../include/iq_frequency_sweep.h"
#include "../include/dut.h"
#include <math.h>

static const float frequencies[] = IQ_SWEEP_FREQUENCIES_HZ;
typedef char frequency_count_matches[(sizeof(frequencies)/sizeof(frequencies[0]) == IQ_SWEEP_NUM_FREQUENCIES && IQ_SWEEP_NUM_FREQUENCIES > 0U) ? 1 : -1];

bool iq_frequency_sweep_is_running(const iq_frequency_sweep_t *self)
{
    return (self->state >= IQ_SWEEP_PREPARE && self->state <= IQ_SWEEP_NEXT_FREQUENCY)
        || self->state == IQ_SWEEP_RETURN_ZERO;
}

bool iq_frequency_sweep_init(iq_frequency_sweep_t *self, float period_s)
{
    *self = (iq_frequency_sweep_t){0};
    if (!isfinite(period_s) || period_s <= 0.0f ||
        !isfinite(IQ_SWEEP_OFFSET_A) || !isfinite(IQ_SWEEP_AMPLITUDE_A) || IQ_SWEEP_AMPLITUDE_A <= 0.0f ||
        IQ_SWEEP_OFFSET_A-IQ_SWEEP_AMPLITUDE_A < DUT_IQ_REFERENCE_MIN_A ||
        IQ_SWEEP_OFFSET_A+IQ_SWEEP_AMPLITUDE_A > DUT_IQ_REFERENCE_MAX_A ||
        IQ_SWEEP_SETTLE_CYCLES == 0U || IQ_SWEEP_MEASURE_CYCLES == 0U || IQ_SWEEP_RAMP_MS == 0U)
        goto invalid;
    double ramp = (double)IQ_SWEEP_RAMP_MS / (1000.0*(double)period_s);
    if (ramp > (double)UINT32_MAX-1.0) goto invalid;
    self->ramp_samples = (uint32_t)(ramp+0.5);
    if (self->ramp_samples == 0U) self->ramp_samples = 1U;
    for (unsigned i=0; i<IQ_SWEEP_NUM_FREQUENCIES; ++i) {
        double increment = (double)frequencies[i] * (double)period_s;
        if (!isfinite(frequencies[i]) || frequencies[i] <= 0.0f ||
            (i && frequencies[i] <= frequencies[i-1]) ||
            increment > 1.0/(double)IQ_SWEEP_MIN_SAMPLES_PER_PERIOD + 1e-8 || increment >= 0.5)
            goto invalid;
        self->increments[i] = increment;
    }
    self->configured = true;
    return true;
invalid:
    self->state = IQ_SWEEP_ERROR;
    return false;
}

bool iq_frequency_sweep_start(iq_frequency_sweep_t *self, float current_reference)
{
    if (iq_frequency_sweep_is_running(self)) return false;
    if (!self->configured || !isfinite(current_reference) ||
        current_reference < DUT_IQ_REFERENCE_MIN_A || current_reference > DUT_IQ_REFERENCE_MAX_A) {
        self->state = IQ_SWEEP_ERROR;
        return false;
    }
    self->frequency_index = 0U;
    self->frequency_hz = frequencies[0];
    self->sample_count = self->ramp_tick = self->completed_cycles = 0U;
    self->phase_turns = 0.0;
    self->phase_rad = 0.0f;
    self->entry_reference = self->reference = current_reference;
    self->state = IQ_SWEEP_PREPARE;
    return true;
}

static void begin_point(iq_frequency_sweep_t *self)
{
    self->phase_turns = 0.0;
    self->phase_rad = 0.0f;
    self->completed_cycles = 0U;
    self->frequency_hz = frequencies[self->frequency_index];
    self->state = IQ_SWEEP_SETTLE;
}

void iq_frequency_sweep_abort(iq_frequency_sweep_t *self)
{
    if (iq_frequency_sweep_is_running(self)) {
        self->reference = 0.0f;
        self->state = IQ_SWEEP_ABORTED;
    }
}

void iq_frequency_sweep_update(iq_frequency_sweep_t *self)
{
    if (!iq_frequency_sweep_is_running(self)) return;
    ++self->sample_count;
    if (self->state == IQ_SWEEP_PREPARE || self->state == IQ_SWEEP_RETURN_ZERO) {
        bool returning = self->state == IQ_SWEEP_RETURN_ZERO;
        if (self->ramp_tick < self->ramp_samples) {
            ++self->ramp_tick;
            float fraction = (float)self->ramp_tick / (float)self->ramp_samples;
            self->reference = returning ? IQ_SWEEP_OFFSET_A*(1.0f-fraction) :
                self->entry_reference + (IQ_SWEEP_OFFSET_A-self->entry_reference)*fraction;
            return;
        }
        if (returning) { self->reference=0.0f; self->state=IQ_SWEEP_DONE; return; }
        begin_point(self);
    }
    if (self->state == IQ_SWEEP_NEXT_FREQUENCY) {
        if (self->frequency_index+1U == IQ_SWEEP_NUM_FREQUENCIES) {
            self->ramp_tick=0U;
            self->state=IQ_SWEEP_RETURN_ZERO;
            return;
        }
        ++self->frequency_index;
        begin_point(self);
    }
    // Bounded accumulator: never round a sinusoidal period to an integer sample count.
    // The small tolerance handles float sample-time representation at exact boundaries.
    if (self->phase_turns >= 1.0-1e-6) {
        self->phase_turns -= 1.0;
        if (self->phase_turns < 0.0) self->phase_turns = 0.0;
        ++self->completed_cycles;
    }
    if (self->completed_cycles >= IQ_SWEEP_SETTLE_CYCLES+IQ_SWEEP_MEASURE_CYCLES) {
        // End at the first sample at/past the final zero crossing, at the offset.
        self->phase_rad = 0.0f;
        self->reference = IQ_SWEEP_OFFSET_A;
        self->state = IQ_SWEEP_NEXT_FREQUENCY;
        return;
    }
    self->state = self->completed_cycles >= IQ_SWEEP_SETTLE_CYCLES ? IQ_SWEEP_MEASURE : IQ_SWEEP_SETTLE;
    self->phase_rad = (float)(self->phase_turns * 6.283185307179586);
    self->reference = IQ_SWEEP_OFFSET_A + IQ_SWEEP_AMPLITUDE_A*sinf(self->phase_rad);
    self->phase_turns += self->increments[self->frequency_index];
}
