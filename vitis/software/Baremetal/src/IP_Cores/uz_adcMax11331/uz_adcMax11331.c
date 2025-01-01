#include "../../uz/uz_global_configuration.h"
#if UZ_ADCMAX11331_MAX_INSTANCES > 0U
#include <stdbool.h>
#include <stdint.h>
#include "../../uz/uz_HAL.h"
#include "uz_adcMax11331.h"
#include "uz_adcMax11331_hw.h"
#include "uz_adcMax11331_hwAdresses.h"

struct uz_adcMax11331_t
{
    bool is_ready;
    struct uz_adcMax11331_config_t config;
};

static size_t instance_counter = 0U;
static uz_adcMax11331_t instances[UZ_ADCMAX11331_MAX_INSTANCES] = {0};

static uz_adcMax11331_t *uz_adcMax11331_allocation(void);

static uz_adcMax11331_t *uz_adcMax11331_allocation(void)
{
    uz_assert(instance_counter < UZ_ADCMAX11331_MAX_INSTANCES);
    uz_adcMax11331_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_adcMax11331_t *uz_adcMax11331_init(struct uz_adcMax11331_config_t config)
{
    uz_adcMax11331_t *self = uz_adcMax11331_allocation();
    uz_assert_not_zero(config.ip_clk_frequency_Hz);
    uz_assert_not_zero(config.base_address);
    uz_assert(config.channel_config.conversion_factor != 0.0f);
    uz_assert(config.cpol != 0U);
    uz_assert(config.cpha != 0U);
    uz_assert(config.clk_div > 0U);
    uz_assert(config.adc_delay_offset < 1024U);
    self->config = config;
    //Assemble the content of SPI configuration register ADC_MAX11331_CLK_DIVISION and write it
    uz_adcMax11331_hw_write_spi_cfgr(self->config.base_address, self->config.clk_div);

    //Assemble the content of Init register ADC_MAX11331_ADCSELECTOR_FORCEINIT and write it. Only the lower 9 Bit of the 32 Bit are used. See detailed Bit mapping at the end of the file ADC_MAX11331_AXI_Lite.vhd.
    	//ForceInit(8): 00000001 xxxxxxxx (8th Bit to force ReInit) or = 00000000 xxxxxxxx (default)
    	//ADC Selector(7..0): xxxxxxxx 00000111 (where each 1 represents one additional ADC chip -> here 3 chips on adapter board)
    	//In total ADC_MAX11331_ADCSELECTOR_FORCEINIT: (8..0): 00000001 00000111 (=0x107) or 00000000 00000111 (=0x7)
    uz_adcMax11331_hw_write_master_channel(self->config.base_address,0x107); //activate ForceInit
    usleep(1000000); //wait to be sure, that Init has happened. This is required since in past a Init without ADC ready lead to unstable behavior.
    uz_adcMax11331_hw_write_master_channel(self->config.base_address,0x7); //deactivate ForceInit

	//Assemble the content of Delay register ADC_MAX11331_DELAY_OFFSET and write it
    uz_adcMax11331_hw_write_delay_offset(self->config.base_address,self->config.adc_delay_offset);

    return (self);
}

void uz_adcMax11331_set_clk_div(uz_adcMax11331_t *self, uint32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(
        uz_adcMax11331_check_32_bit_int_if_not_more_sign_bits_set_than_spec(
            value,
            UZ_ADCMAX11331_SPI_CFGR_CLK_DIV_WIDTH));
    self->config.clk_div = value;
}

void uz_adcMax11331_set_delay_offset(uz_adcMax11331_t *self, uint32_t value)
{
	uz_adcMax11331_hw_write_delay_offset(self->config.base_address, value);
}


uint32_t uz_adcMax11331_get_base_address(uz_adcMax11331_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (self->config.base_address);
}

uint32_t uz_adcMax11331_get_error_code(uz_adcMax11331_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (self->config.error_code);
}

uint32_t uz_adcMax11331_get_clk_div(uz_adcMax11331_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (self->config.clk_div);
}

uint32_t uz_adcMax11331_get_delay_offset(uz_adcMax11331_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (self->config.adc_delay_offset);
}


// update functions
void uz_adcMax11331_check_echo_of_master(uz_adcMax11331_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    //First, write to the IP-Core which master (physical ADC chip) is checked for the echo
    uz_adcMax11331_hw_write_master_channel(self->config.base_address, self->config.master_select);
    //Read the echo of one physical ADC chip. This includes  how the chip is configured (single/diff. or clock divider or ...)
}


/**
 * @brief Returns true if the MSB of value is not set
 *
 * @param value value to be tested
 * @return _Bool
 */
_Bool uz_adcMax11331_check_32_bit_int_if_msb_not_set(uint32_t value)
{
    _Bool return_value = true;
    if ((value >> 31))
    {
        return_value = false;
    }

    return (return_value);
}

/**
 * @brief Returns true, if no more bits than specified by spec are set in the value
 *
 * @param value Value to be tested
 * @param spec Number of LSBs that can be set. If a higher bit is set, the function returns false
 * @return _Bool
 */
_Bool uz_adcMax11331_check_32_bit_int_if_not_more_sign_bits_set_than_spec(uint32_t value, uint32_t spec)
{
    _Bool return_value = true;
    if (value >> spec)
    {
        return_value = false;
    }

    return (return_value);
}

#endif
