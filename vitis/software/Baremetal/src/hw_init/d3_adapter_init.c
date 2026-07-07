#include "../include/d3_adapter_init.h"

/* Project Wizard BEGIN: D3 definitions */
/* Project Wizard generated content for D3 incremental encoder channel 1 */
#include "xparameters.h"

static struct uz_incrementalEncoder_config incremental_encoder_d3_1_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D3_ADAPTER_INCREMENTAL_ENCODER_D3_1_BASEADDR,
    .ip_core_frequency_Hz = 100000000U,
    .line_number_per_turn_mech = 5000U,
    .OmegaPerOverSample_in_rpm = 500.0f,
    .drive_pole_pair = 4U,
    .Encoder_mech_Offset = 0U,
    .Encoder_elec_Offset = 0U,
    .counting_direction = uz_incrementalEncoder_counting_clock_wise,
    .Speed_Timeout_ms = 10U
};

uz_incrementalEncoder_t* initialize_incremental_encoder_d3_1(void)
{
    return uz_incrementalEncoder_init(incremental_encoder_d3_1_config);
}
/* Project Wizard generated content for D3 incremental encoder channel 2 */
#include "xparameters.h"

static struct uz_incrementalEncoder_config incremental_encoder_d3_2_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D3_ADAPTER_INCREMENTAL_ENCODER_D3_2_BASEADDR,
    .ip_core_frequency_Hz = 100000000U,
    .line_number_per_turn_mech = 5000U,
    .OmegaPerOverSample_in_rpm = 500.0f,
    .drive_pole_pair = 4U,
    .Encoder_mech_Offset = 0U,
    .Encoder_elec_Offset = 0U,
    .counting_direction = uz_incrementalEncoder_counting_clock_wise,
    .Speed_Timeout_ms = 10U
};

uz_incrementalEncoder_t* initialize_incremental_encoder_d3_2(void)
{
    return uz_incrementalEncoder_init(incremental_encoder_d3_2_config);
}
/* Project Wizard generated content for D3 incremental encoder channel 3 */
#include "xparameters.h"

static struct uz_incrementalEncoder_config incremental_encoder_d3_3_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D3_ADAPTER_INCREMENTAL_ENCODER_D3_3_BASEADDR,
    .ip_core_frequency_Hz = 100000000U,
    .line_number_per_turn_mech = 5000U,
    .OmegaPerOverSample_in_rpm = 500.0f,
    .drive_pole_pair = 4U,
    .Encoder_mech_Offset = 0U,
    .Encoder_elec_Offset = 0U,
    .counting_direction = uz_incrementalEncoder_counting_clock_wise,
    .Speed_Timeout_ms = 10U
};

uz_incrementalEncoder_t* initialize_incremental_encoder_d3_3(void)
{
    return uz_incrementalEncoder_init(incremental_encoder_d3_3_config);
}
/* Project Wizard END: D3 definitions */
