#ifndef UZ_ERRORHANDLER_H
#define UZ_ERRORHANDLER_H

#include <stdint.h>

/**
 * @brief Data type for object errorhandler
 *
 */
typedef struct uz_errorhandler_t uz_errorhandler_t;

/**
 * @brief Configuration struct for errorhandler
 *
 */
struct uz_errorhandler_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
//    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
};

/**
 * @brief Initializes an instance of the errorhandler driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_errorhandler_t* uz_errorhandler_init(struct uz_errorhandler_config_t config);

/**
 * @brief Sets a new error with the indicated code
 *
 * @param self Pointer to IP-Core instance that was initialized with init function
 * @param error Error code/id to set for th IP
 */
void uz_errorhandler_setError(uz_errorhandler_t* self, int32_t error);

/**
 * @brief Returns the error code established in the IP from software
 * 		  drivers (with AXI interface) or directly from the PL.
 *
 * @param self Pointer to IP-Core instance that was initialized with init function
 * @return The error code
 */
int32_t uz_errorhandler_getError(uz_errorhandler_t* self);

/**
 * @brief Sets a new mask to enable/disable errors
 *
 * @param self Pointer to IP-Core instance that was initialized with init function
 * @param mask The new mask
 */
void uz_errorhandler_setMask(uz_errorhandler_t* self, int32_t mask);

/**
 * @brief Returns the current mask set in the IP from software
 * 		 (with AXI interface).
 *
 * @param self Pointer to IP-Core instance that was initialized with init function
 * @return The current IP mask
 */
int32_t uz_errorhandler_getMask(uz_errorhandler_t* self);

#endif // UZ_ERRORHANDLER_H
