
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
    uint16_t dezimation_U;
    uint16_t dezimation_I;
    uint16_t clk_ratio;
    uint8_t filt_input_delay;
    bool switch_edge;
    bool calib_en;
    bool dsw_clk_en;
    float clk_dutycycle;
};

/**
 * @brief Output 
 *  
 */
struct uz_JL_SDDemod_output_t
{
    int32_t data_U;
    int32_t data_PH1;
    int32_t data_PH2;
    int32_t data_PH3;
    int32_t data_PH4;
};

struct uz_JL_SDDemod_output_t_float
{
    float data_U;
    float data_PH1;
    float data_PH2;
    float data_PH3;
    float data_PH4;
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
void uz_JL_SDDemod_set_dezimation(uz_JL_SDDemod_t *self, uint16_t dezimation_U, uint16_t dezimation_I);


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
void uz_JL_SDDemod_set_switch_edge(uz_JL_SDDemod_t *self, bool switch_edge);

/**
 * @brief Set the switch clock
 * 
 * @param self Pointer to driver instance
 * @param switch_clk Switch clock value
 */
void uz_JL_SDDemod_set_data_delay(uz_JL_SDDemod_t *self, uint8_t filt_input_delay);

/**
 * @brief Set the switch clock
 * 
 * @param self Pointer to driver instance
 * @param switch_clk Switch clock value
 */
void uz_JL_SDDemod_set_calib_en(uz_JL_SDDemod_t *self, bool calib_en);

/**
 * @brief Set the switch clock
 * 
 * @param self Pointer to driver instance
 * @param switch_clk Switch clock value
 */
void uz_JL_SDDemod_set_dsw_clk_en(uz_JL_SDDemod_t *self, bool dsw_clk_en);

/**
 * @brief Set the switch clock
 * 
 * @param self Pointer to driver instance
 * @param switch_clk Switch clock value
 */
void uz_JL_SDDemod_set_clk_dutycycle(uz_JL_SDDemod_t *self, float dutycycle);

/**
 * @brief Get Outputs
 * 
 */
struct uz_JL_SDDemod_output_t uz_JL_SDDemod_get_outputs(uz_JL_SDDemod_t *self);


#endif // UZ_JL_SDDEMOD_H
