#include "../include/a2_adapter_init.h"

/* Project Wizard BEGIN: A2 definitions */
/* Project Wizard generated content for A2 */
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"
#include <stdint.h>

static struct uz_dac_interface_config_t config_dac8831_a2 = {
    .base_address = XPAR_UZ_ANALOG_ADAPTER_A2_ADAPTER_A2_DAC8831_BASEADDR,
    .ip_clk_frequency_Hz = 100000000U,
    .gain = {
        2.0f,
        2.0f,
        2.0f,
        2.0f,
        2.0f,
        2.0f,
        2.0f,
        2.0f}};

static float dac8831_a2_outputs[UZ_DAC_INTERFACE_OUTPUT_CHANNELS] = {
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f};

static uz_array_float_t dac8831_a2_output_array = {
    .data = &dac8831_a2_outputs[0],
    .length = UZ_DAC_INTERFACE_OUTPUT_CHANNELS};

uz_dac_interface_t* initialize_dac8831_a2(void)
{
    return uz_dac_interface_init(config_dac8831_a2);
}

void update_dac8831_a2_outputs(uz_dac_interface_t* instance)
{
    uz_dac_interface_set_ouput_values(instance, &dac8831_a2_output_array);
}
/* Project Wizard END: A2 definitions */
