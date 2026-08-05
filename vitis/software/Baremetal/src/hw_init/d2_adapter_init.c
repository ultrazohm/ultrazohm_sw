#include "../include/d2_adapter_init.h"

/* Project Wizard BEGIN: D2 definitions */
#include "../uz/uz_global_configuration.h"
#include "../globalData.h"
#include "xparameters.h"

static struct uz_inverter_adapter_config_t inverter_adapter_d2_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D2_ADAPTER_UZ_D_INVERTER_ADAPTER_D2_BASEADDR,
    .ip_clk_frequency_Hz = 100000000U,
    .linear_interpolation_params = {.a = -289.01f, .b = 218.72f}};
static struct uz_inverter_adapter_outputs_t inverter_adapter_d2_outputs = {0};

uz_inverter_adapter_t *initialize_inverter_adapter_d2(void)
{
    return uz_inverter_adapter_init(inverter_adapter_d2_config, inverter_adapter_d2_outputs);
}

void update_inverter_adapter_d2_outputs(struct _DS_Data_ *data)
{
    data->av.inverter_adapter_d2 = uz_inverter_adapter_get_outputs(data->objects.inverter_adapter_d2);
}
/* Project Wizard END: D2 definitions */
