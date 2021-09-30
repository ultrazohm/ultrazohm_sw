#include "../../uz/uz_global_configuration.h"
#if UZ_ADCLTC2311_MAX_INSTANCES > 0U
#include <stdbool.h>
#include <stdint.h>
#include "../../uz/uz_HAL.h"
#include "uz_adcLtc2311.h"
#include "uz_adcLtc2311_private_utilities.h"
#include "uz_adcLtc2311_hw.h"


struct uz_adcLtc2311_t {
    bool is_ready;
    struct uz_adcLtc2311_config_t config;
};

static size_t instance_counter = 0U;
static uz_adcLtc2311_t instances[UZ_ADCLTC2311_MAX_INSTANCES] = { 0 };

static uz_adcLtc2311_t* uz_adcLtc2311_allocation(void);

static uz_adcLtc2311_t* uz_adcLtc2311_allocation(void){
    uz_assert(instance_counter < UZ_ADCLTC2311_MAX_INSTANCES);
    uz_adcLtc2311_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_adcLtc2311_t* uz_adcLtc2311_init(struct uz_adcLtc2311_config_t config) {
    uz_adcLtc2311_t* self = uz_adcLtc2311_allocation();
    uz_assert_not_zero(config.ip_clk_frequency_Hz);
    uz_assert_not_zero(config.base_address);
    uz_assert(config.napping_spi_masters == 0);
    uz_assert(config.sleeping_spi_masters == 0);
    uz_assert(config.conversion_factor != 0);
    uz_assert(config.cpol != 0);
    uz_assert(config.cpha == 0);
    uz_assert(config.samples > 0);
    self->config = config;
    uz_adcLtc2311_init_set_parameters(self);
    return (self);
}

void uz_adcLtc2311_software_reset(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    uint32_t adc_cr = uz_adcLtc2311_hw_read_cr(self->config.base_address);
    adc_cr |= UZ_ADCLTC2311_CR_SW_RESET;
    uz_adcLtc2311_hw_write_cr(self->config.base_address, adc_cr);
}

void uz_adcLtc2311_software_trigger(uz_adcLtc2311_t* self, uint32_t spi_masters)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    // if no channel is selected with the function call, use the value in the config struct instead
    if(spi_masters == 0)
    {
        uz_adcLtc2311_hw_write_master_channel(self->config.base_address, self->config.master_select);
    }
    else
    {
        uz_adcLtc2311_hw_write_master_channel(self->config.base_address, spi_masters);
    }
    uint32_t adc_cr = uz_adcLtc2311_hw_read_cr(self->config.base_address);
    adc_cr |= UZ_ADCLTC2311_CR_TRIGGER;
    uz_adcLtc2311_hw_write_cr(self->config.base_address, adc_cr);
}

/**
 * @brief Set the continuos operation mode.
 *
 * @param self
 */
void uz_adcLtc2311_set_continuous_mode(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    uint32_t adc_cr = uz_adcLtc2311_hw_read_cr(self->config.base_address);
    adc_cr |= UZ_ADCLTC2311_CR_MODE;
    uz_adcLtc2311_hw_write_cr(self->config.base_address, adc_cr);
}

/**
 * @brief Set the triggered operation mode
 *
 * @param self
 */
void uz_adcLtc2311_set_triggered_mode(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    uint32_t adc_cr = uz_adcLtc2311_hw_read_cr(self->config.base_address);
    adc_cr &= ~UZ_ADCLTC2311_CR_MODE;
    uz_adcLtc2311_hw_write_cr(self->config.base_address, adc_cr);
}

void uz_adcLtc2311_set_master_select(uz_adcLtc2311_t* self, uint32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.master_select = value;
}

void uz_adcLtc2311_set_channel_select(uz_adcLtc2311_t* self, uint32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.channel_select = value;
}

void uz_adcLtc2311_set_conversion_factor(uz_adcLtc2311_t* self, int32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.conversion_factor = value;
}

void uz_adcLtc2311_set_offset(uz_adcLtc2311_t* self, int32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.offset = value;
}

void uz_adcLtc2311_set_samples(uz_adcLtc2311_t* self, uint32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(value > 0);
    uz_assert(uz_adcLtc2311_check_32_bit_int_if_msb_not_set(value));
    self->config.samples = value;
}

void uz_adcLtc2311_set_max_attempts(uz_adcLtc2311_t* self, uint32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.max_attempts = value;
}

