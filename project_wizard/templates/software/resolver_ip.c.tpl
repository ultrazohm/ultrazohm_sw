/* Project Wizard generated content for {{ slot }} resolver IP channel {{ channel }} */
#include "xparameters.h"

static struct uz_resolverIP_config_t resolver_ip_{{ slot_lower }}_{{ channel }}_config = {
    .base_address = {{ base_address_macro }},
    .ip_clk_frequency_Hz = {{ ip_clk_frequency_Hz }},
    .resolution = {{ resolution }},
    .freq_clockin = {{ freq_clockin }},
    .zero_position_mechanical = {{ zero_position_mechanical }},
    .pole_pairs_machine = {{ pole_pairs_machine }},
    .pole_pairs_resolver = {{ pole_pairs_resolver }},
    .mode_after_init = {{ mode_after_init }}
};

uz_resolverIP_t* initialize_resolver_ip_{{ slot_lower }}_{{ channel }}(void)
{
    return uz_resolverIP_init(resolver_ip_{{ slot_lower }}_{{ channel }}_config);
}
