#ifndef uz_pmsm_model_9ph_H
#define uz_pmsm_model_9ph_H

#include <stdint.h>
#include <stdbool.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"

/**
 * @brief Object data type definition of the PMSM model IP-Core driver
 * 
 */
typedef struct uz_pmsm_model_9ph_t uz_pmsm_model_9ph_t;

/**
 * @brief Configuration struct for the PMSM model IP-Core driver
 * 
 */
struct uz_pmsm_model_9ph_config_t
{
    uint32_t base_address; /**< Base address of the IP-Core instance to which the driver is coupled */
    uint32_t ip_core_frequency_Hz; /**< Clock frequency of IP-Core */
    float polepairs; /**< Pole pairs of the PMSM */
    float r_1; /**< Stator resistance in ohm */
    float L_d; /**< Direct inductance in Henry */
    float L_q; /**< Quadrature inductance in Henry */
    float L_z1; /**< Additional System's inductance in Henry */
    float L_z2; /**< Additional System's inductance in Henry */
    float L_x1; /**< Additional System's inductance in Henry */
    float L_y1; /**< Additional System's inductance in Henry */
    float L_x2; /**< Additional System's inductance in Henry */
    float L_y2; /**< Additional System's inductance in Henry */
    float L_z3; /**< Additional System's inductance in Henry */
    float psi_pm; /**< Linked magnetic flux of PM magnets */
    float friction_coefficient; /**< Linear coefficient of friction */
    float coulomb_friction_constant; /**< Static friction constant */
    float inertia; /**< Inertia of the PMSM */
    bool simulate_mechanical_system; /**< Determine if mechanical system is simulated or speed is an input */
    bool switch_pspl; //true: inputs from PS, false: inputs from PL
    bool control_dq_abc; //true: dq inputs, false: abc inputs
};

/**
 * @brief Struct to return and read the outputs of the PMSM Model
 * 
 */
struct uz_pmsm_model_9ph_outputs_general_t
{
    float torque_Nm; /**< Inner torque of PMSM in Nm*/
    float omega_mech_1_s; /**< Rotational speed of PMSM in 1/s*/
    float theta_el; /**< Angle of rotor*/
    float u_d;
    float u_q;
};

struct uz_pmsm_model_9ph_outputs_dq_t
{
    uz_3ph_dq_t i_dq;
    uz_9ph_alphabeta_t i_subspaces;
};


/**
 * @brief Struct to be used to pass inputs to the PMSM Model
 * 
 */
struct uz_pmsm_model_9ph_inputs_general_t
{
    float omega_mech_1_s; /**< Rotational speed of PMSM in 1/s */
    float load_torque; /**< Applied load torque in Nm */
    float u_d;
    float u_q;
};



/**
 * @brief Initialize an instance of the driver
 * 
 * @param config Config struct
 * @return uz_pmsm_model_9ph_t* Pointer to an initialized instance of the driver
 */
uz_pmsm_model_9ph_t *uz_pmsm_model_9ph_init(struct uz_pmsm_model_9ph_config_t config);

/**
 * @brief Takes the values of the AXI shadow register and pass them to the actual input.
 * 
 * @param self 
 */
void uz_pmsm_model_9ph_trigger_input_general_strobe(uz_pmsm_model_9ph_t *self);

/**
 * @brief Takes the values of the shadow register and pass them to the actual AXI register.
 * 
 * @param self 
 */
void uz_pmsm_model_9ph_trigger_output_general_strobe(uz_pmsm_model_9ph_t *self);

/**
 * @brief Takes the values of the shadow register and pass them to the actual AXI register.
 * 
 * @param self 
 */
void uz_pmsm_model_9ph_trigger_output_currents_dq_strobe(uz_pmsm_model_9ph_t *self);


/**
 * @brief Set inputs of the model and write them to the PMSM model IP-Core
 * 
 * @param self Pointer to driver instance
 * @param inputs Inputs to be written to IP-Core
 */
void uz_pmsm_model_9ph_set_inputs_general(uz_pmsm_model_9ph_t *self, struct uz_pmsm_model_9ph_inputs_general_t inputs);


/**
 * @brief Returns current outputs of PMSM model IP-Core
 * 
 * @param self Pointer to driver instance
 * @return struct uz_pmsm_model_9ph_outputs_t Output values
 */
struct uz_pmsm_model_9ph_outputs_general_t uz_pmsm_model_9ph_get_outputs_general(uz_pmsm_model_9ph_t *self);

/**
 * @brief Returns current outputs of PMSM model IP-Core
 * 
 * @param self Pointer to driver instance
 * @return struct uz_pmsm_model_9ph_outputs_t Output values
 */
struct uz_pmsm_model_9ph_outputs_dq_t uz_pmsm_model_9ph_get_outputs_dq(uz_pmsm_model_9ph_t *self);

/**
 * @brief Resets the PMSM model by writing zero to all inputs and sets integrators to zero
 * 
 * @param self Pointer to driver instance
 */
void uz_pmsm_model_9ph_reset(uz_pmsm_model_9ph_t *self);


#endif // uz_pmsm_model_9ph_H