void uz_adcLtc2311_set_sample_time(uz_adcLtc2311_t* self, uint32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(uz_adcLtc2311_check_32_bit_int_if_msb_not_set(value));
    self->config.sample_time = value;
}

void uz_adcLtc2311_set_pre_delay(uz_adcLtc2311_t* self, uint32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(
        uz_adcLtc2311_check_32_bit_int_if_not_more_sign_bits_set_than_spec(
            value,
            UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_WIDTH));
    self->config.pre_delay = value;
}

void uz_adcLtc2311_set_post_delay(uz_adcLtc2311_t* self, uint32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(
        uz_adcLtc2311_check_32_bit_int_if_not_more_sign_bits_set_than_spec(
            value,
            UZ_ADCLTC2311_SPI_CFGR_POST_DELAY_WIDTH));
    self->config.post_delay = value;
}

void uz_adcLtc2311_set_clk_div(uz_adcLtc2311_t* self, uint32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(
        uz_adcLtc2311_check_32_bit_int_if_not_more_sign_bits_set_than_spec(
            value,
            UZ_ADCLTC2311_SPI_CFGR_CLK_DIV_WIDTH));
    self->config.clk_div = value;
}

void uz_adcLtc2311_set_cpha(uz_adcLtc2311_t* self, uint32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // CPHA must be 0 for correct operation
    uz_assert(value == 0);
    self->config.cpha = value;
}

void uz_adcLtc2311_set_cpol(uz_adcLtc2311_t* self, uint32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // CPOL must be 1 for correct operation
    uz_assert(value > 0);
    self->config.cpol = value;

}

uint32_t uz_adcLtc2311_get_master_select(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.master_select);
}

uint32_t uz_adcLtc2311_get_channel_select(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.channel_select);
}

int32_t uz_adcLtc2311_get_conversion_factor(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.conversion_factor);
}

int32_t uz_adcLtc2311_get_offset(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.offset);
}

uint32_t uz_adcLtc2311_get_samples(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.samples);
}

uint32_t uz_adcLtc2311_get_max_attempts(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.max_attempts);
}

uint32_t uz_adcLtc2311_get_sample_time(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.sample_time);
}

uint32_t uz_adcLtc2311_get_pre_delay(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.pre_delay);
}

uint32_t uz_adcLtc2311_get_post_delay(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.post_delay);
}

uint32_t uz_adcLtc2311_get_clk_div(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.clk_div);
}

uint32_t uz_adcLtc2311_get_cpha(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.cpha);
}

uint32_t uz_adcLtc2311_get_cpol(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.cpol);
}

uint32_t uz_adcLtc2311_get_napping_masters(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.napping_spi_masters);
}

uint32_t uz_adcLtc2311_get_sleeping_masters(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.sleeping_spi_masters);
}

uint32_t uz_adcLtc2311_get_base_address(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.base_address);
}

uint32_t uz_adcLtc2311_get_error_code(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.error_code);
}

// update functions
int32_t uz_adcLtc2311_update_conversion_factor(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    int32_t return_value = UZ_SUCCESS;
    // Get the current state of the control register
    uint32_t adc_cr = uz_adcLtc2311_hw_read_cr(self->config.base_address);

    // Reset all bits that determine the meaning of the value
    adc_cr &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    // Set the appropriate bits to determine the meaning of the value
    // Set the VALUE_VALID bit as well to trigger the update
    adc_cr |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_0;

    // Perform the actual writing to the hardware registers
    // Selection, which channels shall be updated
    uz_adcLtc2311_hw_write_master_channel(self->config.base_address, self->config.master_select);
	uz_adcLtc2311_hw_write_channel(self->config.base_address, self->config.channel_select);
    // Write the desired factor
    uz_adcLtc2311_hw_write_value(self->config.base_address, self->config.conversion_factor);
	// Trigger the update
    uz_adcLtc2311_hw_write_cr(self->config.base_address, adc_cr);

    // Wait for the acknowledgement
    return_value = uz_adcLtc2311_cr_wait_for_value_acknowledgement(self->config.base_address, self->config.max_attempts);

    return return_value;
}

