#pragma once
#include "../IP_Cores/uz_pmsmmodel/uz_pmsmModel.h"
#include "xparameters.h"
#include "../uz/uz_pmsm_control/uz_pmsm_control.h"


uz_pmsmModel_t* initialize_uz_pmsm_cil(void);

/* Synthetic abc measurements for the dq-only model. Use with zero controller
 * angle offset/compensation; these are not physical rotating phase waveforms.
 * The model has no DC-current measurement (reported as zero).
 */
struct uz_pmsm_measurement_values pmsm_cil_get_control_measurements(
    struct uz_pmsmModel_outputs_t outputs,
    struct uz_pmsmModel_inputs_t applied_inputs, float dc_link_voltage_V);
