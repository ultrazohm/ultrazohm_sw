#ifndef UZ_DELAY_COMPENSATION_8_H
#define UZ_DELAY_COMPENSATION_8_H
#include <stdint.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"


/**
 * @brief Object data type definition of the delay_compensation_8 IP-Core driver
 *
 */
typedef struct uz_delay_compensation_8_t uz_delay_compensation_8_t;

struct uz_delay_compensation_8_config_t{
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
};  

/**
 * @brief Initialize an instance of the driver for the delay_compensation_8 IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_delay_compensation_8_t* Pointer to an initialized instance of the driver
 */
uz_delay_compensation_8_t* uz_delay_compensation_8_init(struct uz_delay_compensation_8_config_t config);

/**
 * @brief Read the output currents id, iq, ix and iy from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return uz_6ph_dq_t
 */
uz_6ph_dq_t uz_delay_compensation_8_read_idk1_iqK1_ixk1_iyk1(uz_delay_compensation_8_t* self);

#endif // UZ_DELAY_COMPENSATION_8_H