int32_t uz_adcLtc2311_update_offset(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    int32_t return_value = UZ_SUCCESS;
    // Get the current state of the control register
    uint32_t adc_cr = uz_adcLtc2311_hw_read_cr(self->config.base_address);

    // Reset all bits that determine the meaning of the value
    adc_cr &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    // Set the appropriate bits to determine the meaning of the value
    // Set the VALUE_VALID bit as well to trigger the update
    adc_cr |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID;

    // Perform the actual writing to the hardware registers
    // Selection, which channels shall be updated
    uz_adcLtc2311_hw_write_master_channel(self->config.base_address, self->config.master_select);
	uz_adcLtc2311_hw_write_channel(self->config.base_address, self->config.channel_select);
    // Write the desired factor
    uz_adcLtc2311_hw_write_value(self->config.base_address, self->config.offset);
	// Trigger the update
    uz_adcLtc2311_hw_write_cr(self->config.base_address, adc_cr);

    // Wait for the acknowledgement
    return_value = uz_adcLtc2311_cr_wait_for_value_acknowledgement(self->config.base_address, self->config.max_attempts);

    return return_value;
}

int32_t uz_adcLtc2311_update_samples(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    int32_t return_value = UZ_SUCCESS;
    // Get the current state of the control register
    uint32_t adc_cr = uz_adcLtc2311_hw_read_cr(self->config.base_address);

    // Reset all bits that determine the meaning of the value
    adc_cr &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    // Set the appropriate bits to determine the meaning of the value
    // Set the VALUE_VALID bit as well to trigger the update
    adc_cr |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_1;

    // Perform the actual writing to the hardware registers
    // Selection, which channels shall be updated
    uz_adcLtc2311_hw_write_master_channel(self->config.base_address, self->config.master_select);
    // Write the desired factor
    uz_adcLtc2311_hw_write_value(self->config.base_address, self->config.samples);
	// Trigger the update
    uz_adcLtc2311_hw_write_cr(self->config.base_address, adc_cr);

    // Wait for the acknowledgement
    return_value = uz_adcLtc2311_cr_wait_for_value_acknowledgement(self->config.base_address, self->config.max_attempts);

    return return_value;
}

int32_t uz_adcLtc2311_update_sample_time(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    int32_t return_value = UZ_SUCCESS;
    // Get the current state of the control register
    uint32_t adc_cr = uz_adcLtc2311_hw_read_cr(self->config.base_address);

    // Reset all bits that determine the meaning of the value
    adc_cr &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    // Set the appropriate bits to determine the meaning of the value
    // Set the VALUE_VALID bit as well to trigger the update
    adc_cr |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1;

    // Perform the actual writing to the hardware registers
    // Selection, which channels shall be updated
    uz_adcLtc2311_hw_write_master_channel(self->config.base_address, self->config.master_select);
    // Write the desired factor
    uz_adcLtc2311_hw_write_value(self->config.base_address, self->config.sample_time);
	// Trigger the update
    uz_adcLtc2311_hw_write_cr(self->config.base_address, adc_cr);

    // Wait for the acknowledgement
    return_value = uz_adcLtc2311_cr_wait_for_value_acknowledgement(self->config.base_address, self->config.max_attempts);

    return return_value;
}

void uz_adcLtc2311_update_spi(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    // assemble the content of SPI configuration register and write it
    uint32_t spi_cfgr = (self->config.clk_div << UZ_ADCLTC2311_SPI_CFGR_CLK_DIV_LSB) |
                        (self->config.pre_delay << UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_LSB) |
	                    (self->config.post_delay << UZ_ADCLTC2311_SPI_CFGR_POST_DELAY_LSB);
    uz_adcLtc2311_hw_write_spi_cfgr(self->config.base_address, spi_cfgr);

    // update CPHA and CPOL
    uint32_t spi_cr = uz_adcLtc2311_hw_read_spi_cr(self->config.base_address);
    if (self->config.cpha == 0)
    {
        spi_cr &= ~UZ_ADCLTC2311_SPI_CR_CPHA;
    }
    else
    {
        spi_cr |= UZ_ADCLTC2311_SPI_CR_CPHA;
    }

    if (self->config.cpol == 0)
    {
        spi_cr &= ~UZ_ADCLTC2311_SPI_CR_CPOL;
    }
    else
    {
        spi_cr |= UZ_ADCLTC2311_SPI_CR_CPOL;
    }

    uz_adcLtc2311_hw_write_spi_cr(self->config.base_address, spi_cr);
}

// nap and sleep modes

