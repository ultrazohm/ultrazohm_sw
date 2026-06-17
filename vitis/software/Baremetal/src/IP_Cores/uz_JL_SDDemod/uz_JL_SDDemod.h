
#ifndef UZ_JL_SDDEMOD_H
#define UZ_JL_SDDEMOD_H
#include <stdint.h>
#include <stdbool.h>

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
    uint16_t clk_ratio;
    bool switch_clk;
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
 * @brief Set the clock ratio
 * 
 * @param self Pointer to driver instance
 * @param clk_ratio Clock ratio value
 */
void uz_JL_SDDemod_set_clk_ratio(uz_JL_SDDemod_t *self, uint16_t clk_ratio);

/**
 * @brief Set the switch clock
 * 
 * @param self Pointer to driver instance
 * @param switch_clk Switch clock value
 */
void uz_JL_SDDemod_set_switch_clk(uz_JL_SDDemod_t *self, bool switch_clk);

/**
 * @brief Get Outputs
 * 
 */
struct uz_JL_SDDemod_output_t uz_JL_SDDemod_get_outputs(uz_JL_SDDemod_t *self);


#endif // UZ_JL_SDDEMOD_H
