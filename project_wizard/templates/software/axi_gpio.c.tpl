/* Project Wizard generated content for {{ slot }} AXI GPIO IO card */
#include "xparameters.h"
#include "../IP_Cores/uz_axi_gpio/uz_axi_gpio.h"

#ifndef {{ device_id_macro }}
#define {{ device_id_macro }} {{ fallback_device_id }}U
#endif

#define {{ direction_mask_define }} {{ direction_mask }}U

static struct uz_axi_gpio_config_t axi_gpio_{{ slot_lower }}_config = {
    .base_address = {{ base_address_macro }},
    .device_id = {{ device_id_macro }},
    .number_of_pins = 30U,
    .direction_of_pins = {{ direction_mask_define }}
};

uz_axi_gpio_t* initialize_axi_gpio_{{ slot_lower }}(void)
{
    return uz_axi_gpio_init(axi_gpio_{{ slot_lower }}_config);
}
