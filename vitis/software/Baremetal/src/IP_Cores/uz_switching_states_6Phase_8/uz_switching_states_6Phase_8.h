#ifndef UZ_SWITCHING_STATES_6PHASE_8_H
#define UZ_SWITCHING_STATES_6PHASE_8_H
#include <stdint.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"

/**
 * @brief Object data type definition of the switching_states_6Phase_8 IP-Core driver
 *
 */
typedef struct uz_switching_states_6Phase_8_t uz_switching_states_6Phase_8_t;

struct uz_switching_states_6Phase_8_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
};

/**
 * @brief Initialize an instance of the driver for the switching_states_6Phase_8 IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_switching_states_6Phase_8_t* Pointer to an initialized instance of the driver
 */
uz_switching_states_6Phase_8_t* uz_switching_states_6Phase_8_init(struct uz_switching_states_6Phase_8_config_t config);


/**
 * @brief Read the value of Index_in from the switching_states_6Phase_8 IP-Core
 *
 * @param self Pointer to driver instance
 * @return Value of Index_in
 */
int32_t uz_switching_states_6Phase_8_read_Index_in(uz_switching_states_6Phase_8_t* self);


#endif // UZ_SWITCHING_STATES_6PHASE_8_H
