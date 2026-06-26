/* Project Wizard generated content for {{ slot }} incremental encoder channel {{ channel }} */
#include "xparameters.h"

static struct uz_incrementalEncoder_config incremental_encoder_{{ slot_lower }}_{{ channel }}_config = {
    .base_address = {{ base_address_macro }},
    .ip_core_frequency_Hz = {{ ip_core_frequency_Hz }},
    .line_number_per_turn_mech = {{ line_number_per_turn_mech }},
    .OmegaPerOverSample_in_rpm = {{ OmegaPerOverSample_in_rpm }},
    .drive_pole_pair = {{ drive_pole_pair }},
    .Encoder_mech_Offset = {{ Encoder_mech_Offset }},
    .Encoder_elec_Offset = {{ Encoder_elec_Offset }},
    .counting_direction = {{ counting_direction }},
    .Speed_Timeout_ms = {{ Speed_Timeout_ms }}
};

uz_incrementalEncoder_t* initialize_incremental_encoder_{{ slot_lower }}_{{ channel }}(void)
{
    return uz_incrementalEncoder_init(incremental_encoder_{{ slot_lower }}_{{ channel }}_config);
}
