#ifndef UZ_PREDICTION_AND_COST_FUNCTION_8_H
#define UZ_PREDICTION_AND_COST_FUNCTION_8_H
#include <stdint.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"

/**
 * @brief Object data type definitions of the reference current values for the prediction_and_cost_function_8 IP-Core driver
 * 
 */
typedef struct uz_6ph_idref_iqref_ixref_iyref_t{
    float id_ref;    /**< Amplitude of the d-phase reference current*/
    float iq_ref;    /**< Amplitude of the q-phase reference current */
    float ix_ref;    /**< Amplitude of the x-phase reference current */
    float iy_ref;    /**< Amplitude of the y-phase reference current */
}uz_6ph_idref_iqref_ixref_iyref_t;

/**
 * @brief Object data type definition of the prediction_and_cost_function_8 IP-Core driver
 *
 */
typedef struct uz_prediction_and_cost_function_8_t uz_prediction_and_cost_function_8_t;

struct uz_prediction_and_cost_function_8_config_t{
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
}; 

 /**
 * @brief Initialize an instance of the driver for the prediction_and_cost_function_8 IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_prediction_and_cost_function_8_t* Pointer to an initialized instance of the driver
 */
uz_prediction_and_cost_function_8_t* uz_prediction_and_cost_function_8_init(struct uz_prediction_and_cost_function_8_config_t config);

/** 
 * @brief Set updated reference currents id_ref, iq_ref, ix_ref and iy_ref
 * @param self Pointer to driver instance
 * @param updated_values AXI values for the instance 
*/
void uz_prediction_and_cost_function_8_idref_iqref_ixref_iyref_update(uz_prediction_and_cost_function_8_t* self, uz_6ph_idref_iqref_ixref_iyref_t updated_values);

/**
 * @brief Read the value of Index_in from the Prediction_and_cost_function IP-Core
 *
 * @param self Pointer to driver instance
 * @return Value of Index
 */
int32_t uz_prediction_and_cost_function_8_read_Index(uz_prediction_and_cost_function_8_t* self);

/**
 * @brief Set the value of done_phase_voltages from the Prediction_and_cost_function IP-Core
 *
 * @param self Pointer to driver instance
 * @param done_phase_voltages_AXI Value
 */
//void uz_prediction_and_cost_function_8_set_done_phase_voltages_AXI(uz_prediction_and_cost_function_8_t* self, _Bool done_phase_voltages_AXI);


/**
 * @brief Set the value of done_vsd_and_park from the Prediction_and_cost_function IP-Core
 *
 * @param self Pointer to driver instance
 * @param done_vsd_and_park_AXI Value
 */
void uz_prediction_and_cost_function_8_set_done_vsd_and_park_AXI(uz_prediction_and_cost_function_8_t* self, _Bool done_vsd_and_park_AXI);


/**
 * @brief Set the value of current_valid_in from the Prediction_and_cost_function IP-Core
 *
 * @param self Pointer to driver instance
 * @param current_valid_in_AXI Value
 */
void uz_prediction_and_cost_function_8_set_current_valid_in_AXI(uz_prediction_and_cost_function_8_t* self, _Bool current_valid_in_AXI);


/**
 * @brief Read the value of done_prediction_and_cost_function from the Prediction_and_cost_function IP-Core
 *
 * @param self Pointer to driver instance
 * @return Value of done_prediction_and_cost_function
 */
_Bool uz_prediction_and_cost_function_8_read_done_prediction_and_cost_function(uz_prediction_and_cost_function_8_t* self);
#endif // UZ_PREDICTION_AND_COST_FUNCTION_8_H
