#pragma once
#include "../IP_Cores/uz_pmsmmodel/uz_pmsmModel.h"
#include "xparameters.h"
#include "../uz/uz_pmsm_control/uz_pmsm_control.h"


uz_pmsmModel_t* initialize_uz_pmsm_cil(void);

/* Reset the FPGA plant and the associated software rotor angle together. */
void reset_uz_pmsm_cil(uz_pmsmModel_t* pmsm);

/* Reconstruct rotating abc quantities from the dq-only model. Call exactly once
 * per ISR with its sample period: mechanical angle integrates sampled speed
 * and is wrapped to [0, 2*pi). Electrical angle uses the model's pole-pair count.
 * Use zero DUT angle offset/compensation for this ideal measurement adapter.
 * Phase voltages represent the applied dq command (no switching ripple).
 * The model has no DC-current measurement (reported as zero).
 */
struct uz_pmsm_measurement_values pmsm_cil_get_control_measurements(
    struct uz_pmsmModel_outputs_t outputs,
    struct uz_pmsmModel_inputs_t applied_inputs, float dc_link_voltage_V,
    float sample_time_s);
