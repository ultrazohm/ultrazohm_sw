#ifndef uz_inverter_3ph_H
#define uz_inverter_3ph_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Object data type definition of the inverter model IP-Core driver
 * 
 */
typedef struct uz_inverter_3ph_t uz_inverter_3ph_t;

/**
 * @brief Configuration struct for the Inverter model IP-Core driver
 * 
 */
struct uz_inverter_3ph_config_t
{
    uint32_t base_address; /**< Base address of the IP-Core instance to which the driver is coupled */
    uint32_t ip_core_frequency_Hz; /**< Clock frequency of IP-Core */

    bool switch_pspl_abc; 
    bool switch_pspl_gate; 
    float udc;
};

/**
 * @brief Initialize an instance of the driver
 * 
 * @param config Config struct
 * @return uz_inverter_3ph_t* Pointer to an initialized instance of the driver
 */
uz_inverter_3ph_t *uz_inverter_3ph_init(struct uz_inverter_3ph_config_t config);

/**
 * @brief Struct to be used to pass gate signals to the inverter Model
 * 
 */
struct uz_inverter_3ph_u_abc_ps_t{
    float u_ab; /**< Phase voltage ab from Inverter model as a voltage */
    float u_bc; /**< Phase voltage bc from Inverter model as a voltage */
    float u_ca; /**< Phase voltage ca from Inverter model as a voltage */
};

/**
 * @brief Takes the values of the AXI shadow register and pass them to the actual output.
 * 
 * @param self 
 */
void uz_inverter_3ph_trigger_u_abc_ps_strobe(uz_inverter_3ph_t *self);

/**
 * @brief Returns outputs 
 * 
 * @param self Pointer to driver instance
 * @return  uz_inverter_3ph_Uabc_t Output values
 */
struct uz_inverter_3ph_u_abc_ps_t uz_inverter_3ph_get_u_abc_ps(uz_inverter_3ph_t *self);

/**
 * @brief Struct to be used to pass gate signals to the inverter Model
 * 
 */
struct uz_inverter_3ph_i_abc_ps_t{
    float i_a; /**< Current a for Inverter circuit as an ampere */
    float i_b; /**< Current b for Inverter circuit as an ampere */
    float i_c; /**< Current c for Inverter circuit as an ampere */
};

/**
 * @brief Takes the values of the AXI shadow register and pass them to the actual input.
 * 
 * @param self 
 */
void uz_inverter_3ph_trigger_i_abc_ps_strobe(uz_inverter_3ph_t *self);

/**
 * @brief Set inputs of the model and write them to the Inverter model IP-Core
 * 
 * @param self Pointer to driver instance
 * @param Iabc Inputs to be written to IP-Core
 */
void uz_inverter_3ph_set_i_abc_ps(uz_inverter_3ph_t *self,struct uz_inverter_3ph_i_abc_ps_t Iabc);

/**
 * @brief Struct to be used to pass gate signals to the inverter Model
 * 
 */
struct uz_inverter_3ph_gate_ps_t{
    float gate1; /**< Gate 1 Signal for Inverter circuit */
    float gate2; /**< Gate 2 Signal for Inverter circuit*/
    float gate3; /**< Gate 3 Signal for Inverter circuit */
    float gate4; /**< Gate 4 Signal for Inverter circuit */
    float gate5; /**< Gate 5 Signal for Inverter circuit */
    float gate6; /**< Gate 6 Signal for Inverter circuit */
};

/**
 * @brief Takes the values of the AXI shadow register and pass them to the actual input.
 * 
 * @param self 
 */
void uz_inverter_3ph_trigger_gate_ps_strobe(uz_inverter_3ph_t *self);


/**
 * @brief Set inputs of the model and write them to the Inverter model IP-Core
 * 
 * @param self Pointer to driver instance
 * @param G Inputs to be written to IP-Core
 */
void uz_inverter_3ph_set_gate_ps(uz_inverter_3ph_t *self,struct uz_inverter_3ph_gate_ps_t G);





#endif // uz_inverter_3ph_H
