#include "uz_adcLtc2311_private_utilities.h"
#include "uz_adcLtc2311_hw.h"
#include "uz_adcLtc2311.h"
#include "../../uz/uz_HAL.h"

uint32_t uz_adcLtc2311_cr_wait_for_value_acknowledgement(uint32_t base_address, uint32_t max_attempts)
{
    uint32_t l_max_attempts = max_attempts;
    uint32_t return_value = UZ_SUCCESS;
    // Wait for max_attempts if set otherwise wait forever until the condition is zero
    // Condition == zero means that the hardware has updated the value
    uint32_t condition = uz_adcLtc2311_hw_read_cr(base_address) & UZ_ADCLTC2311_CR_CONV_VALUE_VALID;
    if (l_max_attempts > 0)
    {
        while (condition)
        {
            if (--l_max_attempts <= 0)
            {
                return_value = UZ_FAILURE;
                break;
            }
            condition = uz_adcLtc2311_hw_read_cr(base_address) & UZ_ADCLTC2311_CR_CONV_VALUE_VALID;
        }
    }
    else
    {
        while (condition)
        {
            condition = uz_adcLtc2311_hw_read_cr(base_address) & UZ_ADCLTC2311_CR_CONV_VALUE_VALID;
        }
    }

    return (return_value);
}

uint32_t uz_adcLtc2311_spi_cr_wait_for_control_set_acknowledgement(uint32_t base_address, uint32_t max_attempts)
{
    uint32_t l_max_attempts = max_attempts;
    uint32_t return_value = UZ_SUCCESS;
    // Wait for max_attempts if set otherwise wait forever until the condition is zero
    // Condition != zero means that the hardware transitioned to manual control mode
    uint32_t condition = uz_adcLtc2311_hw_read_spi_cr(base_address) & UZ_ADCLTC2311_SPI_CR_CONTROL_STATUS;
    if (l_max_attempts > 0)
    {
        while (condition == 0)
        {
            if (--l_max_attempts <= 0)
            {
                return_value = UZ_FAILURE;
                break;
            }
            condition = uz_adcLtc2311_hw_read_spi_cr(base_address) & UZ_ADCLTC2311_SPI_CR_CONTROL_STATUS;
        }
    }
    else
    {
        while (condition == 0)
        {
            condition = uz_adcLtc2311_hw_read_spi_cr(base_address) & UZ_ADCLTC2311_SPI_CR_CONTROL_STATUS;
        }
    }

    return (return_value);
}

uint32_t uz_adcLtc2311_spi_cr_wait_for_control_reset_acknowledgement(uint32_t base_address, uint32_t max_attempts)
{
    uint32_t l_max_attempts = max_attempts;
    uint32_t return_value = UZ_SUCCESS;
    // Wait for max_attempts if set otherwise wait forever until the condition is zero
    // Condition == zero means that the hardware left manual mode
    uint32_t condition = uz_adcLtc2311_hw_read_spi_cr(base_address) & UZ_ADCLTC2311_SPI_CR_CONTROL_STATUS;
    if (l_max_attempts > 0)
    {
        while (condition)
        {
            if (--l_max_attempts <= 0)
            {
                return_value = UZ_FAILURE;
                break;
            }
            condition = uz_adcLtc2311_hw_read_spi_cr(base_address) & UZ_ADCLTC2311_SPI_CR_CONTROL_STATUS;
        }
    }
    else
    {
        while (condition)
        {
            condition = uz_adcLtc2311_hw_read_spi_cr(base_address) & UZ_ADCLTC2311_SPI_CR_CONTROL_STATUS;
        }
    }

    return (return_value);
}

/**
 * @brief Returns true if the MSB of value is not set
 * 
 * @param value value to be tested
 * @return _Bool 
 */
_Bool uz_adcLtc2311_check_32_bit_int_if_msb_not_set(uint32_t value)
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
_Bool uz_adcLtc2311_check_32_bit_int_if_not_more_sign_bits_set_than_spec(uint32_t value, uint32_t spec)
{
    _Bool return_value = true;
    if (value >> spec)
    {
        return_value = false;
    }

    return (return_value);
}

