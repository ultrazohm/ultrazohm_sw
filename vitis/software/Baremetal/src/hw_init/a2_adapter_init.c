#include "../include/a2_adapter_init.h"

/* Project Wizard BEGIN: A2 definitions */
/* Project Wizard generated content for A2 */
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "../uz/uz_wavegen/uz_wavegen.h"
#include "../globalData.h"
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

void update_dac8831_a2_outputs(struct _DS_Data_* data)
{

    data->av.dac8831_a2_ch0 = uz_wavegen_sine_sample_with_offset(data->objects.dac8831_a2_ch0_sine, 1.0f, 10.0f, 0.0f);
    dac8831_a2_outputs[0] = data->av.dac8831_a2_ch0;

    data->av.dac8831_a2_ch1 = uz_wavegen_sawtooth_sample_with_offset(data->objects.dac8831_a2_ch1_sawtooth, 1.0f, 10.0f, -2.5f);
    dac8831_a2_outputs[1] = data->av.dac8831_a2_ch1;

    data->av.dac8831_a2_ch2 = uz_wavegen_triangle_sample_with_offset(data->objects.dac8831_a2_ch2_triangle, 1.0f, 10.0f, -1.0f);
    dac8831_a2_outputs[2] = data->av.dac8831_a2_ch2;

    data->av.dac8831_a2_ch3 = uz_wavegen_sine_sample_with_offset(data->objects.dac8831_a2_ch3_sine, 1.0f, 10.0f, 0.0f);
    dac8831_a2_outputs[3] = data->av.dac8831_a2_ch3;

    data->av.dac8831_a2_ch4 = uz_wavegen_sine_sample_with_offset(data->objects.dac8831_a2_ch4_sine, 1.0f, 10.0f, 0.0f);
    dac8831_a2_outputs[4] = data->av.dac8831_a2_ch4;

    data->av.dac8831_a2_ch5 = uz_wavegen_sine_sample_with_offset(data->objects.dac8831_a2_ch5_sine, 1.0f, 10.0f, 0.0f);
    dac8831_a2_outputs[5] = data->av.dac8831_a2_ch5;

    data->av.dac8831_a2_ch6 = uz_wavegen_sine_sample_with_offset(data->objects.dac8831_a2_ch6_sine, 1.0f, 20.0f, 0.0f);
    dac8831_a2_outputs[6] = data->av.dac8831_a2_ch6;

    data->av.dac8831_a2_ch7 = uz_wavegen_sine_sample_with_offset(data->objects.dac8831_a2_ch7_sine, 1.0f, 10.0f, 0.0f);
    dac8831_a2_outputs[7] = data->av.dac8831_a2_ch7;

    uz_dac_interface_set_ouput_values(data->objects.dac8831_a2, &dac8831_a2_output_array);
}
/* Project Wizard END: A2 definitions */
