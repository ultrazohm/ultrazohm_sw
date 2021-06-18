#ifndef UZ_PLANTPT1_H
#define UZ_PLANTPT1_H

/**
 * @brief Object definition of the plant model PT1 IP-Core
 * 
 */
typedef struct uz_plantPT1_t uz_plantPT1_t;

/**
 * @brief Configuration struct for plant PT1 IP-Core
 * 
 */
struct uz_plantPT1_config_t
{
    uint32_t base_address; /**< Base address of IP-Core instance */
    uint32_t ip_core_frequency_Hz; /**< Clock frequency of IP-Core */
    float gain;  /**< Gain of PT1 */
    float time_constant; /**< time constant of the PT1 */
};

/**
 * @brief Initialize an instance of the driver
 * 
 * @param config Configuration struct
 * @return uz_plantPT1_t* Pointer to initialized instance of driver
 */
uz_plantPT1_t *uz_plantPT1_init(struct uz_plantPT1_config_t config);

/**
 * @brief Resets the integrator of the PT1 once.
 * 
 * @param self Pointer to driver instance that is reset
 */
void uz_plantPT1_reset_integrator(uz_plantPT1_t *self);

/**
 * @brief Set the input value u(k) of the PT1
 * 
 * @param self Pointer to driver instance
 * @param input_value
 */
void uz_plantPT1_set_input(uz_plantPT1_t *self, float input_value);

/**
 * @brief Set the gain of the PT1
 * 
 * @param self Pointer to driver instance
 * @param gain
 */
void uz_plantPT1_set_gain(uz_plantPT1_t *self, float gain);

/**
 * @brief Set the time constant of the PT1
 * 
 * @param self Pointer to driver instance
 * @param time_constant 
 */
void uz_plantPT1_set_time_constant(uz_plantPT1_t *self, float time_constant);

/**
 * @brief Reads the output of the PT1
 * 
 * @param self Pointer to driver instance
 * @return float 
 */
float uz_plantPT1_read_output(uz_plantPT1_t *self);

#endif // UZ_PLANTPT1_H
