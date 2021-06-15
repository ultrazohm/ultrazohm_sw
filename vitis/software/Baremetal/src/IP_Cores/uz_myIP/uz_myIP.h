#ifndef UZ_MYIP_H
#define UZ_MYIP_H
#include <stdint.h>

/**
 * @brief Data type for object myIP
 *
 */
typedef struct uz_myIP_t uz_myIP_t;

/**
 * @brief Configuration struct for myIP
 *
 */
struct uz_myIP_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
};

/**
 * @brief Initializes an instance of the myIP driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_myIP_t* uz_myIP_init(struct uz_myIP_config_t config);

/**
 * @brief Calculates C=A*B
 *
 * @param self Pointer to IP-Core instance that was initialized with init function
 * @param A First factor
 * @param B Second factor
 * @return Product of A times B
 */
int32_t uz_myIP_multiply(uz_myIP_t* self, int32_t A, int32_t B);

#endif // UZ_MYIP_H