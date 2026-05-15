
#ifndef UZ_JL_INVMODEL_PT1_H
#define UZ_JL_INVMODEL_PT1_H

#include <stdint.h>

/**
 * @brief Object definition pf the inverter model PT1 IP Core
 * 
 */
typedef struct uz_JL_invModel_PT1_t  uz_JL_invModel_PT1_t;

/**
 * @brief Configuration struct of inverter model PT1 IP-Core
 * 
 */

struct  uz_JL_invModel_PT1_config_t
{
    uint32_t base_adress;
    uint32_t ip_core_frequency_Hz;
    float gain;
    float time_constant;
};

/**
 * @brief Outoput struct of the inverter model PT1 IP-Core
 * 
 */
struct uz_JL_invModel_PT1_output_t
{
    float Ua;
    float Ub;
    float Uc;
};

/**
 * @brief Initialize an instance of the driver
 * 
 * @param config Configuration struct
 * @return uz_plantPT1_t* Pointer to initialized instance of driver
 */
uz_JL_invModel_PT1_t *uz_JL_invModel_PT1_init(struct uz_JL_invModel_PT1_config_t config);

/**
 * @brief Resets the integrator of the PT1 once.
 * 
 * @param self Pointer to driver instance that is reset
 */
void uz_JL_invModel_PT1_reset_integrator(uz_JL_invModel_PT1_t *self);

/**
 * @brief Set the input voltages alpha and beta for inverter model PT1
 * 
 * @param self Pointer to driver instance
 * @param input_value
 */
void uz_JL_invModel_PT1_set_input(uz_JL_invModel_PT1_t *self, float Ualpha, float Ubeta);

/**
 * @brief Set the gain of the PT1
 * 
 * @param self Pointer to driver instance
 * @param gain
 */
void uz_JL_invModel_PT1_set_gain(uz_JL_invModel_PT1_t *self, float gain);

/**
 * @brief Set the time constant of the PT1
 * 
 * @param self Pointer to driver instance
 * @param time_constant 
 */
void uz_JL_invModel_PT1_set_time_constant(uz_JL_invModel_PT1_t *self, float time_constant);


/**
 * @brief Read the output voltages of the inverter model PT1
 * 
 */
struct uz_JL_invModel_PT1_output_t uz_JL_invModel_PT1_get_outputs(uz_JL_invModel_PT1_t *self);

/**
 * @brief Trigger Output update of the inverter model PT1
 * 
 */
void uz_JL_invModel_PT1_trigger_output_strobe(uz_JL_invModel_PT1_t *self);


#endif // UZ_JL_INVMODEL_PT1_H
