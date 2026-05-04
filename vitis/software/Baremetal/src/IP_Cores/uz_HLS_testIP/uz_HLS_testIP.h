#ifndef UZ_HLS_TESTIP_H
#define UZ_HLS_TESTIP_H
#include <stdint.h>

/**
* @brief Data type for object uz_HLS_testIP
*
*/
typedef struct uz_HLS_testIP uz_HLS_testIP;

/**
* @brief Configuration struct for myTestIP
*
*/
struct uz_HLS_testIP_config_t{
   uint32_t base_address; /**< Base address of the IP-Core */
   uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
};

/**
* @brief Initializes an instance of the myTestIP driver
*
* @param config Configuration values for the IP-Core
* @return Pointer to initialized instance
*/
uz_HLS_testIP* uz_HLS_testIP_init(struct uz_HLS_testIP_config_t config);

/**
* @brief Calculates result=A*B
*
* @param self Pointer to IP-Core instance that was initialized with init function
* @param A First factor
* @param B Second factor
* @return Product of A times B
*/
int32_t uz_HLS_testIP_multiply(uz_HLS_testIP* self, int32_t A, int32_t B);

#endif // UZ_HLS_TESTIP_H