
#ifndef UZ_JL_INVMODEL_IDEAL_H
#define UZ_JL_INVMODEL_IDEAL_H

#include <stdint.h>

/**
 * @brief Object definition pf the inverter model PT1 IP Core
 * 
 */
typedef struct uz_JL_invModel_ideal_t  uz_JL_invModel_ideal_t;

/**
 * @brief Configuration struct of inverter model PT1 IP-Core
 * 
 */

struct  uz_JL_invModel_ideal_config_t
{
    uint32_t base_adress;
    uint32_t ip_core_frequency_Hz;
    float Udc;
};

/**
 * @brief Outoput struct of the inverter model PT1 IP-Core
 * 
 */
struct uz_JL_invModel_ideal_output_t
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
uz_JL_invModel_ideal_t *uz_JL_invModel_ideal_init(struct uz_JL_invModel_ideal_config_t config);


/**
 * @brief Set the input voltages alpha and beta for inverter model PT1
 * 
 * @param self Pointer to driver instance
 * @param input_value
 */
void uz_JL_invModel_ideal_set_Udc(uz_JL_invModel_ideal_t *self, float Udc);



/**
 * @brief Get Outputs of inverter model ideal IP Core
 * 
 */
struct uz_JL_invModel_ideal_output_t uz_JL_invModel_ideal_get_outputs(uz_JL_invModel_ideal_t *self);


/**
 * @brief Trigger the output strobe of the inverter model ideal IP Core
 * 
 */
void uz_JL_invModel_ideal_trigger_output_strobe(uz_JL_invModel_ideal_t *self);




#endif // UZ_JL_INVMODEL_IDEAL_H
