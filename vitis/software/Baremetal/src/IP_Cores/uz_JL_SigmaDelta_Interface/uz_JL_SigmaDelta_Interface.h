
#ifndef UZ_JL_SigmaDelta_Interface_H
#define UZ_JL_SigmaDelta_Interface_H
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Data typ for SigmaDelta_Interface IP Core
 * 
 */
typedef struct uz_JL_SigmaDelta_Interface_t uz_JL_SigmaDelta_Interface_t;

/**
 * @brief Configuration Struct
 * 
 */
struct uz_JL_SigmaDelta_Interface_config_t{
    uint32_t base_address;
    uint32_t ip_clk_frequency_Hz;
    uint16_t dezimation;
    uint16_t clk_ratio;
    uint8_t filt_input_delay;
    uint8_t switch_edge;
    bool dsw_clk_en;
    float clk_dutycycle;
};

/**
 * @brief Output 
 *  
 */
struct uz_JL_SigmaDelta_Interface_output_t
{
    int32_t data_U;
    int32_t data_PH1;
    int32_t data_PH2;
    int32_t data_PH3;
    int32_t data_PH4;
};

struct uz_JL_SigmaDelta_Interface_output_t_float
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
 * @return uz_JL_SigmaDelta_Interface_t* Pointer to initialized instance of driver
 */
uz_JL_SigmaDelta_Interface_t *uz_JL_SigmaDelta_Interface_init(struct uz_JL_SigmaDelta_Interface_config_t config);

/**
 * @brief Determine the falling edge of the clock for sampling the data input: 0: every fallung edge; 1: every even falling edge; 2: every odd falling edge
 * 
 * @param self Pointer to driver instance
 * @param switch_clk Switch clock value
 */
void uz_JL_SigmaDelta_Interface_set_switch_edge(uz_JL_SigmaDelta_Interface_t *self, uint8_t switch_edge);

/**
 * @brief Set the data input sampling delay for the SInc³ filter. The data input is sampled with a delay of filt_input_delay clock cycles after the falling edge of the clock.
 * 
 * @param self Pointer to driver instance
 * @param switch_clk Switch clock value
 */
void uz_JL_SigmaDelta_Interface_set_data_delay(uz_JL_SigmaDelta_Interface_t *self, uint8_t filt_input_delay);

/**
 * @brief Enable the clock for the Sigma Delta Converter
 * 
 * @param self Pointer to driver instance
 * @param switch_clk Switch clock value
 */
void uz_JL_SigmaDelta_Interface_set_dsw_clk_en(uz_JL_SigmaDelta_Interface_t *self, bool dsw_clk_en);

/**
 * @brief Set the dutycycle of the clock for the Sigma Delta Converter. 
 * 
 * @param self Pointer to driver instance
 * @param switch_clk Switch clock value
 */
void uz_JL_SigmaDelta_Interface_set_clk_dutycycle(uz_JL_SigmaDelta_Interface_t *self, float dutycycle);

/**
 * @brief Get Outputs oft the ip Core: data_U, data_PH1, data_PH2, data_PH3, data_PH4
 * 
 */
struct uz_JL_SigmaDelta_Interface_output_t uz_JL_SigmaDelta_Interface_get_outputs(uz_JL_SigmaDelta_Interface_t *self);


#endif // UZ_JL_SigmaDelta_Interface_H
