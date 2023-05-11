#ifndef UZ_PMSM_MODEL3PH_H
#define UZ_PMSM_MODEL3PH_H

#include <stdint.h>
#include <stdbool.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"
#include "../../uz/uz_PMSM_config/uz_PMSM_config.h"

/**
 * @brief Object data type definition of the PMSM model IP-Core driver
 * 
 */
typedef struct uz_pmsm_model3ph_t uz_pmsm_model3ph_t;

/*! enum for readable configuring for for the source of voltages */
enum uz_cil_pmsm_input_source {
	src_PS=0, 
	src_PL
	}; 

/*! enum for readable configuring for for the load type */
enum uz_cil_pmsm_load_type {
	set_fixed_rpm=0, 
	set_load_torque}; 

/**
 * @brief Configuration struct for the PMSM model IP-Core driver
 * 
 */
struct uz_pmsm_model3ph_config_t
{
    uint32_t base_address; /**< Base address of the IP-Core instance to which the driver is coupled */
    uint32_t ip_core_frequency_Hz; /**< Clock frequency of IP-Core */
    uz_PMSM_t pmsm; /**< PMSM Config with necessary parameters */
    float friction_coefficient; /**< Linear coefficient of friction */
    float coulomb_friction_constant; /**< Static friction constant */
    enum uz_cil_pmsm_input_source simulate_mechanical_system; /**< Determine if mechanical system is simulated or speed is an input */
    enum uz_cil_pmsm_load_type switch_pspl; /**< true: input voltage from AXI, false: input voltage from PL */
};

/**
 * @brief Struct to return and read the outputs of the PMSM Model
 * 
 */
struct uz_pmsm_model3ph_outputs_t
{
    uz_3ph_dq_t currents; /**< Current in d-axis in A */
    float torque_Nm; /**< Inner torque of PMSM in Nm*/
    float omega_mech_1_s; /**< Rotational speed of PMSM in 1/s*/
    float theta_el; /**<Electrical rotor angle*/
};

/**
 * @brief Struct to be used to pass inputs to the PMSM Model
 * 
 */
struct uz_pmsm_model3ph_inputs_t
{
    uz_3ph_dq_t voltages; /**< Voltage in d-axis in V */
    float omega_mech_1_s; /**< Rotational speed of PMSM in 1/s */
    float load_torque; /**< Applied load torque in Nm */
};

/**
 * @brief Initialize an instance of the driver
 * 
 * @param config Config struct
 * @return uz_pmsm_model3ph_t* Pointer to an initialized instance of the driver
 */
uz_pmsm_model3ph_t *uz_pmsm_model3ph_init(struct uz_pmsm_model3ph_config_t config);

/**
 * @brief Takes the values of the AXI shadow register and pass them to the actual input.
 * 
 * @param self 
 */
void uz_pmsm_model3ph_trigger_input_strobe(uz_pmsm_model3ph_t *self);

/**
 * @brief Takes the values of the shadow register and pass them to the actual AXI register.
 * 
 * @param self 
 */
void uz_pmsm_model3ph_trigger_output_strobe(uz_pmsm_model3ph_t *self);

/**
 * @brief Set inputs of the model and write them to the PMSM model IP-Core
 * 
 * @param self Pointer to driver instance
 * @param inputs Inputs to be written to IP-Core
 */
void uz_pmsm_model3ph_set_inputs(uz_pmsm_model3ph_t *self,struct uz_pmsm_model3ph_inputs_t inputs);

/**
 * @brief Returns current outputs of PMSM model IP-Core
 * 
 * @param self Pointer to driver instance
 * @return struct uz_pmsm_model3ph_outputs_t Output values
 */
struct uz_pmsm_model3ph_outputs_t uz_pmsm_model3ph_get_outputs(uz_pmsm_model3ph_t *self);

/**
 * @brief Resets the PMSM model by writing zero to all inputs and sets integrators to zero
 * 
 * @param self Pointer to driver instance
 */
void uz_pmsm_model3ph_reset(uz_pmsm_model3ph_t *self);

/**
 * @brief Change input source for voltages (PL or PS) during runtime
 * 
 * @param self Pointer to driver instance
 * @param use_axi true: voltages from PS, false: voltages from PL
 */
void uz_pmsm_model_dq_set_use_axi_input(uz_pmsm_model3ph_t *self, bool use_axi);

/**
 * @brief Safe function to read out the set input voltages of PMSM. Works for voltages coming from PS and PL.
 * 
 * @param self
 * @return struct of type uz_3ph_dq_t containing the set voltages
 */
uz_3ph_dq_t uz_pmsm_model3ph_dq_get_input_voltages(uz_pmsm_model3ph_t *self);


#endif // uz_pmsm_model3ph_H
