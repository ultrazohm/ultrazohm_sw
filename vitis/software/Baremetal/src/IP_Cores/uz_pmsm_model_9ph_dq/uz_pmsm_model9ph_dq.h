#ifndef UZ_PMSM_MODEL9PH_DQ_H
#define UZ_PMSM_MODEL9PH_DQ_H

#include <stdint.h>
#include <stdbool.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"

/**
 * @brief Object data type definition of the PMSM model IP-Core driver
 * 
 */
typedef struct uz_pmsm_model9ph_dq_t uz_pmsm_model9ph_dq_t;

/**
 * @brief Configuration struct for the PMSM model IP-Core driver
 * 
 */
struct uz_pmsm_model9ph_dq_config_t
{
    uint32_t base_address; /**< Base address of the IP-Core instance to which the driver is coupled */
    uint32_t ip_core_frequency_Hz; /**< Clock frequency of IP-Core */
    float polepairs; /**< Pole pairs of the PMSM */
    float r_1; /**< Stator resistance in ohm */
    uz_9ph_dq_t inductance; /**< Subsystem inductances */
    float psi_pm; /**< Linked magnetic flux of PM magnets */
    float friction_coefficient; /**< Linear coefficient of friction */
    float coulomb_friction_constant; /**< Static friction constant */
    float inertia; /**< Inertia of the PMSM */
    bool simulate_mechanical_system; /**< Determine if mechanical system is simulated or speed is an input */
    bool switch_pspl; //true: inputs from PS, false: inputs from PL
};

/**
 * @brief Struct to return and read the outputs of the PMSM Model
 * 
 */
struct uz_pmsm_model9ph_dq_outputs_general_t
{
    float torque; /**< Inner torque of PMSM in Nm*/
    float omega_mech; /**< Rotational speed of PMSM in 1/s*/
    float theta_el; /**< Angle of rotor*/
};

/**
 * @brief Initialize an instance of the driver
 * 
 * @param config Config struct
 * @return uz_pmsm_model9ph_dq_t* Pointer to an initialized instance of the driver
 */
uz_pmsm_model9ph_dq_t *uz_pmsm_model9ph_dq_init(struct uz_pmsm_model9ph_dq_config_t config);

/**
 * @brief Takes the values of the AXI shadow register and pass them to the actual input.
 * 
 * @param self 
 */
void uz_pmsm_model9ph_trigger_voltage_input_strobe(uz_pmsm_model9ph_dq_t *self);

/**
 * @brief Takes the values of the shadow register and pass them to the actual AXI register.
 * 
 * @param self 
 */
void uz_pmsm_model9ph_trigger_voltage_output_strobe(uz_pmsm_model9ph_dq_t *self);

/**
 * @brief Takes the values of the shadow register and pass them to the actual AXI register.
 * 
 * @param self 
 */
void uz_pmsm_model9ph_trigger_current_output_strobe(uz_pmsm_model9ph_dq_t *self);


void uz_pmsm_model9ph_dq_set_voltage(uz_pmsm_model9ph_dq_t *self, uz_9ph_dq_t voltages);

void uz_pmsm_model9ph_dq_set_voltage_unsafe(uz_pmsm_model9ph_dq_t *self, uz_9ph_dq_t voltages);


uz_9ph_dq_t uz_pmsm_model9ph_dq_get_input_voltages(uz_pmsm_model9ph_dq_t *self);

uz_9ph_dq_t uz_pmsm_model9ph_dq_get_input_voltages_unsafe(uz_pmsm_model9ph_dq_t *self);

void uz_pmsm_model9ph_dq_set_inputs_general(uz_pmsm_model9ph_dq_t *self, float omega_mech, float load_torque);

struct uz_pmsm_model9ph_dq_outputs_general_t uz_pmsm_model9ph_dq_get_outputs_general(uz_pmsm_model9ph_dq_t *self);




uz_9ph_dq_t uz_pmsm_model9ph_dq_get_output_currents(uz_pmsm_model9ph_dq_t *self);


void uz_pmsm_model9ph_dq_reset(uz_pmsm_model9ph_dq_t *self);



void uz_pmsm_model9ph_dq_set_use_axi_input(uz_pmsm_model9ph_dq_t *self, bool use_axi);


#endif // uz_pmsm_model9ph_dq_H
