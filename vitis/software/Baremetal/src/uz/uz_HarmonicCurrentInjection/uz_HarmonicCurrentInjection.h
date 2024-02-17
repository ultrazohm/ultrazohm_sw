#ifndef UZ_HARMONICCURRENTINJECTION_H
#define UZ_HARMONICCURRENTINJECTION_H

#include "../uz_CurrentControl/uz_CurrentControl.h"
#include "../uz_signals/uz_signals.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_PMSM_config/uz_PMSM_config.h"

/*! enum for readable configuring for Mode of the HarmonicCurrentInjection sample function */
enum uz_HarmonicCurrentInjection_mode_select {
    abc_to_dq=0,
    dq_to_dqn    
};

/**
 * @brief Configuration struct for HarmonicCurrentInjection. Accessible by the user
 */
// struct uz_HarmonicCurrentInjection_config {
//     int order_first_harmonic;
//     int order_second_harmonic;
//     enum uz_HarmonicCurrentInjection_mode_select selection;
//     struct uz_CurrentControl_config config_first_harmonic;
//     struct uz_CurrentControl_config config_second_harmonic;
//     struct uz_IIR_Filter_config config_bandpass_first_harmonic_abc;
//     struct uz_IIR_Filter_config config_bandpass_second_harmonic_abc;
//     struct uz_IIR_Filter_config config_bandpass_harmonic_dq;
//     struct uz_IIR_Filter_config config_lowpass_dq;
// };

struct uz_HarmonicCurrentInjection_config {
    float order_harmonic;
    enum uz_HarmonicCurrentInjection_mode_select selection;
    struct uz_CurrentControl_config config_currentcontroller;
    struct uz_IIR_Filter_config config_bandpass_abc;
    struct uz_IIR_Filter_config config_bandpass_dq;
    struct uz_IIR_Filter_config config_lowpass_dq;
};

/**
 * @brief Object definition for HarmonicCurrentInjection
 *
 */
typedef struct uz_HarmonicCurrentInjection_t uz_HarmonicCurrentInjection_t;

/**
 * @brief Initialization of the uz_HarmonicCurrentInjection object
 *
 * @param config configuration struct for HarmonicCurrentInjection
 * @return uz_HarmonicCurrentInjection_t* Pointer to uz_HarmonicCurrentInjection_t instance
 */
uz_HarmonicCurrentInjection_t* uz_HarmonicCurrentInjection_init(struct uz_HarmonicCurrentInjection_config config);

// /**
//  * @brief calculates last sample and transforms the dq-output voltage into the abc-system
//  * 
//  * @param self uz_HarmonicCurrentInjection_t instance
//  * @param i_ref_first_harmonic_Ampere uz_3ph_dq_t struct for reference dq-currents of first harmonic in Ampere
//  * @param i_ref_second_harmonic_Ampere uz_3ph_dq_t struct for reference dq-currents of second hamornic in Ampere
//  * @param i_actual_Ampere uz_3ph_abc_t struct for measured abc-currents in Ampere
//  * @param V_dc_volts DC link voltage. Must be greater than 0.0f
//  * @param omega_el_rad_per_sec electrical rotational speed in rad/s
//  * @param theta_el_rad electrical rotor angle in rad
//  * @return uz_3ph_dq_t Output abc-voltage struct
//  */
// uz_3ph_dq_t uz_HarmonicCurrentInjection_sample(uz_HarmonicCurrentInjection_t* self, uz_3ph_dq_t i_ref_first_harmonic_Ampere, uz_3ph_dq_t i_ref_second_harmonic_Ampere, uz_3ph_abc_t i_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec, float theta_el_rad);

/**
 * @brief calculates last sample and transforms the dq-output voltage into the abc-system
 * 
 * @param self uz_HarmonicCurrentInjection_t instance
 * @param i_ref_harmonic_Ampere uz_3ph_dq_t struct for reference dq-currents of harmonic in Ampere
 * @param i_actual_Ampere uz_3ph_abc_t struct for measured abc-currents in Ampere
 * @param V_dc_volts DC link voltage. Must be greater than 0.0f
 * @param omega_el_rad_per_sec electrical rotational speed in rad/s
 * @param theta_el_rad electrical rotor angle in rad
 * @return uz_3ph_dq_t Output abc-voltage struct
 */
uz_3ph_dq_t uz_HarmonicCurrentInjection_sample(uz_HarmonicCurrentInjection_t* self, uz_3ph_dq_t i_ref_harmonic_Ampere, uz_3ph_abc_t i_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec, float theta_el_rad);

/**
 * @brief Updates the abc-bandpasses and dqn-lowpasses for a given electrical rotational speed
 * 
 * @param self uz_HarmonicCurrentInjection_t instance
 * @param omega_el_ref_rad_per_sec Electrical rotational speed in rad/s
 */
void uz_HarmonicCurrentInjection_set_filters_abc(uz_HarmonicCurrentInjection_t* self, float omega_el_rad_per_sec);

/**
 * @brief Updates the dq-bandpasses and dqn-lowpasses for a given electrical rotational speed
 * 
 * @param self uz_HarmonicCurrentInjection_t instance
 * @param omega_el_ref_rad_per_sec Electrical rotational speed in rad/s
 */
void uz_HarmonicCurrentInjection_set_filters_dq(uz_HarmonicCurrentInjection_t* self, float omega_el_rad_per_sec);

#endif // UZ_HARMONICCURRENTINJECTION_H
