#ifndef UZ_COUNT_SWITCHING_IP_H
#define UZ_COUNT_SWITCHING_IP_H


#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Object data type definition of the IP-Core driver
 *
 */
typedef struct uz_count_switching_IP_t uz_count_switching_IP_t;

struct uz_count_switching_IP_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz;
};

/**
 * @brief Initialize an instance of the driver for the IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_count_switching_IPCore_t* Pointer to an initialized instance of the driver
 */
uz_count_switching_IP_t* uz_count_switching_IP_init(struct uz_count_switching_IP_config_t config);


/**
 * @brief Read 
 *
 * @param self Pointer to driver instance
 * @return uint32_t
 */
uint32_t uz_count_switching_IP_get_count(uz_count_switching_IP_t* self, unsigned int num);

uint32_t uz_count_switching_IP_get_count_sum(uz_count_switching_IP_t* self);

void uz_count_switching_IP_set_reset(uz_count_switching_IP_t* self, bool reset);

#endif // UZ_COUNT_SWITCHING_IP_H
