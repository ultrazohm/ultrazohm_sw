#include "uz_adcLtc2311.h"
#include "uz_adcLtc2311_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_adcLtc2311_private.h"

uz_adcLtc2311* uz_adcLtc2311_init(uz_adcLtc2311* self)
{
    // Check correct initialization
    uz_assert_not_NULL(self);
    uz_assert_false(self->is_ready);
    self->is_ready=true;
    uz_assert_not_zero(self->base_address);
    uz_assert_not_zero(self->ip_clk_frequency_Hz);
    return (self);
}

void uz_adcLtc2311_init_conversionConfig(uz_adcLtc2311_conversionConfig* configuration)
{
    uz_assert_not_NULL(configuration);

    configuration->channel_select=0;
    configuration->master_select=0;
    configuration->conversion_factor=1;
    configuration->offset=0;
    configuration->set_conversion=false;
    configuration->set_offset=false;
    configuration->error_code=0;
    configuration->try_infinite=true;
    configuration->max_attempts=0;
}

uz_adcLtc2311_conversionConfig* uz_adcLtc2311_configureConversion(uz_adcLtc2311* self, uz_adcLtc2311_conversionConfig* configuration)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(configuration);

    uz_adcLtc2311_hw_write_master_channel(self->base_address, configuration->master_select);
    uz_adcLtc2311_hw_write_channel(self->base_address, configuration->channel_select);

    uint32_t max_attempts=configuration->max_attempts;
    if(configuration->set_offset)
    {
        uz_adcLtc2311_hw_write_conversion_value(self->base_address, configuration->offset);
        uz_adcLtc2311_hw_write_cr(self->base_address, uz_adcLtc2311_hw_read_cr(self->base_address) | UZ_ADCLTC2311_CR_CONV_VALUE_VALID);
        while(uz_adcLtc2311_hw_read_cr(self->base_address) & UZ_ADCLTC2311_CR_CONV_VALUE_VALID)
        {
            if((configuration->try_infinite == false) && (--max_attempts <= 0))
            {
                configuration->error_code |= UZ_ADCLTC2311_SET_OFFSET_FAILED;
                break;
            }
        }
    }

    max_attempts=configuration->max_attempts;
    if(configuration->set_conversion)
    {
        uz_adcLtc2311_hw_write_conversion_value(self->base_address, configuration->conversion_factor);
        uz_adcLtc2311_hw_write_cr(self->base_address, uz_adcLtc2311_hw_read_cr(self->base_address) | UZ_ADCLTC2311_CR_CONV_VALUE_VALID);
        while(uz_adcLtc2311_hw_read_cr(self->base_address) & UZ_ADCLTC2311_CR_CONV_VALUE_VALID)
        {
            if((configuration->try_infinite == false) && (--max_attempts <= 0))
            {
                configuration->error_code |= UZ_ADCLTC2311_SET_CONV_FAILED;
                break;
            }
        }
    }

    return configuration;
}

void uz_adcLtc2311_softwareReset(uz_adcLtc2311* self)
{
    uz_assert_not_NULL(self);

    uz_adcLtc2311_hw_write_cr(self->base_address, uz_adcLtc2311_hw_read_cr(self->base_address) | UZ_ADCLTC2311_CR_SW_RESET);

    while(uz_adcLtc2311_hw_read_cr(self->base_address) & UZ_ADCLTC2311_CR_SW_RESET)
    {
        ;
    }
}