int32_t uz_adcLtc2311_enter_nap_mode(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    int32_t return_value = UZ_SUCCESS;
    self->config.error_code = 0;

    // Check if masters have been selected for the operation
    if (self->config.master_select == 0)
    {
        return_value = UZ_FAILURE;
        self->config.error_code |= UZ_ADCLTC2311_NS_NO_SELECTION;
    }
    // Check if the selected masters are already in nap or sleep mode
    else if ((self->config.master_select & self->config.napping_spi_masters) ||
    (self->config.master_select & self->config.sleeping_spi_masters))
    {
        return_value = UZ_FAILURE;
        self->config.error_code |= UZ_ADCLTC2311_NS_ALREADY_IN_MODE;
    }
    else
    {
        return_value = uz_adcLtc2311_prepare_manual_operation(self);
        if(return_value == UZ_FAILURE)
        {
            self->config.error_code |= UZ_ADCLTC2311_NS_MAN_MODE_EN_FAILED;
        }
        else
        {
            // perform the hardware action to send the LTC2311 to nap mode
            for (uint32_t i = 0; i < UZ_ADCLTC2311_NAP_PULSES; i++)
            {
				uz_adcLtc2311_spi_set_ss_n(self->config.base_address);
                uz_adcLtc2311_spi_reset_ss_n(self->config.base_address);
			}
			uz_adcLtc2311_spi_set_ss_n(self->config.base_address);

            // capture, which masters entered nap mode
			self->config.napping_spi_masters |= self->config.master_select;

            // signal the hardware that the selected channels are not available
            uint32_t adc_available = uz_adcLtc2311_hw_read_adc_available(self->config.base_address);
            adc_available &= ~(self->config.master_select);
            uz_adcLtc2311_hw_write_adc_available(self->config.base_address, adc_available);

            // Disable manual mode
            return_value = uz_adcLtc2311_disable_manual_mode(self->config.base_address, self->config.max_attempts);
            if (return_value == UZ_FAILURE)
            {
                self->config.error_code |= UZ_ADCLTC2311_NS_MAN_MODE_DIS_FAILED;
            }
        }
    }
    return(return_value);
}

int32_t uz_adcLtc2311_leave_nap_mode(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    int32_t return_value = UZ_SUCCESS;
    self->config.error_code = 0;

    // Check if masters have been selected for the operation
    if (self->config.master_select == 0)
    {
        return_value = UZ_FAILURE;
        self->config.error_code |= UZ_ADCLTC2311_NS_NO_SELECTION;
    }
    // Check if the selected master are not in sleep mode
    else if (self->config.master_select & self->config.sleeping_spi_masters)
    {
        return_value = UZ_FAILURE;
        self->config.error_code |= UZ_ADCLTC2311_NS_NOT_IN_MODE;
    }
    // Check if the selected masters are in nap mode
    else
    {
        return_value = uz_adcLtc2311_all_masked_bits_set_in_value(self->config.napping_spi_masters, self->config.master_select);
        if (return_value == UZ_FAILURE)
        {
            self->config.error_code |= UZ_ADCLTC2311_NS_NOT_IN_MODE;
        }
        else
        {
            return_value = uz_adcLtc2311_prepare_manual_operation(self);
            if (return_value == UZ_FAILURE)
            {
                self->config.error_code |= UZ_ADCLTC2311_NS_MAN_MODE_EN_FAILED;
            }
            else
            {
                // perform the hardware action to wake the LTC2311 from nap mode
                uz_adcLtc2311_spi_reset_sclk(self->config.base_address);
                uz_adcLtc2311_spi_set_sclk(self->config.base_address);

                // capture, which masters left nap mode
                self->config.napping_spi_masters &= ~self->config.master_select;

                // signal the hardware that the selected channels are available
                uint32_t adc_available = uz_adcLtc2311_hw_read_adc_available(self->config.base_address);
                adc_available |= self->config.master_select;
                uz_adcLtc2311_hw_write_adc_available(self->config.base_address, adc_available);

                // Disable manual mode
                return_value = uz_adcLtc2311_disable_manual_mode(self->config.base_address, self->config.max_attempts);
                if (return_value == UZ_FAILURE)
                {
                    self->config.error_code |= UZ_ADCLTC2311_NS_MAN_MODE_DIS_FAILED;
                }
            }
        }
    }
    return(return_value);

}

