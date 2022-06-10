#ifndef UZ_TRANS_DQ_ALPHABETA_123_H
#define UZ_TRANS_DQ_ALPHABETA_123_H
#include <stdint.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"

/**
 * @brief Object data type definition of the dq_alphabeta_123 IP-Core driver
 *
 */
typedef struct uz_dq_alphabeta_123_IPcore_t uz_dq_alphabeta_123_IPcore_t;

struct uz_dq_alphabeta_123_IPcore_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
    float theta_offset; /**< Offset of encoder to alpha-axis */
    float id_ref; /**< initial id_ref current of the IP_Core */
    float iq_ref; /**< initial iq_ref current of the IP_Core */
};   

/**
 * @brief Initialize an instance of the driver for the dq_alphabeta_123 IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_dq_alphabeta_123_IPcore_t* Pointer to an initialized instance of the driver
 */
uz_dq_alphabeta_123_IPcore_t* uz_dq_alphabeta_123_IPcore_init(struct uz_dq_alphabeta_123_IPcore_config_t config);

//struct uz_dq_alphabeta_123_IPcore_update_t{
//    uint32_t base_address; /**< Base address of the IP-Core */
//    float idref; /**< update for the idref current in the isr */
//    float iqref; /**< update for the iqref current in the isr */
//};

/** 
 * @brief Initialize update for idref and iqref
 * 
 * @param update Update struct for the instance 
*/

//uz_dq_alphabeta_123_IPcore_t* uz_dq_alphabeta_123_IPcore_idref_iqref_update(struct uz_dq_alphabeta_123_IPcore_update_t update);
void uz_dq_alphabeta_123_IPcore_idref_iqref_update(uz_dq_alphabeta_123_IPcore_t* self, uz_3ph_dq_t updated_values);

/**
 * @brief Read the output currents ia and ib and ic from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return uz_abc_t
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
