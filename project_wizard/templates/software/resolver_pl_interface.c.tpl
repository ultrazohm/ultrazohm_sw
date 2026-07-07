/* Project Wizard generated content for {{ slot }} resolver PL interface channel {{ channel }} */
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

static struct uz_resolver_pl_interface_config_t resolver_pl_interface_{{ slot_lower }}_{{ channel }}_config = {
    .base_address = {{ base_address_macro }},
    .ip_clk_frequency_Hz = {{ ip_clk_frequency_Hz }},
    .resolver_polepairs = {{ resolver_polepairs }},
    .machine_polepairs = {{ machine_polepairs }},
    .position_intmax = {{ position_intmax }},
    .bitToRPS_factor = {{ bitToRPS_factor }},
    .theta_m_offset_rad = {{ theta_m_offset_rad }}
};

static struct uz_resolver_pl_interface_outputs_t resolver_pl_interface_{{ slot_lower }}_{{ channel }}_outputs = {
    .revolution_counter = 0,
    .position_mech_2pi = 0.0f,
    .position_el_2pi = 0.0f,
    .omega_mech_rad_s = 0.0f,
    .n_mech_rpm = 0.0f
};

uz_resolver_pl_interface_t* initialize_resolver_pl_interface_{{ slot_lower }}_{{ channel }}(void)
{
    return uz_resolver_pl_interface_init(
        resolver_pl_interface_{{ slot_lower }}_{{ channel }}_config,
        resolver_pl_interface_{{ slot_lower }}_{{ channel }}_outputs
    );
}
