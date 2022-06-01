#ifndef UZ_TRANS_DQ_ALPHABETA_123_H
#define UZ_TRANS_DQ_ALPHABETA_123_H
#include <stdint.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"

/**
 * @brief Object data type definition of the dq IP-Core driver
 *
 */
typedef struct uz_dq_alphabeta_123_IPcore_t uz_dq_alphabeta_123_IPcore_t;

struct uz_dq_alphabeta_123_IPcore_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
    float theta_offset; /**< Offset of encoder to alpha-axis */
    float id_ref; 
    float iq_ref;
};

/**
 * @brief Initialize an instance of the driver for the dq-IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_dqIPcore_t* Pointer to an initialized instance of the driver
 */
uz_dq_alphabeta_123_IPcore_t* uz_dq_alphabeta_123_IPcore_init(struct uz_dq_alphabeta_123_IPcore_config_t config);

struct uz_dq_alphabeta_123_IPcore_update_t{
    uint32_t base_address;
    float idref;
    float iqref;
};

/** 
 * @brief Initialize update for idref and iqref
 * 
 * @param update Update struct for the instance 
 * @return 0
*/

uz_dq_alphabeta_123_IPcore_t* uz_dq_alphabeta_123_IPcore_idref_iqref_update(struct uz_dq_alphabeta_123_IPcore_update_t update);

/**
 * @brief Read the output currents ia and ib and ic from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 *
 */

uz_3ph_abc_t uz_dq_alphabeta_123_IPcore_get_i_abc(uz_dq_alphabeta_123_IPcore_t* self);

/**
 * @brief Read the output currents ialpha and ibeta from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return uz_alphabeta_t
 */
uz_3ph_alphabeta_t uz_dq_alphabeta_123_IPcore_get_ialpha_ibeta(uz_dq_alphabeta_123_IPcore_t* self);


#endif // UZ_TRANS_DQ_ALPHABETA_123_H
