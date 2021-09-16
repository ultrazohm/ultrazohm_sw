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
            condition = uz_adcLtc2311_hw_read_cr(base_address) & UZ_ADCLTC2311_CR_CONV_VALUE_VALID;
            if (--l_max_attempts <= 0) {
                return_value = UZ_FAILURE;
                break;
            }
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