int32_t uz_adcLtc2311_enter_sleep_mode(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    int32_t return_value = UZ_SUCCESS;
    self->config.error_code = 0;

    // Check if masters have been selected for the operation
    if (self->config.master_select == 0)
    {
        return_value = UZ_FAILURE;
        self->config.error_code |= UZ_ADCLTC2311_NS_NO_SELECTION;
    }
    // Check if the selected masters are already in nap or sleep mode
    else if ((self->config.master_select & self->config.napping_spi_masters) ||
    (self->config.master_select & self->config.sleeping_spi_masters))
    {
        return_value = UZ_FAILURE;
        self->config.error_code |= UZ_ADCLTC2311_NS_ALREADY_IN_MODE;
    }
    else
    {
        return_value = uz_adcLtc2311_prepare_manual_operation(self);
        if(return_value == UZ_FAILURE)
        {
            self->config.error_code |= UZ_ADCLTC2311_NS_MAN_MODE_EN_FAILED;
        }
        else
        {
            // perform the hardware action to send the LTC2311 to sleep mode
            for (uint32_t i = 0; i < UZ_ADCLTC2311_SLEEP_PULSES; i++)
            {
				uz_adcLtc2311_spi_set_ss_n(self->config.base_address);
                uz_adcLtc2311_spi_reset_ss_n(self->config.base_address);
			}
			uz_adcLtc2311_spi_set_ss_n(self->config.base_address);

            // capture, which masters entered sleep mode
			self->config.sleeping_spi_masters |= self->config.master_select;

            // signal the hardware that the selected channels are not available
            uint32_t adc_available = uz_adcLtc2311_hw_read_adc_available(self->config.base_address);
            adc_available &= ~(self->config.master_select);
            uz_adcLtc2311_hw_write_adc_available(self->config.base_address, adc_available);

            // Disable manual mode
            return_value = uz_adcLtc2311_disable_manual_mode(self->config.base_address, self->config.max_attempts);
            if (return_value == UZ_FAILURE)
            {
                self->config.error_code |= UZ_ADCLTC2311_NS_MAN_MODE_DIS_FAILED;
            }
        }
    }
    return(return_value);
}

int32_t uz_adcLtc2311_leave_sleep_mode(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    int32_t return_value = UZ_SUCCESS;
    self->config.error_code = 0;

    // Check if masters have been selected for the operation
    if (self->config.master_select == 0)
    {
        return_value = UZ_FAILURE;
        self->config.error_code |= UZ_ADCLTC2311_NS_NO_SELECTION;
    }
    // Check if the selected master are not in nap mode
    else if (self->config.master_select & self->config.napping_spi_masters)
    {
        return_value = UZ_FAILURE;
        self->config.error_code |= UZ_ADCLTC2311_NS_NOT_IN_MODE;
    }
    // Check if the selected masters are in sleep mode
    else
    {
        return_value = uz_adcLtc2311_all_masked_bits_set_in_value(self->config.sleeping_spi_masters, self->config.master_select);
        if (return_value == UZ_FAILURE)
        {
            self->config.error_code |= UZ_ADCLTC2311_NS_NOT_IN_MODE;
        }
        else
        {
            return_value = uz_adcLtc2311_prepare_manual_operation(self);
            if (return_value == UZ_FAILURE)
            {
                self->config.error_code |= UZ_ADCLTC2311_NS_MAN_MODE_EN_FAILED;
            }
            else
            {
                // perform the hardware action to wake the LTC2311 from sleep mode
                uz_adcLtc2311_spi_reset_ss_n(self->config.base_address);
                uz_adcLtc2311_spi_set_ss_n(self->config.base_address);

                // capture, which masters left sleep mode
                self->config.sleeping_spi_masters &= ~self->config.master_select;

                // signal the hardware that the selected channels are available
                uint32_t adc_available = uz_adcLtc2311_hw_read_adc_available(self->config.base_address);
                adc_available |= self->config.master_select;
                uz_adcLtc2311_hw_write_adc_available(self->config.base_address, adc_available);

                // Disable manual mode
                return_value = uz_adcLtc2311_disable_manual_mode(self->config.base_address, self->config.max_attempts);
                if (return_value == UZ_FAILURE)
                {
                    self->config.error_code |= UZ_ADCLTC2311_NS_MAN_MODE_DIS_FAILED;
                }
            }
        }
    }
    return(return_value);
}

#endif
