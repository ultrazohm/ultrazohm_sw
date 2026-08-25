
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
    bool switch_cont_disc;
    float clk_dutycycle;
    float start_time_us;
    uint8_t delay_data_valid;
    uint8_t sinc_sample_periods;
    bool use_clk_ext;
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
 * @brief Switch the sampling mode between continuous and discrete operation.
 *
 * @param self Pointer to driver instance
 * @param switch_cont_disc Switch continuous/discrete value
 */
void uz_JL_SigmaDelta_Interface_set_switch_cont_disc(uz_JL_SigmaDelta_Interface_t *self, bool switch_cont_disc);

/**
 * @brief Set the dutycycle of the clock for the Sigma Delta Converter.
 * 
 * @param self Pointer to driver instance
 * @param switch_clk Switch clock value
 */
void uz_JL_SigmaDelta_Interface_set_clk_dutycycle(uz_JL_SigmaDelta_Interface_t *self, float dutycycle);

/**
 * @brief Set the delay (in clock cycles) after which the Data_valid output is asserted following a strobe trigger.
 *
 * @param self Pointer to driver instance
 * @param delay_data_valid Delay in clock cycles
 */
void uz_JL_SigmaDelta_Interface_set_delay_data_valid(uz_JL_SigmaDelta_Interface_t *self, uint8_t delay_data_valid);

/**
 * @brief Set the number of SINC filter sample periods.
 *
 * @param self Pointer to driver instance
 * @param sinc_sample_periods Number of sample periods
 */
void uz_JL_SigmaDelta_Interface_set_sinc_sample_periods(uz_JL_SigmaDelta_Interface_t *self, uint8_t sinc_sample_periods);

/**
 * @brief Enable sampling with an externally supplied clock instead of the internally generated one.
 *
 * @param self Pointer to driver instance
 * @param use_clk_ext Use external clock value
 */
void uz_JL_SigmaDelta_Interface_set_use_clk_ext(uz_JL_SigmaDelta_Interface_t *self, bool use_clk_ext);

/**
 * @brief Get Outputs oft the ip Core: data_U, data_PH1, data_PH2, data_PH3, data_PH4
 *
 */
struct uz_JL_SigmaDelta_Interface_output_t uz_JL_SigmaDelta_Interface_get_outputs(uz_JL_SigmaDelta_Interface_t *self);

/**
 * @brief Check whether the output data of the IP core is currently valid.
 *
 * @param self Pointer to driver instance
 * @return true if the output data is valid, false otherwise
 */
bool uz_JL_SigmaDelta_Interface_is_data_valid(uz_JL_SigmaDelta_Interface_t *self);

/**
 * @brief Reset the counter that counts how often Data_valid has been triggered.
 *
 * @param self Pointer to driver instance
 */
void uz_JL_SigmaDelta_Interface_reset_data_valid_cnt(uz_JL_SigmaDelta_Interface_t *self);

/**
 * @brief Get the current value of the counter that counts how often Data_valid has been triggered.
 *
 * @param self Pointer to driver instance
 * @return uint8_t Current counter value
 */
uint8_t uz_JL_SigmaDelta_Interface_get_data_valid_cnt(uz_JL_SigmaDelta_Interface_t *self);


#endif // UZ_JL_SigmaDelta_Interface_H
