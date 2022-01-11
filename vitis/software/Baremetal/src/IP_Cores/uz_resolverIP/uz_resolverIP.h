#ifndef UZ_RESOLVERIP_H
#define UZ_RESOLVERIP_H
#include <stdint.h>


/**
 * @brief Data type for object resolverIP
 *
 */
typedef struct uz_resolverIP_t uz_resolverIP_t;


/**
 * @brief Configuration struct for resolverIP
 *
 */
struct uz_resolverIP_config_t{

    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */

};


/**
 * @brief Initializes an instance of the resolverIP driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_resolverIP_t* uz_resolverIP_init(struct uz_resolverIP_config_t config);


/**

 * @brief Calculates C=A*B
 *
 * @param self Pointer to IP-Core instance that was initialized with init function
 * @param A First factor
 * @param B Second factor
 * @return Product of A times B
 */
int32_t uz_resolverIP_multiply(uz_resolverIP_t* self, int32_t A, int32_t B);


#endif // UZ_RESOLVERIP_H
