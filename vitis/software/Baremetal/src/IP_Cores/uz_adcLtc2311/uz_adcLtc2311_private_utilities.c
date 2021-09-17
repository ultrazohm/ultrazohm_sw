#include "uz_adcLtc2311_private_utilities.h"
#include "uz_adcLtc2311_hw.h"
#include "uz_adcLtc2311.h"
#include "../../uz/uz_HAL.h"

int32_t uz_adcLtc2311_cr_wait_for_value_acknowledgement(uint32_t base_address, uint32_t max_attempts)
{
    uint32_t l_max_attempts = max_attempts;
    int32_t return_value = UZ_SUCCESS;
    // Wait for max_attempts if set otherwise wait forever until the condition is zero
    // Condition == zero means that the hardware has updated the value
    uint32_t condition = uz_adcLtc2311_hw_read_cr(base_address) & UZ_ADCLTC2311_CR_CONV_VALUE_VALID;
    if (l_max_attempts > 0) {
        while (condition)
        {
            if (--l_max_attempts <= 0) {
                return_value = UZ_FAILURE;
                break;
            }
            condition = uz_adcLtc2311_hw_read_cr(base_address) & UZ_ADCLTC2311_CR_CONV_VALUE_VALID;
        }
    }
    else {
        while (condition)
        {
            condition = uz_adcLtc2311_hw_read_cr(base_address) & UZ_ADCLTC2311_CR_CONV_VALUE_VALID;
        }
    }

    return(return_value);
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

    return(return_value);
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
    if(value >> spec)
    {
        return_value = false;
    }

    return(return_value);

}