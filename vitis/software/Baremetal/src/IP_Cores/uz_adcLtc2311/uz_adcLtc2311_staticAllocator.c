#pragma once
#include "uz_adcLtc2311.h"
#include "uz_adcLtc2311_private.h"
#include "xparameters.h"

static uz_adcLtc2311 uz_adcLtc2311_instance_one=
{
    .base_address=XPAR_ADC_LTC2311_S00_AXI_BASEADDR,
    .ip_clk_frequency_Hz=100000000U,
};

uz_adcLtc2311* uz_adcLtc2311_allocate_instance_one(void)
{
    return (uz_adcLtc2311_init(&uz_adcLtc2311_instance_one));
}
