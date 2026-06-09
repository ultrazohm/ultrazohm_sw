
#ifndef UZ_JL_SDDEMOD_H
#define UZ_JL_SDDEMOD_H
#include <stdint.h>

/**
 * @brief Data typ for SDDemod IP Core
 * 
 */
typedef struct uz_JL_SDDemod_t uz_JL_SDDemod_t;

/**
 * @brief Configuration Struct
 * 
 */
struct uz_JL_SDDemod_config_t{
    uint32_t base_address;
    uint32_t ip_clk_frequency_Hz;
    uint16_t R_axi;
};

/**
 * @brief Output 
 *  
 */
struct uz_JL_SDDemod_output_t
{
    int32_t data;
};

/**
 * @brief Initialize an instance of the driver
 * 
 * @param config Configuration struct
 * @return uz_JL_SDDemod_t* Pointer to initialized instance of driver
 */
uz_JL_SDDemod_t *uz_JL_SDDemod_init(struct uz_JL_SDDemod_config_t config);


/**
 * @brief Set the input R_Axi
 * 
 * @param self Pointer to driver instance
 * @param input_value
 */
void uz_JL_SDDemod_set_Raxi(uz_JL_SDDemod_t *self, uint16_t R_axi);



/**
 * @brief Get Outputs
 * 
 */
struct uz_JL_SDDemod_output_t uz_JL_SDDemod_get_outputs(uz_JL_SDDemod_t *self);


#endif // UZ_JL_SDDEMOD_H
