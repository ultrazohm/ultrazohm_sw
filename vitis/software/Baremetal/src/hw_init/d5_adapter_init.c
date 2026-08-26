#include "../include/d5_adapter_init.h"

/* Project Wizard BEGIN: D5 definitions */
/* Project Wizard generated content for D5 incremental encoder channel 1 */
#include "xparameters.h"

static struct uz_incrementalEncoder_config incremental_encoder_d5_1_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_INCREMENTAL_ENCODER_D5_1_BASEADDR,
    .ip_core_frequency_Hz = 100000000U,
    .line_number_per_turn_mech = 5000U,
    .OmegaPerOverSample_in_rpm = 500.0f,
    .drive_pole_pair = 4U,
    .Encoder_mech_Offset = 0U,
    .Encoder_elec_Offset = 0U,
    .counting_direction = uz_incrementalEncoder_counting_clock_wise,
    .Speed_Timeout_ms = 10U
};

uz_incrementalEncoder_t* initialize_incremental_encoder_d5_1(void)
{
    return uz_incrementalEncoder_init(incremental_encoder_d5_1_config);
}
/* Project Wizard END: D5 definitions */
