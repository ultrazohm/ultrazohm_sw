#ifndef UZ_FCS_MPC_3PHASE_SPMSM_H
#define UZ_FCS_MPC_3PHASE_SPMSM_H

#include <stdint.h>

/**
 * @brief Object data type definition of the dq IP-Core driver
 *
 */
typedef struct uz_fcs_mpc_3phase_spmsm_t uz_fcs_mpc_3phase_spmsm_t;

struct uz_fcs_mpc_3phase_spmsm_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
    float u_dc_link; /**< u_dc_link voltage of the 2-level inverter*/
    float SampleTime; /**< Value of the Sample time for the 3 phase spmsm modell*/
    float Rs; /**< phase resistance in Ohm */
    float Ld; /**< d-axis inductance in H */
    float Lq; /**< q-axis inductance in H */
    float psiPM; /**< flux linkage in Vs */
    float pole_pairs; /**< number of pole_pairs */
};

/**
 * @brief Initialize an instance of the driver for the fcs_mpc_3phase_spmsm IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_fcs_mpc_3phase_spmsm_t* Pointer to an initialized instance of the driver
 */
uz_fcs_mpc_3phase_spmsm_t* uz_fcs_mpc_3phase_spmsm_init(struct uz_fcs_mpc_3phase_spmsm_config_t config);

#endif // UZ_FCS_MPC_3PHASE_SPMSM_H