void uz_adcLtc2311_spi_set_ss_n(uint32_t base_address)
{
    uint32_t spi_cr = uz_adcLtc2311_hw_read_spi_cr(base_address) | UZ_ADCLTC2311_SPI_CR_SS_N;
    uz_adcLtc2311_hw_write_spi_cr(base_address, spi_cr);
}

void uz_adcLtc2311_spi_reset_ss_n(uint32_t base_address)
{
    uint32_t spi_cr = uz_adcLtc2311_hw_read_spi_cr(base_address) & ~UZ_ADCLTC2311_SPI_CR_SS_N;
    uz_adcLtc2311_hw_write_spi_cr(base_address, spi_cr);
}

void uz_adcLtc2311_spi_set_sclk(uint32_t base_address)
{
    uint32_t spi_cr = uz_adcLtc2311_hw_read_spi_cr(base_address) | UZ_ADCLTC2311_SPI_CR_SCLK;
    uz_adcLtc2311_hw_write_spi_cr(base_address, spi_cr);
}

void uz_adcLtc2311_spi_reset_sclk(uint32_t base_address)
{
    uint32_t spi_cr = uz_adcLtc2311_hw_read_spi_cr(base_address) & ~UZ_ADCLTC2311_SPI_CR_SCLK;
    uz_adcLtc2311_hw_write_spi_cr(base_address, spi_cr);
}

uint32_t uz_adcLtc2311_prepare_manual_operation(uz_adcLtc2311_t *self)
{
    uint32_t base_address = uz_adcLtc2311_get_base_address(self);
    // leave continuous mode because a transition to manual mode is only possible from triggered mode
    uz_adcLtc2311_set_triggered_mode(self);
    // select the masters that shall enter manual mode
    uz_adcLtc2311_hw_write_master_channel(base_address, uz_adcLtc2311_get_master_select(self));
    // set default values for SPI signals
    uz_adcLtc2311_spi_set_ss_n(base_address);
    uz_adcLtc2311_spi_set_sclk(base_address);

    // activate manual control mode and wait for acknowledgement
    uint32_t spi_cr = uz_adcLtc2311_hw_read_spi_cr(base_address) | UZ_ADCLTC2311_SPI_CR_CONTROL;
    uz_adcLtc2311_hw_write_spi_cr(base_address, spi_cr);
    uint32_t return_value = uz_adcLtc2311_spi_cr_wait_for_control_set_acknowledgement(base_address, uz_adcLtc2311_get_max_attempts(self));
    return (return_value);
}

uint32_t uz_adcLtc2311_disable_manual_mode(uint32_t base_address, uint32_t max_attempts)
{
    uint32_t spi_cr = uz_adcLtc2311_hw_read_spi_cr(base_address) & ~UZ_ADCLTC2311_SPI_CR_CONTROL;
    uz_adcLtc2311_hw_write_spi_cr(base_address, spi_cr);
    uint32_t return_value = uz_adcLtc2311_spi_cr_wait_for_control_reset_acknowledgement(base_address, max_attempts);
    return (return_value);
}

uint32_t uz_adcLtc2311_all_masked_bits_set_in_value(uint32_t value, uint32_t mask)
{
    uint32_t return_value = UZ_SUCCESS;

    for (uint32_t i = 0U; i < sizeof(value); i++)
    {

        if (mask & (1U << i))
        {
            if ((value & (1U << i)) == 0U)
            {
                return_value = UZ_FAILURE;
                break;
            }
        }
    }

    return (return_value);
}

/**
 * @brief Updates all operation parameters and sets triggered mode. Intended to use in the init function
 * 
 * @param self 
 */
void uz_adcLtc2311_init_set_parameters(uz_adcLtc2311_t *self)
{
    uint32_t return_value = UZ_SUCCESS;
    uz_adcLtc2311_set_trigger_mode(self);
    return_value = uz_adcLtc2311_update_conversion_factor(self);
    uz_assert(return_value == UZ_SUCCESS);
    return_value = uz_adcLtc2311_update_offset(self);
    uz_assert(return_value == UZ_SUCCESS);
    return_value = uz_adcLtc2311_update_samples(self);
    uz_assert(return_value == UZ_SUCCESS);
    return_value = uz_adcLtc2311_update_sample_time(self);
    uz_assert(return_value == UZ_SUCCESS);
    uz_adcLtc2311_update_spi(self);
}