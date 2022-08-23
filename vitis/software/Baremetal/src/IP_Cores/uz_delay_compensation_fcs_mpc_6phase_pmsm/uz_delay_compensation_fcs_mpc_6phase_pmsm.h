#ifndef UZ_DELAY_COMPENSATION_FCS_MPC_6PHASE_PMSM_H
#define UZ_DELAY_COMPENSATION_FCS_MPC_6PHASE_PMSM_H
#include <stdint.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"

/**
 * @brief Object data type definitions of the output AXI_values for the delay_compensation_fcs_mpc_6phase_pmsm IP-Core driver
 * 
 */
typedef struct uz_6ph_idk1_iqk1_ixk1_iyk1_t{
    float id_k_1;    /**< Amplitude of the predicted id component */
    float iq_k_1;     /**< Amplitude of the predicted iq component */
    float ix_k_1;        /**< Amplitude of the predicted ix component */
    float iy_k_1;        /**< Amplitude of the predicted iy component */
}uz_6ph_idk1_iqk1_ixk1_iyk1_t;


/**
 * @brief Object data type definition of the delay_compensation_fcs_mpc_6phase IP-Core driver
 *
 */
typedef struct uz_delay_compensation_fcs_mpc_6phase_t uz_delay_compensation_fcs_mpc_6phase_t;

struct uz_delay_compensation_fcs_mpc_6phase_config_t{
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
    _Bool use_AXI; /**< true when AXI_values in use */
};  

 struct uz_delay_compensation_fcs_mpc_6phase_AXI_values_t{
    float last_applied_optimal_voltage_ud; /**< last applied optimal voltge ud */ 
    float last_applied_optimal_voltage_uq; /**< last applied optimal voltge uq */
    float last_applied_optimal_voltage_ux; /**< last applied optimal voltge ux */
    float last_applied_optimal_voltage_uy; /**< last applied optimal voltge uy */
    float id_measured; /**< id current */
    float iq_measured; /**< iq current */
    float ix_measured; /**< ix current */
    float iy_measured; /**< iy current */
    float omega_m_measured; /**< omega_mech */
 };

/**
 * @brief Initialize an instance of the driver for the delay_compensation_fcs_mpc_6phase_pmsm IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_delay_compensation_fcs_mpc_6phase_t* Pointer to an initialized instance of the driver
 */
uz_delay_compensation_fcs_mpc_6phase_t* uz_delay_compensation_fcs_mpc_6phase_init(struct uz_delay_compensation_fcs_mpc_6phase_config_t config);

/** 
 * @brief Initialize AXI_values for id_k_1, iq_k_q, ix_k_1, last_applied_optimal_voltage_ud, last_applied_optimal_voltage_uq, last_applied_optimal_voltage_ux, last_applied_optimal_voltage_uy and omega_mech
 * @param self Pointer to driver instance
 * @param AXI_values AXI values for the instance 
*/
void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_AXI_values(uz_delay_compensation_fcs_mpc_6phase_t* self, struct uz_delay_compensation_fcs_mpc_6phase_AXI_values_t AXI_values);

/**
 * @brief Read the predicted output currents id_k_1, iq_k_1, ix_k_1 and iy_k_1 from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return uz_6ph_idk1_iqk1_ixk1_iyk1_t
 */
uz_6ph_idk1_iqk1_ixk1_iyk1_t uz_delay_compensation_fcs_mpc_6phase_pmsm_read_idk1_iqK1_ixk1_iyk1(uz_delay_compensation_fcs_mpc_6phase_t* self);

#endif // UZ_DELAY_COMPENSATION_FCS_MPC_6PHASE_PMSM_H
