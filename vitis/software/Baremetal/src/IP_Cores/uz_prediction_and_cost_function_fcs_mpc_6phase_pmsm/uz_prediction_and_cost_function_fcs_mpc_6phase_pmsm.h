#ifndef UZ_PREDICTION_AND_COST_FUNCTION_FCS_MPC_6PHASE_PMSM_H
#define UZ_PREDICTION_AND_COST_FUNCTION_FCS_MPC_6PHASE_PMSM_H
#include <stdint.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"

/**
 * @brief Object data type definition of the prediction_and_cost_function_fcs_mpc_6phase_pmsm IP-Core driver
 *
 */
typedef struct uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t;

struct uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
    float psiPM; /**< flux linkage in Vs */
    float Lq; /**< q-axis inductance in H */
    float Ld; /**< d-axis inductance in H */
    float Rs; /**< phase resistance in Ohm */
    float SampleTime; /**< Value of the Sample time for the 6 phase pmsm modell*/
    float pole_pairs; /**< number of pole_pairs */
    float Lx; /**< x-axis inductance in H */
    float Ly; /**< y-axis inductance in H */
    float id_ref; /**< d-axis reference current value in A */
    float iq_ref; /**< q-axis reference current value in A */
    float ix_ref; /**< x-axis reference current value in A */
    float iy_ref; /**< y-axis reference current value in A */
    _Bool use_AXI; /**< true when AXI_values in use */
}; 

 struct uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_AXI_values_t{
    float d_voltage_per_switching_state_AXI; /**< d-axis voltage for a respective switching state of the inverter */ 
    float q_voltage_per_switching_state_AXI; /**< q-axis voltage for a respective switching state of the inverter */
    float x_voltage_per_switching_state_AXI; /**< x-axis voltage for a respective switching state of the inverter */
    float y_voltage_per_switching_state_AXI; /**< y-axis voltage for a respective switching state of the inverter */
    float id_k_1_AXI; /**< predicted d-axis current via delay compensation */
    float iq_k_1_AXI; /**< predicted q-axis current via delay compensation */
    float ix_k_1_AXI; /**< predicted x-axis current via delay compensation */
    float iy_k_1_AXI; /**< predicted y-axis current via delay compensation */
    float omega_m_measured_AXI; /**< omega_mech */
 };

 /**
 * @brief Initialize an instance of the driver for the prediction_and_cost_function_fcs_mpc_6phase_pmsm IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* Pointer to an initialized instance of the driver
 */
uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_init(struct uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_config_t config);

/** 
 * @brief Initialize AXI_values for d_voltage_per_switching_state_AXI, q_voltage_per_switching_state_AXI, x_voltage_per_switching_state_AXI, y_voltage_per_switching_state_AXI, id_k_1_AXI, iq_k_1_AXI, ix_k_1_AXI, iy_k_1_AXI and omega_m_measured_AXI
 * @param self Pointer to driver instance
 * @param AXI_values AXI values for the instance 
*/
void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_set_AXI_values(uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* self, struct uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_AXI_values_t AXI_values);

/**
 * @brief Read the cost function output J_AXI from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return float
 */
float uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_get_J_AXI(uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* self);

#endif // UZ_PREDICTION_AND_COST_FUNCTION_FCS_MPC_6PHASE_PMSM_H
