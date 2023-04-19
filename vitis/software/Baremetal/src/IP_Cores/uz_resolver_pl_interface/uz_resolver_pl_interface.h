#ifndef UZ_RESOLVER_PL_INTERFACE_H
#define UZ_RESOLVER_PL_INTERFACE_H
#include <stdint.h>

/**
 * @brief Data type for object uz_resolver_pl_interface
 *
 */
typedef struct uz_resolver_pl_interface_t uz_resolver_pl_interface_t;

/**
 * @brief Configuration struct for uz_resolver_pl_interface
 *
 */
struct uz_resolver_pl_interface_config_t {
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
};

/**
 * @brief Initializes an instance of the uz_resolver_pl_interface driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_resolver_pl_interface_t* uz_resolver_pl_interface_init(struct uz_resolver_pl_interface_config_t config);

#endif // UZ_RESOLVER_PL_INTERFACE_H
